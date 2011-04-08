#ifndef WIMAGE_H
#define WIMAGE_H

#include <QWidget>
#include <ITranslatable.h>
#include <QMap>

namespace Ui {
    class WImage;
}

class WImage : public QWidget, public ITranslatable
{
    Q_OBJECT

public:
    explicit WImage(QWidget *parent = 0);
    ~WImage();

    /** @brief: Populate widget with default values
      *
      */
    void loadDefaults();

    QString getOutputPath();

private:
    QMap<QString, QWidget*>& getParameterMap();

private:
    Ui::WImage *ui;
    QMap<QString, QWidget*> m_paramMap;

private slots:
    void on_toolButton_clicked();
    void on_checkBox_AlphaColors_stateChanged(int );
};

#endif // WIMAGE_H
