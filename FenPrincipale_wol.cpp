#include "FenPrincipale.h"

int FenPrincipale::wol(QString sousReseau, QString mac, int numero_m_liste, int parametre) {
    maj_formulaire_action("D�marrage � distance", "Proc�dure lanc�e.", 30, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
    static int numero_ping = 0;
    QProcess *process = new QProcess;

    if(ENVIRONNEMENT == 1) {    //Windows
    } else {
        return -1;        //Linux
    }

    QString chemin_executable(QCoreApplication::applicationDirPath()+"/rw.exe");
    QFile file(chemin_executable);
    if(!file.exists()) {
        QMessageBox::warning(this, "WOL", "L'executable qui permet le d�marrage � distance n'a pas �t� trouv�.\n V�rifiez la pr�sence du fichier : \n"+chemin_executable+"\n Le  d�marrage � distance de la machine a �t� arr�t�e." );
        return -2;
    }

    QRegExp regExp("^([a-fA-F0-9]{2}:){5}[a-fA-F0-9]{2}$");
    if(!mac.contains(regExp)) {
        QMessageBox::warning(this, "WOL", "L'adresse MAC ne convient pas.\n Veuillez rev�rifier la synthaxe puis recommencez." );
        return -3;
    }

    mac.remove(QRegExp(":")); //remise ne forme de la synthaxe pour l'executable
    process->start(chemin_executable+" /m:"+mac+" ");
    process->setObjectName(QString::number(numero_ping));
    process->setProperty("termine",false);
    process->setProperty("parametre",parametre);
    process->setProperty("numero_m_liste", numero_m_liste);
    m_liste_processus.insert(numero_ping,process);
    QObject::connect(m_liste_processus[numero_ping], SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(fin_processus(int,QProcess::ExitStatus)));
    QObject::connect(m_liste_processus[numero_ping], SIGNAL(readyReadStandardOutput()), this, SLOT(sortie_processus_wol()));
    maj_formulaire_action("D�marrage � distance", "Signal de d�marrage envoy�. Attente d'une r�ponse.", 50, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
    numero_ping++;
    return 0;
}

void FenPrincipale::sortie_processus_wol() {
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
        QMessageBox::critical(this, "Fin de processus", "Le processus n'a pas �t� retrouv�");

    } else {
        QString retour;
        retour = monProcessus->readAllStandardOutput();
        console->appendPlainText("Retour \n<br />\n"+retour);
        //console->setPlainText(console"Retour \n<br />\n"+retour);
        if(retour == "\nRW.EXE - v1.3.2\nCopyright (c) 2002 by Patrick Garnier\n\nThis program is freeware - http://www.sysworksoft.net\nFeel free to send any comments to patrick.garnier@sysworksoft.net\n\nTrying to wake-up remote host: 0030BDB4BF37") {
            maj_formulaire_action("D�marrage � distance", "La proc�dure de lancement est termin�e.", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
            QMessageBox::information(this, "WOL", "La proc�dure de lancement est termin�e. \nVeuillez d�sormais v�rifier que la machine est bien r�veill�e. \n  Si dans 4 minutes, la machine ne r�pond pas, cela signifie qu'elle est peut �tre d�branche, mal configur�e ou <b>mal arr�t�e</b>.");
        } else if(retour == "\nRW.EXE - v1.3.2\nCopyright (c) 2002 by Patrick Garnier\n\nThis program is freeware - http://www.sysworksoft.net\nFeel free to ") {
                //si on r�cup�re 1/2 du texte de retour (1ere partie) alors on fait rien
            QMessageBox::warning(this, "WOL", "moiti� 1"+retour );

        } else if(retour == "") {

        }
        maj_formulaire_action("D�marrage � distance", "La proc�dure de lancement est termin�e.", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
        QMessageBox::warning(this, "WOL", "La r�ponse du programmee n'est pas correcte. Il s'est peut �tre produit une erreur. \n Voici la r�ponse du programme :\n"+retour );
    }
}



