#ifndef SCIRCOSSESSION_H
#define SCIRCOSSESSION_H
#include <QObject>
#include <QProcess>
#include <QToolBox>

class SCircosSession : public QObject
{
    Q_OBJECT

public:
    static SCircosSession* getInstance();

    QString getFileName(){
        return m_loadedFile;
    }

    QString getOutputFile();

    /** @brief: Load a new file
      * @param: name - Full path of file to load
      * @param: toolBox - Pointer to toolbox widget
      */
    int loadFile(QString name, QToolBox* loadBox);

    bool updateCircosPlot();

public slots:
    void updateDone(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void newPlotAvailable(QString fileName);

private:
    SCircosSession();
    SCircosSession(SCircosSession const&){};
    SCircosSession &operator=(SCircosSession const&){};
    static SCircosSession* m_pInstance;

    QString m_loadedFile;
    QProcess* m_pProcess;
    QToolBox* m_pToolBox;
};

#endif // SCIRCOSSESSION_H
