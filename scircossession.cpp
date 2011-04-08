#include "scircossession.h"
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include "wimage.h"

SCircosSession* SCircosSession::m_pInstance = 0;

SCircosSession* SCircosSession::getInstance()
{
    if (!m_pInstance)
        m_pInstance = new SCircosSession();

    return m_pInstance;
}

SCircosSession::SCircosSession()
{
    m_loadedFile = "";
    m_pProcess = NULL;
}

int SCircosSession::loadFile(QString name, QToolBox *loadBox)
{
    //Open file
    QFile f(name);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    m_pToolBox = loadBox;

    //Read complete file
    QStringList file;
    QTextStream textStream(&f);
    while (true)
    {
        QString line = textStream.readLine();
        if (line.isNull())
            break;
        else
            //clean-up line (tabs and such)
            file.append(line.trimmed());
    }

    //Get image block
    int imgStart = file.indexOf(QString("<image>"));
    int imgEnd = file.indexOf(QString("</image>"));

    QStringList imgBlock;
    for (int i=imgStart+1; i<imgEnd; ++i)
        imgBlock << file.at(i);


    WImage *imgWidget = new WImage(m_pToolBox);
    imgWidget->setType(ITranslatable::IMAGE);
    imgWidget->fromText(imgBlock);

    m_pToolBox->insertItem(1,imgWidget,"Image");
    m_loadedFile = name;
}

QString SCircosSession::getOutputFile()
{
    for (int i=0; i<m_pToolBox->count(); ++i) {
        QWidget* p = m_pToolBox->widget(i);
        WImage* trans = dynamic_cast<WImage*>(p);
        if (trans) {
            return trans->getOutputPath();
        }
    }
}

bool SCircosSession::updateCircosPlot()
{
    //TODO: get Circos path from Settings
    m_pProcess = new QProcess();

    //Connect finished signal
    connect(m_pProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(updateDone(int,QProcess::ExitStatus)));

    QString app = QString("/home/paul/Work/circos-0.53/bin/") + QString("circos");
    m_pProcess->start(app,QStringList() << "-conf" << m_loadedFile);

    if (!m_pProcess->waitForStarted()) {
        //something went wrong.
        delete m_pProcess;
        return false;
    }

    return true;
}

void SCircosSession::updateDone(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::NormalExit) {
        //New plot available, emit!
        emit newPlotAvailable(getOutputFile());
    }

    //Remove process
    delete m_pProcess;
}
