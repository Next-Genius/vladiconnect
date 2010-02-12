#include "FenPrincipale.h"

int FenPrincipale::wol(QString sousReseau, QString mac, int numero_m_liste, int parametre) {
    maj_formulaire_action("Démarrage à distance", "Procédure lancée.", 30,
                          QCoreApplication::applicationDirPath()
                          + "/images/utilities-system-monitor.png");
    static int numero_ping = 0;
    QProcess *process = new QProcess;

    if(ENVIRONNEMENT == 1) {    //Windows
    } else {
        return -1;        //Linux
    }

    QString chemin_executable(QCoreApplication::applicationDirPath()+"/rw.exe");
    QFile file(chemin_executable);
    if(!file.exists()) {
        QMessageBox::warning(this, "WOL", "L'executable qui permet le démarrage à distance n'a pas été trouvé.\n Vérifiez la présence du fichier : \n"+chemin_executable+"\n Le  démarrage à distance de la machine a été arrêtée." );
        return -2;
    }

    QRegExp regExp("^([a-fA-F0-9]{2}:){5}[a-fA-F0-9]{2}$");
    if(!mac.contains(regExp)) {
        QMessageBox::warning(this, "WOL", "L'adresse MAC ne convient pas.\n Veuillez revérifier la synthaxe puis recommencez." );
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
    maj_formulaire_action("Démarrage à distance", "Signal de démarrage envoyé. Attente d'une réponse.", 50, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
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
        QMessageBox::critical(this, "Fin de processus", "Le processus n'a pas été retrouvé");
        maj_formulaire_action("Démarrage à distance", "Le processus n'a pas été retrouvé.", 0, QCoreApplication::applicationDirPath() + "/images/delete.png");

    } else {
        console->appendPlainText(monProcessus->readAllStandardOutput());    //insère le retour de console

        QScrollBar *sb = console->verticalScrollBar();
        sb->setValue(sb->maximum());

        maj_formulaire_action("Démarrage à distance", "La procédure de lancement est terminée.", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
        //QMessageBox::information(this, "WOL", "La procédure de lancement est terminée. \nVeuillez désormais vérifier que la machine est bien réveillée. \nSi dans 4 minutes, la machine ne répond pas, cela signifie qu'elle est peut être débranche, mal configurée ou mal arrêtée.\nVous pouvez vérifier dans la console le retour du programme pour déceler les éventuelles erreurs.");
    }
}



