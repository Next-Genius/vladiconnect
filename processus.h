#ifndef PROCESSUS_H
#define PROCESSUS_H
#include <QtCore>

class processus : public QProcess {

    Q_OBJECT

    public:
       processus();
       int getNumero();
       void demarrer(QString chaine);
    public slots:
       void slot_fini(int,QProcess::ExitStatus);

signals :
        void signal_fini(int,QProcess::ExitStatus,int);

    protected:
       int m_numero;
       //QProcess process;

};

#endif // PROCESSUS_H
