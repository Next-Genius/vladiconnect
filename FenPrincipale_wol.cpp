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

int FenPrincipale::wol(QString sousReseau, QString mac, int numero_m_liste,
                       int parametre) {
    maj_formulaire_action("Démarrage à distance", "Procédure lancée.", 30,
                          QCoreApplication::applicationDirPath()
                          + "/images/utilities-system-monitor.png");
    static int numero_ping = 0;
    QProcess *process = new QProcess;

    if(ENVIRONNEMENT != 1) {    //n'estpas Windows
        return (-1);
    }

    QString chemin_executable(
            QCoreApplication::applicationDirPath()+":/executable/wol.exe");
    QFile file(chemin_executable);
    if(!file.exists()) {
        QMessageBox::critical(this, "WOL",
                              "L'executable qui permet le démarrage"
                             " à distance n'a pas été trouvé.\nVérifiez la "
                             "présence du fichier : \n"+chemin_executable+"\n"
                             );
        return -2;
    }

    QRegExp regExp("^([a-fA-F0-9]{2}:){5}[a-fA-F0-9]{2}$");
    if(!mac.contains(regExp)) {
        QMessageBox::warning(this, "WOL", "L'adresse MAC ne convient pas.\n"
                             "Veuillez revérifier la syntaxe");
        return -3;
    }

    //remise ne forme de la syntaxe pour l'executable
    mac.remove(QRegExp(":"));

    process->start(chemin_executable+" /m:"+mac+" ");
    process->start(":/executables/wol.exe /m:"+mac+" ");
    process->setObjectName(QString::number(numero_ping));
    process->setProperty("parametre",parametre);
    process->setProperty("numero_m_liste", numero_m_liste);
    m_liste_processus.insert(numero_ping,process);
    QObject::connect(m_liste_processus[numero_ping],
                     SIGNAL(finished(int,QProcess::ExitStatus)), this,
                     SLOT(fin_processus(int,QProcess::ExitStatus)));
    QObject::connect(m_liste_processus[numero_ping],
                     SIGNAL(readyReadStandardOutput()), this,
                     SLOT(sortie_processus_wol()));
    maj_formulaire_action("Démarrage à distance",
                          "Signal de démarrage envoyé. Attente d'une réponse.",
                          50, QCoreApplication::applicationDirPath()
                          + "/images/utilities-system-monitor.png");
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
        QMessageBox::critical(this, "Fin de processus",
                              "Le processus n'a pas été retrouvé");
        maj_formulaire_action("Démarrage à distance",
                              "Le processus n'a pas été retrouvé.", 0,
                              QCoreApplication::applicationDirPath()
                              + "/images/delete.png");

    } else {
        //insère le retour de console à ma fin du bloc
        console->appendPlainText(monProcessus->readAllStandardOutput());

        QScrollBar *sb = console->verticalScrollBar();
        sb->setValue(sb->maximum());

        maj_formulaire_action("Démarrage à distance",
                              "La procédure de lancement est terminée.", 100,
                              QCoreApplication::applicationDirPath()
                              + "/images/utilities-system-monitor.png");

       console->appendPlainText("La procédure de lancement est terminée. \n"
                                "Veuillez désormais vérifier que la machine "
                                "est bien réveillée. \n Si dans 4 minutes, "
               "la machine ne répond pas, cela signifie qu'elle "
               "est peut être débranchée, mal configurée ou mal arrêtée.\n"
               "Vérifiez également que le programme a les droits administrateurs.");
    }
}



