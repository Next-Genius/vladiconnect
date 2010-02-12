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
                             "d�marrage � distance n'a pas �t� trouv�.\n"
                             "V�rifiez la pr�sence du fichier : \n"+chemin_executable+"\n" );
        return -2;
    }

    if(parametre == Putty::EXECUTER) {

        maj_formulaire_action("Execution � distance", "Proc�dure lanc�e.", 10,
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
        maj_formulaire_action("D�marrage � distance", "Signal de d�marrage envoy�."
                              "Attente d'une r�ponse.", 50, QCoreApplication::applicationDirPath()
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
        QMessageBox::critical(this, "Fin de processus", "Le processus n'a pas �t� retrouv�");
        maj_formulaire_action("D�marrage � distance", "Le processus n'a pas �t� retrouv�.", 0, QCoreApplication::applicationDirPath() + "/images/delete.png");

    } else {
        console->appendPlainText(monProcessus->readAllStandardOutput());    //ins�re le retour de console

        QScrollBar *sb = console->verticalScrollBar();
        sb->setValue(sb->maximum());

        maj_formulaire_action("D�marrage � distance", "Lancement de putty termin�", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
        //QMessageBox::information(this, "WOL", "La proc�dure de lancement est termin�e. \nVeuillez d�sormais v�rifier que la machine est bien r�veill�e. \nSi dans 4 minutes, la machine ne r�pond pas, cela signifie qu'elle est peut �tre d�branche, mal configur�e ou mal arr�t�e.\nVous pouvez v�rifier dans la console le retour du programme pour d�celer les �ventuelles erreurs.");
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
        QMessageBox::critical(this, "Fin de processus", "Le processus n'a pas �t� retrouv�");
        maj_formulaire_action("D�marrage � distance", "Le processus n'a pas �t� retrouv�.", 0, QCoreApplication::applicationDirPath() + "/images/delete.png");

    } else {
        console->appendPlainText(monProcessus->readAllStandardOutput());    //ins�re le retour de console

        QScrollBar *sb = console->verticalScrollBar();
        sb->setValue(sb->maximum());

        maj_formulaire_action("D�marrage � distance", "Putty est termin�.", 100, QCoreApplication::applicationDirPath() + "/images/utilities-system-monitor.png");
        //QMessageBox::information(this, "WOL", "La proc�dure de lancement est termin�e. \nVeuillez d�sormais v�rifier que la machine est bien r�veill�e. \nSi dans 4 minutes, la machine ne r�pond pas, cela signifie qu'elle est peut �tre d�branche, mal configur�e ou mal arr�t�e.\nVous pouvez v�rifier dans la console le retour du programme pour d�celer les �ventuelles erreurs.");
    }
    monProcessus->close();
}


