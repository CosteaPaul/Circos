#include "circosmain.h"
#include "ui_circosmain.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>
#include <wimage.h>

#include "scircossession.h"

CircosMain::CircosMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CircosMain)
{
    ui->setupUi(this);
}

CircosMain::~CircosMain()
{
    delete ui;
}

void CircosMain::on_pushButton_clicked()
{
    //Some testing...

    //Add some image widget
    WImage *img = new WImage(ui->toolBox_editor);
    ui->toolBox_editor->insertItem(1,img,"Image");

}

void CircosMain::on_actionSettings_triggered()
{
    //TODO: implement
}

void CircosMain::on_actionOpen_triggered()
{
    QString input = QFileDialog::getOpenFileName(this,"Select circos file");
    SCircosSession* s = SCircosSession::getInstance();

    if (!s->loadFile(input,ui->toolBox_editor))
        QMessageBox::warning(this,"Load failed","Unable to load selected file");

    //Disconnect all previous connections
    disconnect(s,SIGNAL(newPlotAvailable(QString)),this,SLOT(on_newPlotAvailable(QString)));

    //Connect new
    connect(s,SIGNAL(newPlotAvailable(QString)),this,SLOT(on_newPlotAvailable(QString)));

    //Force update
    on_pushButton_2_clicked();
}

void CircosMain::on_pushButton_2_clicked()
{
    //On update
    ui->label_Image->setCursor(Qt::BusyCursor);
    //Get seesion
    SCircosSession* s = SCircosSession::getInstance();
    if (!s->updateCircosPlot()) {
        QMessageBox::warning(this,"Update failed", "Unable to update plot");
        ui->label_Image->setCursor(Qt::ArrowCursor);
    }

}

void CircosMain::on_newPlotAvailable(QString fileName)
{
    QPixmap pix(fileName);
    ui->label_Image->setScaledContents(true);
    ui->label_Image->setPixmap(pix);

    ui->label_Image->setCursor(Qt::ArrowCursor);
}
