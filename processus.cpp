#include "processus.h"
/*
processus::processus() {
    QProcess();
    static int numero = 0;

    m_numero = numero;

    numero++; //préparation prochain appel
    QObject::connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slot_fini(int,QProcess::ExitStatus)));

}*/
processus::processus() : QProcess(), m_numero(10) {

}

void processus::demarrer(QString chaine) {
    start(chaine);
}

int processus::getNumero() {
    return m_numero;
}

void processus::slot_fini(int exitCode, QProcess::ExitStatus exitStatut) {
    emit signal_fini(exitCode,exitStatut,m_numero);
}
/*
void processus::signal_fini(int exitCode,QProcess::ExitStatus exitStatut,int numero) {


}*/
