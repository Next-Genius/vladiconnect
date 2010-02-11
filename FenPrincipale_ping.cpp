#include "FenPrincipale.h"

int FenPrincipale::ping(QString ip, int numero_m_liste, int parametre) {
    static int numero_ping = 0;
    QProcess *process = new QProcess;
    QString arguments;

    //Limiter à un ping
    if(ENVIRONNEMENT == 1) {    //Windows
        arguments="ping "+ip+" -n 1 -w 1";
    } else {
        arguments="ping "+ip+" -c 1 -w 1";   //Linux
    }

    process->start(arguments);
    process->setObjectName(QString::number(numero_ping));
    process->setProperty("termine",false);
    process->setProperty("parametre",parametre);
    process->setProperty("numero_m_liste", numero_m_liste);

    m_liste_processus.insert(numero_ping,process);

    QObject::connect(m_liste_processus[numero_ping], SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(fin_processus(int,QProcess::ExitStatus)));

    numero_ping++;
    return numero_ping;
}

void FenPrincipale::fin_processus(int exitCode,QProcess::ExitStatus exitStatus) {

    QObject *monObjet = sender();
    QString nom(monObjet->objectName());
    QProcess *monProcessus = new QProcess;
    int trouve = 0;
    for(int i=0 ; i<m_liste_processus.count() ; i++) {
        if(nom == m_liste_processus[i]->objectName()) {
            monProcessus = m_liste_processus[i];
            trouve = 1;
            i = m_liste_processus.count(); //fin de la boucle
        }
    }

    if(trouve == 0) {
        QMessageBox::critical(this, "Fin de processus", "Le processus n'a pas été retrouvé");

    } else {
        monProcessus->setProperty("termine",true);
        int numero_m_liste = monProcessus->property("numero_m_liste").toInt();
        int parametre = monProcessus->property("parametre").toInt();
        if(exitCode == 0) {
            m_liste[numero_m_liste].setConnecte(true);
            (*(liste_serveur->item(numero_m_liste))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
            //QMessageBox::information(this, "Ti","Ping n°"+QString::number(numero)+"\n Numero m_liste :"+QString::number(numero_m_liste)+" \nCode :"+QString::number(monProcessus->exitCode())+"\nPC Allumé");
            if(parametre == 1) {
                //mise en forme des données pour le fomulaire
                maj_formulaire_action("Connexion", "Ping terminé. Machine connectée", 100, QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png");
            } else if(parametre == 2 && numero_m_liste !=0) {

            } else if(parametre == 3 && numero_m_liste !=0) {
                m_liste[numero_m_liste].setConnecte(true);
                action_etat->setText("Connecté");
                action_nom->setText("Vérification de connexion");
                action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
                action_progression->setValue(100);
                bouton_arreter->setEnabled(true);
                bouton_redemarrer->setEnabled(true);
                bouton_demarrer->setEnabled(false);
            }

        } else {
            m_liste[numero_m_liste].setConnecte(false);
            (*(liste_serveur->item(numero_m_liste))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
            //QMessageBox::information(this, "Ti","Ping n°"+QString::number(numero)+"\n Numero m_liste :"+QString::number(numero_m_liste)+"\nCode :"+QString::number(monProcessus->exitCode())+"\nPC Eteint\nStatut :"+QString::number(monProcessus->exitStatus())+"\nNbre processus :"+QString::number(m_liste_processus.count()));
            if(parametre == 1) {
                //mise en forme des données pour le fomulaire
                maj_formulaire_action("Connexion", "Ping terminé. Machine déconnectée", 1, QCoreApplication::applicationDirPath() + "/images/network-offline.png");
            } else if(parametre == 3 && numero_m_liste !=0) {
                bouton_arreter->setEnabled(false);
                bouton_redemarrer->setEnabled(false);
                bouton_demarrer->setEnabled(true);
            }
        }
        monProcessus->close();
    }
}



