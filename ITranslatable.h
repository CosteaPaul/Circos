#ifndef ITRANSLATABLE_H
#define ITRANSLATABLE_H

class QStringList;
class QWidget;
#include <QMap>

class ITranslatable {
public:
    enum Type {
        IMAGE = 0,
        PLOT,
        LINK,
        RULE,
        MISC
    };

    void setType(Type t) {
        type = t;
    }

    Type getType() {
        return type;
    }

    virtual void fromText(QStringList &text);
    virtual QStringList toText();

protected:
    virtual QMap<QString,QWidget*>& getParameterMap() = 0;

protected:
    Type type;
};

#endif // ITRANSLATABLE_H
