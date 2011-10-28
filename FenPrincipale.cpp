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

FenPrincipale::FenPrincipale(QSettings * s) {
    setupUi(this);
    setWindowIcon(QIcon(":/images/icone.png"));
    setWindowTitle(QString(NOM_LOGICIEL())+" - v"+QString::number(VERSION_LOGICIEL()));

    f_ver = VERSION_LOGICIEL();
    ver = "0.511";

    if (tr("LTR") == "RTL") { qApp->setLayoutDirection(Qt::RightToLeft); }

#ifdef Q_WS_MAC
    actionBrushedMetalStyle = new QAction(tr("Use the brushed metal style"), this);
    actionBrushedMetalStyle->setStatusTip(tr("Use the brushed metal style"));
    actionBrushedMetalStyle->setCheckable(true);
    menuOptions->addAction(actionBrushedMetalStyle);

    actionQuit->setMenuRole(QAction::QuitRole);
    actionAbout->setMenuRole(QAction::AboutRole);
#endif

    this->createTrayActions();
    this->createTrayIcon();
    trayIcon->show();

        run_hidden = false;
    //charger la liste des serveurs vers QList<serveur> + copie des noms dans QListString
    chargerConfiguration("defaut");
    activer_formulaire(false);

    //barre état
    QLabel *progression = new QLabel("Prêt");
    statusBar()->addWidget(progression);

    QSize taille_icone(30,30);
    bouton_editer->setIcon(QIcon(":/images/document-edit.png"));
    bouton_editer->setIconSize(taille_icone);

    //QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/document-edit.png"));
    trayIcon->showMessage("Vladiconnect", "Vladiconnect est démarré");


    bouton_serveur_valider_modifications->setIcon(QIcon(":/images/dialog-ok.png"));
    bouton_serveur_valider_modifications->setIconSize(taille_icone);

    bouton_supprimer_serveur->setIcon(QIcon(":/images/delete.png"));
    bouton_supprimer_serveur->setIconSize(taille_icone);

    connect(actionCharger_une_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_importer_clicked()));
    connect(actionSauver_la_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_exporter_clicked()));
    connect(actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(actionRun_hidden, SIGNAL(toggled(bool)), this, SLOT(setRunHidden(bool)));

    sync_settings = s;
    readSettings();

    initialisation_executables();
}


void FenPrincipale::maj_formulaire_action(QString titre, QString etat, int progression, QString icone) {
    action_nom->setText(titre);
    action_etat->setText(etat);
    action_progression->setValue(progression);
    action_etat_pixmap->setPixmap(QPixmap(icone));
    trayIcon->showMessage(titre, etat);
}
void FenPrincipale::initialisation_executables() {
    /*QMessageBox::critical(this, "vérification de l'intégrité du logiciel",
         "Une erreur s'est produite lors du démarrage du logiciel.<br> "
         "Certains fichiers nécessaires au logiciels sont absents :<br>"
         "test.exe");*/
    QString chemin_executable(
            QCoreApplication::applicationDirPath()+"/wol.exe");
    QFile file(chemin_executable);
    if(!file.exists()) {
        QMessageBox::critical(this, "WOL",
                              "L'executable qui permet le démarrage"
                             " à distance n'a pas été trouvé.\n Vérifiez la "
                             "présence du fichier : \n"+chemin_executable+"\n"
                             );
        //return -2;
    }

}

int FenPrincipale::miseAJour_QList_vers_formulaire(int numero_serveur) {
int i;
i = numero_serveur;
    serveur_nom->setText(liste_serveur->item(i)->text());
    serveur_ip->setText(liste_serveur->item(i)->data(100).toString());
    serveur_mac->setText(liste_serveur->item(i)->data(200).toString());
    serveur_sousReseau->setText(liste_serveur->item(i)->data(300).toString());
    serveur_description->setText(liste_serveur->item(i)->data(400).toString());
    if(liste_serveur->item(i)->data(600).toString() == "Windows 7") {
        serveur_os->setCurrentIndex(1);
    } else if (liste_serveur->item(i)->data(600).toString() == "Windows XP") {
        serveur_os->setCurrentIndex(0);
    } else if (liste_serveur->item(i)->data(600).toString() == "Linux") {
        serveur_os->setCurrentIndex(2);
    } else {    //Autre
        serveur_os->setCurrentIndex(3);
    }

    serveur_utilisateur->setText(liste_serveur->item(i)->data(700).toString());
    serveur_mdp->setText(liste_serveur->item(i)->data(800).toString());
/*
    if(m_liste[numero_serveur].getConnecte() == true) {
        //serveur connecté
        action_etat->setText("Connecté");
        action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
        //(*(liste_serveur->item(numero_serveur))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
    } else {
        //serveur non connecté
        action_etat->setText("Déconnecté");
        action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
        //(*(liste_serveur->item(numero_serveur))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
    }*/
    return true;
}

