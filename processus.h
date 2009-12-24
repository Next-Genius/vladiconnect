#ifndef PROCESSUS_H
#define PROCESSUS_H
#include <QtCore>
#include <QtGui>
//temp pou les QmessageBox

class processus : public QProcess {


    Q_OBJECT


    public:
        processus();
        int getNumero();

public slots:

    void slot_fini(int,QProcess::ExitStatus);

signals:
    void processus_signal_fini(int,QProcess::ExitStatus,int);

private:
    int m_numero;
    //QProcess process;

};

#endif // PROCESSUS_H


