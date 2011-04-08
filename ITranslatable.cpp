#include "ITranslatable.h"
#include <QString>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>

void ITranslatable::fromText(QStringList &text)
{
    //Get Translation map
    QMap <QString,QWidget*> paramMap = getParameterMap();
    for (int i=0; i<text.count(); ++i) {
        QString t = text.at(i);
        //Get param key
        QString key = t.section("=",0,0).trimmed();

        if (paramMap.find(key) != paramMap.end()) {
            QWidget* p = paramMap.find(key).value();
            //Is text type.
            QLineEdit* l = dynamic_cast<QLineEdit*>(p);
            if (l) {
                l->setText(t.section("=",1,1).trimmed());
                continue;
            }
            //Is checkbox type.
            QCheckBox* b = dynamic_cast<QCheckBox*>(p);
            if (b) {
                if (t.section("=",1,1).trimmed() == "yes")
                    b->setChecked(true);
                else
                    b->setChecked(false);
                continue;
            }

        }
    }
}

QStringList ITranslatable::toText()
{
    QStringList output;
    QMap<QString,QWidget*> paramMap = getParameterMap();
    QMap<QString,QWidget*>::iterator it = paramMap.begin();

    for (it; it != paramMap.end(); ++it) {
        QWidget* p = it.value();
        if (!p->isVisible())
            //Don't output non-visible params
            continue;
        QString key = it.key();
        QString out = key + " = ";
        //Is text type
        QLineEdit* l = dynamic_cast<QLineEdit*>(p);
        if (l) {
            out += l->text();
            output << out;
            continue;
        }
        //Is checkbox type.
        QCheckBox* b = dynamic_cast<QCheckBox*>(p);
        if (b) {
            if (b->isChecked())
                out += "yes";
            else
                out += "no";
            output << out;
            continue;
        }
        //Is combobox type.
        QComboBox* c = dynamic_cast<QComboBox*>(p);
        if (c) {
            out += c->currentText();
            output << out;
            continue;
        }
    }

    return output;
}