int FenPrincipale::miseAJour_formulaire_vers_QList(int numero_serveur) {
    //modifs du nom du serveur
    (liste_serveur->currentItem())->setText(serveur_nom->text());
    liste_serveur->item(numero_serveur)->setText(serveur_nom->text());;
    liste_serveur->item(numero_serveur)->setData(100, serveur_ip->text());
    liste_serveur->item(numero_serveur)->setData(200, serveur_mac->text());
    liste_serveur->item(numero_serveur)->setData(300, serveur_sousReseau->text());
    liste_serveur->item(numero_serveur)->setData(400, serveur_description->toPlainText());
    liste_serveur->item(numero_serveur)->setData(600, serveur_os->currentText());
    liste_serveur->item(numero_serveur)->setData(700, serveur_utilisateur->text());
    liste_serveur->item(numero_serveur)->setData(800, serveur_mdp->text());

    ping(liste_serveur->item(numero_serveur)->data(100).toString(), liste_serveur->currentRow());

    return 0;
}

void FenPrincipale::on_bouton_ping_clicked() {
    bouton_ping->setEnabled(false); //on désactive le ping temporairement
    maj_formulaire_action("Vérification de connexion", "Initialisation du ping", 10,
                          ":/images/network-transmit.png");
    ping(serveur_ip->text(), liste_serveur->currentRow(),1);
    action_etat->setText("Ping en cours");

    bouton_ping->setEnabled(true); //on réactive le bouton ping
}


void FenPrincipale::on_bouton_arreter_clicked() {
    maj_formulaire_action("Arrêt à distance", "Initialisation. Connexion en cours.", 5,
                          ":/images/network-transmit.png");

    action_progression->setValue(50);
}

void FenPrincipale::on_bouton_ajouter_serveur_clicked() {
    QString nom;
    if((liste_serveur->findItems(QString("Nouveau serveur"),
                                 Qt::MatchExactly|Qt::MatchCaseSensitive)).size() != 0) {
        for(int i=1; i < (*liste_serveur).count()+1 ;i++) {
            if((liste_serveur->findItems("Nouveau serveur (" +QString::number(i)+ ")",
                                         Qt::MatchExactly|Qt::MatchCaseSensitive)).size() == 0) {
                nom = "Nouveau serveur ("+QString::number(i)+")";
                i = (*liste_serveur).count(); //liste_serveur->count();
            }
        }
    } else {
        nom = "Nouveau serveur";
    }

    QListWidgetItem *item2 = new QListWidgetItem(liste_serveur); /*, nom, "192.168..",
                                           "", "192.168.1.255", "Windows 7", "", "");*/
    item2->setText(nom);
    item2->setData(100, QString("192.168.."));
    item2->setData(200, QString(""));
    item2->setData(300, QString("192.168.1.255"));
    item2->setData(400, QString("Pas de description"));
    item2->setData(500, false);
    item2->setData(600, QString("1"));
    liste_serveur->addItem(item2);

    //modifie la sélection vers le nouvel élément + scroll vers le nouvel élément pour être sûr qu'il est visualisé
    int ligne = liste_serveur->count();
    ligne--;
    liste_serveur->setCurrentRow((ligne));
    liste_serveur->item(ligne)->setIcon(QIcon(":/images/network-offline.png"));
    QObject::connect(bouton_ajouter_serveur, SIGNAL(clicked()), liste_serveur, SLOT(scrollToBottom()));

    //active les boutons de suppression au cas où ils auraient été désactivé dans le cas où plus de serveur.
    bouton_supprimer_serveur->setEnabled(true);
    bouton_supprimer_serveur2->setEnabled(true);
}

