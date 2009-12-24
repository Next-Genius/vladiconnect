#include "processus.h"


processus::processus() {
    QProcess();
    static int numero = 0;  //en static pour sauvegarder le n° de processus
    m_numero = numero;
    QObject::connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slot_fini(int,QProcess::ExitStatus)));
    numero++; //préparation prochain appel
}

/*void processus::out() {
   // QMessageBox::information(0, "Fichier", "Serveur : \n nom : " +m_nom+ "\n ip : " + m_ip+"\n mac :"+m_mac+" ous avez sélectionné :\n");
}*/
int processus::getNumero() {
    return m_numero;
}

void processus::slot_fini(int exitCode, QProcess::ExitStatus exitStatut) {
    //emit processus_signal_fini(exitCode,exitStatut,m_numero);
    QMessageBox::information(0, "Fichier", "Serveur : ping n° : " +QString::number(m_numero)+ "\n Exitcode : " + QString::number(exitCode)+"us avez sélectionné :\n");
}



