#ifndef WATCHERS_H

#include <QPlainTextEdit>
#include <QDomCharacterData>

class CharacterDataWatcher : public QObject {
	Q_OBJECT
protected:
	QPlainTextEdit* edit;
	QDomCharacterData data;
public:
	CharacterDataWatcher(QPlainTextEdit* _edit, const QDomCharacterData &_data) : QObject(_edit), edit(_edit), data(_data) {
		connect(edit, &QPlainTextEdit::textChanged,
            this, &CharacterDataWatcher::changed);
	}
public Q_SLOTS:
	void changed() {
		data.setData(edit->toPlainText());
	}
};

class TagNameWatcher : public QObject {
	Q_OBJECT
protected:
	QLineEdit* edit;
	QDomElement data;
public:
	TagNameWatcher(QLineEdit* _edit, const QDomElement &_data) : QObject(_edit), edit(_edit), data(_data) {
		connect(edit, &QLineEdit::textChanged,
            this, &TagNameWatcher::changed);
	}
public Q_SLOTS:
	void changed() {
		data.setTagName(edit->text());
	}
};

class AttrWatcher : public QObject {
	Q_OBJECT
protected:
	QLineEdit* edit;
	QDomAttr data;
	bool isValue;
public:
	AttrWatcher(QLineEdit* _edit, const QDomAttr &_data, bool _isValue) : QObject(_edit), edit(_edit), data(_data), isValue(_isValue) {
		connect(edit, &QLineEdit::textChanged,
            this, &AttrWatcher::changed);
	}
public Q_SLOTS:
	void changed() {
		if (isValue)
			data.setValue(edit->text());
		else
			data.setName(edit->text());
	}
};


#endif