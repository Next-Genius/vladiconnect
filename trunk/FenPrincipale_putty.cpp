/*******************************************************************
 This file is part of Vladiconnect
 Copyright (C) 2009-2010 Louis VICAINNE (louis.vicainne@gmail.com)

 Vladiconnect is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public Licence
 as published by the Free Software Foundation; either version 2
 of the Licence, or (at your option) any later version.

 Vladiconnect is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public Licence for more details.

 You should have received a copy of the GNU General Public Licence
 along with VladiConnect; if not, write to the Free Software Foundation,
 Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
********************************************************************/
#include "FenPrincipale.h"

int FenPrincipale::putty_commande(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int parametre) {
    int os = Putty::LINUX;
    Putty::commande(hote, utilisateur, mdp, numero_m_liste, os, parametre);

    static int numero_ping = 0;
    QProcess *process = new QProcess;

    QString chemin_executable(QCoreApplication::applicationDirPath()+"/plink.exe");
    QFile file(chemin_executable);
    if(!file.exists()) {
        QMessageBox::warning(this, "PLink", "L'executable qui permet le "
                             "démarrage à distance n'a pas été trouvé.\n"
                             "Vérifiez la présence du fichier : \n"+chemin_executable+"\n" );
        return -2;
    }

    if(parametre == Putty::EXECUTER) {

        maj_formulaire_action("Execution à distance", "Procédure lancée.", 10,
                              QCoreApplication::applicationDirPath()
                              + "/images/utilities-system-monitor.png");
        //-v : verbosity
        //-l : specifier login
        //-P : port
        //-pw : password (not recommended)
        process->start(chemin_executable+" -ssh -v -pw "+mdp+" "+utilisateur+"@"+hote+"");
        //process->start(chemin_executable+" -ssh -v -pw "+mdp+" -m "+QCoreApplication::applicationDirPath()+"/commande_putty.txt "+utilisateur+"@"+hote+"");
        process->setObjectName(QString::number(numero_ping));
        process->setProperty("numero_m_liste", numero_m_liste);
        m_liste_processus.insert(numero_ping,process);
        QObject::connect(m_liste_processus[numero_ping], SIGNAL(finished(int,QProcess::ExitStatus)),
                         this, SLOT(putty_fin(int,QProcess::ExitStatus)));
        QObject::connect(m_liste_processus[numero_ping],
                         SIGNAL(readyReadStandardOutput()),
                         this, SLOT(putty_retour()));
        maj_formulaire_action("Démarrage à distance", "Signal de démarrage envoyé."
                              "Attente d'une réponse.", 50, QCoreApplication::applicationDirPath()
                              + "/images/utilities-system-monitor.png");
        numero_ping++;
    }
    return 0;
}

void FenPrincipale::putty_retour() {
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

        maj_formulaire_action("Démarrage à distance", "Lancement de putty terminé", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
        //QMessageBox::information(this, "WOL", "La procédure de lancement est terminée. \nVeuillez désormais vérifier que la machine est bien réveillée. \nSi dans 4 minutes, la machine ne répond pas, cela signifie qu'elle est peut être débranche, mal configurée ou mal arrêtée.\nVous pouvez vérifier dans la console le retour du programme pour déceler les éventuelles erreurs.");
    }
}

void FenPrincipale::putty_fin(int exitCode,QProcess::ExitStatus exitStatus) {
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

        maj_formulaire_action("Démarrage à distance", "Putty est terminé.", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
        //QMessageBox::information(this, "WOL", "La procédure de lancement est terminée. \nVeuillez désormais vérifier que la machine est bien réveillée. \nSi dans 4 minutes, la machine ne répond pas, cela signifie qu'elle est peut être débranche, mal configurée ou mal arrêtée.\nVous pouvez vérifier dans la console le retour du programme pour déceler les éventuelles erreurs.");
    }
    monProcessus->close();
}


