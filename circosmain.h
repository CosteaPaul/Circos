#ifndef CIRCOSMAIN_H
#define CIRCOSMAIN_H

#include <QMainWindow>

namespace Ui {
    class CircosMain;
}

class CircosMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CircosMain(QWidget *parent = 0);
    ~CircosMain();

private:
    Ui::CircosMain *ui;

private slots:
    void on_pushButton_2_clicked();
    void on_actionOpen_triggered();
    void on_actionSettings_triggered();
    void on_pushButton_clicked();
    void on_newPlotAvailable(QString fileName);
};

#endif // CIRCOSMAIN_H
