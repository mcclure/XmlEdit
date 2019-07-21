#include "xmledit.h"
#include <QMessageBox>
#include <QTextStream>
#include <QStack>
#include <QLabel>

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

void XmlEdit::addNode(QDomNode node, int depth) {
	QWidget *pane = new QWidget(widget());

	QVBoxLayout *vPaneLayout = new QVBoxLayout(pane);
	pane->setLayout(vPaneLayout);

	QLabel *kindLabel = new QLabel(pane); vPaneLayout->addWidget(kindLabel);
	kindLabel->setText(nodeTypeName(node.nodeType()));
	switch(node.nodeType()) {
		case QDomNode::ElementNode:

			break;
		case QDomNode::TextNode:
		case QDomNode::CommentNode:

			break;
		// These should be impossible
		case QDomNode::AttributeNode:
		case QDomNode::BaseNode:
		// I don't know what these are
		case QDomNode::ProcessingInstructionNode:
		case QDomNode::DocumentNode:
		case QDomNode::DocumentTypeNode:
		case QDomNode::DocumentFragmentNode:
		case QDomNode::NotationNode:
		case QDomNode::CDATASectionNode:
		case QDomNode::EntityReferenceNode:
		case QDomNode::EntityNode:
		case QDomNode::CharacterDataNode: break;
	}
	//label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	//label->setAlignment(Qt::AlignBottom | Qt::AlignRight);
	vLayout->addWidget(kindLabel);
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