void FenPrincipale::on_bouton_supprimer_serveur_clicked() { //vérifié 1
    if(liste_serveur->count() < 1) {
        //pas d'item donc pas de suppression
        QMessageBox::critical(this, "Déletion d'un serveur",
             "Une erreur s'est produite lors de la suppression "
             "du serveur sélectionné : la liste est vide !");

    } else {

        //pointeur vers l'item actuel
        QListWidgetItem *item_actuel;
        item_actuel = liste_serveur->currentItem();

        //sélection du nouveau serveur courant pour après suppression
        if(liste_serveur->count() == 1)  {  //plus de serveur donc pas de sélection
            bouton_supprimer_serveur->setEnabled(false);
            bouton_supprimer_serveur2->setEnabled(false);
        } else {
            if(liste_serveur->currentRow() == 0) {
                liste_serveur->setCurrentRow(0);    //sélection de la 1ere ligne (n°0)
            } else {
                //sélection de la ligne précédénte
                liste_serveur->setCurrentRow((liste_serveur->currentRow())-1);
            }
        }

        //suppression dans la vue de l'item
        delete item_actuel;

    }
}
void FenPrincipale::on_bouton_supprimer_serveur2_clicked() {
    on_bouton_supprimer_serveur_clicked();
}

void FenPrincipale::on_bouton_trier_serveur_clicked() {
    liste_serveur->sortItems(Qt::AscendingOrder);
}

void FenPrincipale::on_bouton_editer_clicked() {
    liste_serveur->setEnabled(false);
    activer_formulaire(true);
}

void FenPrincipale::on_bouton_serveur_valider_modifications_clicked() {
    liste_serveur->setEnabled(true);
    activer_formulaire(false);

    miseAJour_formulaire_vers_QList(liste_serveur->currentRow());
    enregistrerConfiguration("defaut");

}

void FenPrincipale::on_bouton_configuration_importer_clicked() {
    int reponse = QMessageBox::warning(this, "Chargement d'une nouvelle configuration",
                     "Êtes vous sûr de vouloir écraser l'ancienne configuration ?",
                     QMessageBox::Yes | QMessageBox::No);

    if(reponse == QMessageBox::Yes) {
        chargerConfiguration();
    }
}

void FenPrincipale::on_bouton_configuration_exporter_clicked() {
    enregistrerConfiguration();
}

void FenPrincipale::setValueAction(int value) {
    action_progression->setValue(value);
}

void FenPrincipale::on_bouton_demarrer_clicked() {
    maj_formulaire_action("Démarrage à distance", "Lancement de la procédure.",
                          5, ":/images/network-offline.png");
    //wol::wol(serveur_mac->text(), liste_serveur->currentRow());
    wol(serveur_sousReseau->text(), serveur_mac->text(), liste_serveur->currentRow());
}

void FenPrincipale::on_liste_serveur_itemSelectionChanged() {
    liste_serveur->setEnabled(true);
    if(liste_serveur->count() != 0) {
        int i = liste_serveur->currentRow();

        ping(liste_serveur->item(i)->data(100).toString(), i, 3);
        activer_formulaire(false);
        miseAJour_QList_vers_formulaire(i);
    }
}

int FenPrincipale::miseAJourItem() {    //vérifié 1
    if(liste_serveur->count()!=0) //si pas d'Item, inutile de MAJ
        return true;

    //si pas de sélection, inutile aussi
    if((liste_serveur->selectedItems()).size() == 0)
        return true;

    //MAJ form->QList
    if(miseAJour_formulaire_vers_QList(liste_serveur->currentRow()) == true)
        return true;
    //sinon
    return false;
}

void FenPrincipale::on_bouton_maj_auto_clicked() {
    for (int i=0; i<liste_serveur->count(); i++) {
        ping(liste_serveur->item(i)->data(100).toString(), i);
    }

    QMessageBox::information(this, "Mise à jour des serveur",
                             "Les états des serveurs ont été mis à jour !");
}

void FenPrincipale::activer_formulaire(bool activer) {
    //1ère partie du formulaire
    serveur_nom->setEnabled(activer);
    serveur_ip->setEnabled(activer);
    serveur_mac->setEnabled(activer);
    serveur_sousReseau->setEnabled(activer);
    serveur_description->setEnabled(activer);
    serveurActiverArret->setEnabled(activer);
    if(serveurActiverArret->isEnabled()) {
        //Paramètres d'arret à distance
        serveur_os->setEnabled(activer);
        serveur_utilisateur->setEnabled(activer);
        serveur_mdp->setEnabled(activer);
    } else {
        serveur_os->setEnabled(false);
        serveur_utilisateur->setEnabled(false);
        serveur_mdp->setEnabled(false);
    }

    if(activer == false) {
        bouton_demarrer->setEnabled(activer);
        bouton_redemarrer->setEnabled(activer);
        bouton_arreter->setEnabled(activer);
    }
    //Ne pas modifier le bouton ping

    //Activation des boutons d'activation du formulaire
    if(activer == true) {
        bouton_serveur_valider_modifications->setEnabled(true);
        bouton_editer->setEnabled(false);
    } else {
        bouton_serveur_valider_modifications->setEnabled(false);
        bouton_editer->setEnabled(true);
    }
}
void FenPrincipale::on_serveurActiverArret_stateChanged(int state) {
    if(state == Qt::Checked) {
        serveur_os->setEnabled(true);
        serveur_utilisateur->setEnabled(true);
        serveur_mdp->setEnabled(true);
    } else {
        serveur_os->setEnabled(false);
        serveur_utilisateur->setEnabled(false);
        serveur_mdp->setEnabled(false);
    }
}

