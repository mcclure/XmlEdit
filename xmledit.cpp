#include "xmledit.h"
#include <QMessageBox>
#include <QTextStream>
#include <QStack>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>

DocumentEdit::DocumentEdit(QWidget *parent) : QScrollArea(parent) {
	setWidgetResizable(true);
}

void DocumentEdit::clearUi() {
	setWidget(new QWidget());
}

XmlEdit::XmlEdit(QWidget *parent) : DocumentEdit(parent), vLayout(NULL) {
}

XmlEdit::~XmlEdit() {
	
}

void XmlEdit::clearUi() {
	DocumentEdit::clearUi();

	vLayout = new QVBoxLayout(widget());
	widget()->setLayout(vLayout);
}

static const QString &nodeTypeName(QDomNode::NodeType nodeType) {
	static QString Element("Element"), Attribute("Attribute"), Text("Text"),
		CDATA("CData"), EntityReference("Entity Reference"), Entity("Entity"),
		ProcessingInstruction("Processing Instruction"), Comment("Comment"),
		Document("Document"), DocumentType("Document Type"),
		DocumentFragment("DocumentFragment"), Notation("Notation"),
		Base("Untyped?"), CharacterData("CharacterData");
	switch(nodeType) {
		case QDomNode::ElementNode:               return Element;
		case QDomNode::AttributeNode:             return Attribute;
		case QDomNode::TextNode:                  return Text;
		case QDomNode::CDATASectionNode:          return CDATA;
		case QDomNode::EntityReferenceNode:       return EntityReference;
		case QDomNode::EntityNode:                return Entity;
		case QDomNode::ProcessingInstructionNode: return ProcessingInstruction;
		case QDomNode::CommentNode:               return Comment;
		case QDomNode::DocumentNode:              return Document;
		case QDomNode::DocumentTypeNode:          return DocumentType;
		case QDomNode::DocumentFragmentNode:      return DocumentFragment;
		case QDomNode::NotationNode:              return Notation;
		case QDomNode::BaseNode:                  return Base;
		case QDomNode::CharacterDataNode:         return CharacterData;
	}
} 

#include <watchers.h>

void XmlEdit::addNode(QDomNode node, int depth) {
	QWidget *pane = new QWidget(widget());

	QWidget *content = pane;
	if (depth > 0) {
		QHBoxLayout *hPaneLayout = new QHBoxLayout(pane);
		hPaneLayout->setContentsMargins(0,0,0,0);
		pane->setLayout(hPaneLayout);
		hPaneLayout->addSpacing(depth*40);
		content = new QWidget(pane);
		hPaneLayout->addWidget(content);
	}

	QVBoxLayout *vContentLayout = new QVBoxLayout(content);
	vContentLayout->setContentsMargins(0,0,0,0);
	content->setLayout(vContentLayout);

	QLabel *kindLabel = new QLabel(content); vContentLayout->addWidget(kindLabel);
	kindLabel->setText(nodeTypeName(node.nodeType()));
	vContentLayout->addWidget(kindLabel);
	switch(node.nodeType()) {
		case QDomNode::ElementNode: {
			QDomElement element = node.toElement();

			QLineEdit *tagEdit = new QLineEdit(content);
			vContentLayout->addWidget(tagEdit);
			QFontMetrics metrics(tagEdit->font());
			int columnWidth = metrics.averageCharWidth();
			tagEdit->setFixedWidth(30*columnWidth);
			tagEdit->setText(element.tagName());

			new TagNameWatcher(tagEdit, element);

			QDomNamedNodeMap attributes = element.attributes();
			for(int c = 0; c < attributes.length(); c++) {
				QDomNode attributeNode = attributes.item(c);
				QDomAttr attribute = attributeNode.toAttr();
				if (!attribute.isNull()) {
					QWidget *assign = new QWidget(content);
					QHBoxLayout *hAssignLayout = new QHBoxLayout(assign);
					hAssignLayout->setContentsMargins(0,0,0,0);
					assign->setLayout(hAssignLayout);
					vContentLayout->addWidget(assign);

					QLineEdit *assignLeft = new QLineEdit(assign);
					hAssignLayout->addWidget(assignLeft);
					assignLeft->setFixedWidth(30*columnWidth);
					assignLeft->setText(attribute.name());

					QLabel *assignLabel = new QLabel("=", assign);
					hAssignLayout->addWidget(assignLabel);

					QLineEdit *assignRight = new QLineEdit(assign);
					hAssignLayout->addWidget(assignRight);
					assignRight->setFixedWidth(38*columnWidth);
					assignRight->setText(attribute.value());
					new AttrWatcher(assignLeft, assignRight, element);

					hAssignLayout->addStretch();
				}
			}
		} break;
		case QDomNode::TextNode:
		case QDomNode::CommentNode: {
			QDomCharacterData data = node.toCharacterData();
			QPlainTextEdit *textEdit = new QPlainTextEdit(content);

			QFontMetrics metrics(textEdit->font());
			int rowHeight = metrics.lineSpacing();
			int columnWidth = metrics.averageCharWidth();
			textEdit->setFixedHeight(6*rowHeight);
			textEdit->setFixedWidth(80*columnWidth);

			textEdit->setPlainText(data.data());
			vContentLayout->addWidget(textEdit);

			new CharacterDataWatcher(textEdit, data);
		} break;
		// These should be impossible
		case QDomNode::AttributeNode:
		case QDomNode::BaseNode:
		case QDomNode::CharacterDataNode:
		// I don't know what these are
		case QDomNode::ProcessingInstructionNode:
		case QDomNode::DocumentNode:
		case QDomNode::DocumentTypeNode:
		case QDomNode::DocumentFragmentNode:
		case QDomNode::NotationNode:
		case QDomNode::CDATASectionNode:
		case QDomNode::EntityReferenceNode:
		case QDomNode::EntityNode:
			break;
	}
	//label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	//label->setAlignment(Qt::AlignBottom | Qt::AlignRight);

	vLayout->addWidget(pane);
}

bool XmlEdit::isModified() const {
	return false;
}

#ifndef QT_NO_CLIPBOARD
void XmlEdit::cut() {

}
void XmlEdit::copy() {

}
void XmlEdit::paste() {

}
#endif

bool XmlEdit::read(QIODevice *device) {
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        QMessageBox::information(window(), tr("XML Editor"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
        return false;
    }

    clearUi();

    QDomElement root = domDocument.documentElement();
    QStack<QDomNode> stack;
    QDomNode current = root;

    while(1) {
    	if (!current.isNull()) {
    		addNode(current, stack.count());
    		stack.push(current);
    		current = current.firstChild();
    	} else if (!stack.count()) {
    		break;
    	} else {
    		current = stack.pop().nextSibling();
    	}
    }

    return true;
}

bool XmlEdit::write(QIODevice *device) const {
    const int IndentSize = 4;

    QTextStream out(device);
    domDocument.save(out, IndentSize);
    return true;
}


void XmlEdit::clear() { // Also resets file state
	domDocument.clear();
	clearUi();
}

