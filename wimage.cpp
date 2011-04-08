#include "wimage.h"
#include "ui_wimage.h"
#include <QDir>
#include <QFileDialog>

WImage::WImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WImage)
{
    ui->setupUi(this);
    //Create map!
    m_paramMap["dir"] = ui->lineEdit_Dir;
    m_paramMap["file"] = ui->lineEdit_FileName;
    m_paramMap["24bit"] = ui->checkBox_24bit;
    m_paramMap["png"] = ui->checkBox_png;
    m_paramMap["svg"] = ui->checkBox_svg;
    m_paramMap["radius"] = ui->lineEdit_Radius;
    m_paramMap["background"] = ui->comboBox_color;
    m_paramMap["auto_alpha_colors"] = ui->checkBox_AlphaColors;
    m_paramMap["auto_alpha_steps"] = ui->lineEdit_AlphaSteps;

    loadDefaults();
}

QMap<QString,QWidget*>& WImage::getParameterMap()
{
    return m_paramMap;
}

QString WImage::getOutputPath()
{
    return ui->lineEdit_Dir->text()+ QDir::separator() + ui->lineEdit_FileName->text();
}

void WImage::loadDefaults()
{
    ui->lineEdit_Dir->setText("/tmp");
    ui->lineEdit_FileName->setText("tmp.png");
    ui->lineEdit_Radius->setText("1500p");
    ui->lineEdit_AlphaSteps->setText("5");
    ui->checkBox_24bit->setChecked(true);
    ui->checkBox_png->setChecked(true);
    ui->checkBox_svg->setChecked(false);
    ui->checkBox_AlphaColors->setChecked(false);
    ui->lineEdit_AlphaSteps->setVisible(false);
    ui->label_5->setVisible(false);
}

WImage::~WImage()
{
    delete ui;
}

void WImage::on_checkBox_AlphaColors_stateChanged(int state)
{
    ui->label_5->setVisible(state == Qt::Checked);
    ui->lineEdit_AlphaSteps->setVisible(state == Qt::Checked);
}

void WImage::on_toolButton_clicked()
{
    ui->lineEdit_Dir->setText( QFileDialog::getExistingDirectory(this,"Output directory",QString(),QFileDialog::ShowDirsOnly) );
}