void FenPrincipale::on_bouton_console_clicked() {
    putty_commande("192.168.1.5","vladiyork","danton",liste_serveur->currentRow(),Putty::EXECUTER);
    QMessageBox::critical(this, "Test", "Sortie d'un elelement :\nnom="
                          +liste_serveur->currentItem()->text()
                          +"\nip="+liste_serveur->currentItem()->data(100).toString()
                          +"\nmac="+liste_serveur->currentItem()->data(200).toString()
                          +"\nsousres="+liste_serveur->currentItem()->data(300).toString()
                          +"\ndesc="+liste_serveur->currentItem()->data(400).toString()
                          );
}

void FenPrincipale::on_bouton_open_putty_clicked() {
    QProcess *putty_process = new QProcess;

    QString chemin_executable(QCoreApplication::applicationDirPath()+"/putty.exe");
    QFile file(chemin_executable);
    if(file.exists()) {
        maj_formulaire_action("Putty", "Lancement de Putty en cours.", 10,
                              ":/images/utilities-system-monitor.png");
        putty_process->start(chemin_executable);
        maj_formulaire_action("Lancement de Putty", "Putty est lancé.",
                              100, ":/images/utilities-system-monitor.png");
    } else {
        QMessageBox::warning(this, "Putty", "L'executable n'a pas été trouvé.\n"
                             "Vérifiez la présence du fichier : \n"+chemin_executable+"\n" );
    }
        trayIcon->showMessage("Putty", tr("Putty est lancé !"));
}

void FenPrincipale::on_bouton_close_putty_clicked() {
    if(putty_process->state() == QProcess::NotRunning) {
        QMessageBox::warning(this, "Putty", tr("Putty était déjà arrêté.\n"));
    } else {
        putty_process->kill();
        maj_formulaire_action("Putty", "Putty a été arrêté.", 10,
                              ":/images/utilities-system-monitor.png");
    }
}

void FenPrincipale::on_bouton_winsent_clicked() {
    QString test4;
    wol::send_wol("00:30:BD:B4:BF:37");
    QMessageBox::warning(this, "Putty", "CODE"+test4+"\n" );
    /*
    QProcess *process = new QProcess;

    QString chemin_executable(":/executables/winnosent/winnosent.exe");
    QFile file(chemin_executable);
    if(file.exists()) {
        maj_formulaire_action("WinSent", "Lancement de WinSent en cours.", 10,
                              ":/images/utilities-system-monitor.png");
        process->start(chemin_executable);
        if(process->state() == 1) {
            QMessageBox::warning(this, "WinSent", "1"
                                 ""+chemin_executable+"\n" );
        } else if(process->state() == 2) {
            QMessageBox::warning(this, "WinSent", "2"
                                 ""+chemin_executable+"\n" );
        }
        maj_formulaire_action("WinSent", "WinSent est lancé...",
                              100, ":/images/utilities-system-monitor.png");
    } else {
        QMessageBox::warning(this, "WinSent", "L'executable n'a pas été trouvé.\n"
                             "Vérifiez la présence du fichier : \n"+chemin_executable+"\n" );
    }*/
}


void FenPrincipale::about ()
{
    About *about = new About(ver, QVariant(QDate::currentDate().year()).toString());
    about->show();
}

void FenPrincipale::demarrage_automatique_activer ()
{
QSettings setting("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
setting.setValue(QString(NOM_LOGICIEL()), '"'+ QDir::convertSeparators(QCoreApplication::applicationFilePath()) +'"');
}
void FenPrincipale::demarrage_automatique_desactiver ()
{
QSettings setting("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
setting.remove(QString(NOM_LOGICIEL()));
}


