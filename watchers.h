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

#endif