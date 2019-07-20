#ifndef XMLEDIT_H
#define XMLEDIT_H

#include <QAbstractScrollArea>

// Frustratingly, Qt has no abstract document class.
// They have a text document class but it cannot be separated from its text model.
// Therefore, this class reimplements much of the interface of QPlainTextEdit and QTextDocument.
class XmlEdit : public QAbstractScrollArea
{
    Q_OBJECT

public:
    XmlEdit();
    virtual ~XmlEdit();

    bool isModified() const;

public Q_SLOTS:
#ifndef QT_NO_CLIPBOARD
	void cut();
    void copy();
    void paste();
#endif
    //void undo();
    //void redo();
    void clear(); // Also resets file state
Q_SIGNALS:
	void contentsChanged();
    //void undoAvailable(bool);
    //void redoAvailable(bool);
    //void undoCommandAdded();
    void copyAvailable(bool b);
};

#endif
