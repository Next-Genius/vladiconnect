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

FenPrincipale::FenPrincipale(QSettings * s, QApplication* app) {
	this->app = app;

	this->putty_process = NULL;
	this->processCommandLineArguments();

	setupUi(this);
	setWindowIcon(QIcon(":/images/icone.png"));
	setWindowTitle(QString(NOM_LOGICIEL())+" - v"+QString::number(VERSION_LOGICIEL()));

	f_ver = VERSION_LOGICIEL();
	ver = "0.511";

	if (tr("LTR") == "RTL") {
		qApp->setLayoutDirection(Qt::RightToLeft);
	}

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
	this->trayIcon->show();

	this->run_hidden = false;

	QObject::connect(this->serverModel, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
					 this, SLOT(selectedServerChanged(QListWidgetItem*, QListWidgetItem*)));

	//charger la liste des serveurs vers QList<serveur> + copie des noms dans QListString
	this->chargerConfiguration("defaut");
	this->activer_formulaire(false);

	//barre état
	QLabel *progression = new QLabel("Prêt");
	this->statusBar()->addWidget(progression);

	QSize taille_icone(30,30);
	this->bouton_editer->setIcon(QIcon(":/images/document-edit.png"));
	this->bouton_editer->setIconSize(taille_icone);

	//QSystemTrayIcon *trayIcon = new QSystemTrayIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/document-edit.png"));
	this->trayIcon->showMessage("Vladiconnect", tr("Vladiconnect est démarré"));

	this->bouton_serveur_valider_modifications->setIcon(QIcon(":/images/dialog-ok.png"));
	this->bouton_serveur_valider_modifications->setIconSize(taille_icone);

	this->bouton_supprimer_serveur->setIcon(QIcon(":/images/delete.png"));
	this->bouton_supprimer_serveur->setIconSize(taille_icone);

	this->connect(actionCharger_une_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_importer_clicked()));
	this->connect(actionSauver_la_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_exporter_clicked()));
	this->connect(actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
	this->connect(actionAbout, SIGNAL(triggered()), this, SLOT(about()));
	this->connect(actionRun_hidden, SIGNAL(toggled(bool)), this, SLOT(setRunHidden(bool)));

	this->sync_settings = s;
	this->readSettings();

	this->initialisation_executables();

	//Receiver for the chat interface
	this->chatReceiver = new Receiver(PORT, this);
	QObject::connect(this->chatReceiver, SIGNAL(receivedMessage(QString)),
					 this, SLOT(printMessage(QString)));


}


void FenPrincipale::maj_formulaire_action(QString titre, QString etat, int progression, QString icone) {
	this->action_nom->setText(titre);
	this->action_etat->setText(etat);
	this->action_progression->setValue(progression);
	this->action_etat_pixmap->setPixmap(QPixmap(icone));
	this->trayIcon->showMessage(titre, etat);
}
void FenPrincipale::initialisation_executables() {
	/*QMessageBox::critical(this, "vérification de l'intégrité du logiciel",
		 "Une erreur s'est produite lors du démarrage du logiciel.<br> "
		 "Certains fichiers nécessaires au logiciels sont absents :<br>"
		 "test.exe");*/
	QString chemin_executable(
			QCoreApplication::applicationDirPath()+"/putty.exe");
	QFile file(chemin_executable);
	if(!file.exists()) {
		QMessageBox::critical(this, "Putty",
							  "L'executable qui permet le contrôle"
							  " à distance n'a pas été trouvé.\n Vérifiez la "
							  "présence du fichier : \n"+chemin_executable+"\n"
							  );
		//return -2;
	}

}

int FenPrincipale::miseAJour_QList_vers_formulaire(Server* myServer) {
	if(myServer == NULL) {
		return false;
	}
	serveur_nom->setText(myServer->getName());
	serveur_ip->setText(myServer->getIp());
	serveur_mac->setText(myServer->getMac());
	serveur_sousReseau->setText(myServer->getSubnetmask());
	serveur_description->setText(myServer->getDescription());

	if(myServer->getOsToString() == "Windows 7") {
		serveur_os->setCurrentIndex(1);
	} else if (myServer->getOsToString() == "Windows XP") {
		serveur_os->setCurrentIndex(0);
	} else if (myServer->getOsToString() == "Linux") {
		serveur_os->setCurrentIndex(2);
	} else {    //Autre
		serveur_os->setCurrentIndex(3);
	}

	serveur_utilisateur->setText(myServer->getUser());
	serveur_mdp->setText(myServer->getPassword());

	return true;
}

int FenPrincipale::miseAJour_formulaire_vers_QList(Server* myServer) {

	myServer->setName(serveur_nom->text());
	myServer->setIp(serveur_ip->text());
	myServer->setMac(serveur_mac->text());
	myServer->setSubnetmask(serveur_sousReseau->text());
	myServer->setDescription(serveur_description->toPlainText());
	myServer->setOsFromString(serveur_os->currentText());
	myServer->setUser(serveur_utilisateur->text());
	myServer->setPassword(serveur_mdp->text());


	myServer->ping();

	return 0;
}

void FenPrincipale::on_bouton_ping_clicked() {
	this->bouton_ping->setEnabled(false); //on désactive le ping temporairement

	Server* myServer = dynamic_cast<Server*> (this->serverModel->currentItem());

	this->printMessage(tr("Ping on %1").arg(myServer->getIp()));
	myServer->ping();

	this->bouton_ping->setEnabled(true); //on réactive le bouton ping
}



void FenPrincipale::on_bouton_ajouter_serveur_clicked() {
	QString nom;
	if((serverModel->findItems(QString("Nouveau serveur"),
								 Qt::MatchExactly|Qt::MatchCaseSensitive)).size() != 0) {
		for(int i=1; i < serverModel->count()+1 ;i++) {
			if((serverModel->findItems("Nouveau serveur (" +QString::number(i)+ ")",
										 Qt::MatchExactly|Qt::MatchCaseSensitive)).size() == 0) {
				nom = "Nouveau serveur ("+QString::number(i)+")";
				i = serverModel->count(); //serverModel->count();
			}
		}
	} else {
		nom = "Nouveau serveur";
	}

	Server* item2 = new Server(serverModel);

	item2->setName(nom);
	item2->setIp("192.168..");
	item2->setMac("");
	item2->setSubnetmask("192.168.1.255");
	item2->setDescription("Pas de description");
	item2->setOsFromString("Linux");
	item2->setOff();
	serverModel->addItem(item2);

	//modifie la sélection vers le nouvel élément + scroll vers le nouvel élément pour être sûr qu'il est visualisé
	int ligne = serverModel->count();
	ligne--;

	serverModel->setCurrentRow(ligne);
	QObject::connect(bouton_ajouter_serveur, SIGNAL(clicked()), serverModel, SLOT(scrollToBottom()));

	//active les boutons de suppression au cas où ils auraient été désactivé dans le cas où plus de serveur.
	bouton_supprimer_serveur->setEnabled(true);
	bouton_supprimer_serveur2->setEnabled(true);
}

void FenPrincipale::on_bouton_supprimer_serveur_clicked() { //vérifié 1
	if(serverModel->count() < 1) {
		//pas d'item donc pas de suppression
		QMessageBox::critical(this, "Déletion d'un serveur",
							  "Une erreur s'est produite lors de la suppression "
							  "du serveur sélectionné : la liste est vide !");

	} else {

		//pointeur vers l'item actuel
		Server* item_actuel =  dynamic_cast<Server*> (serverModel->currentItem());

		//sélection du nouveau serveur courant pour après suppression
		if(serverModel->count() == 1)  {  //plus de serveur donc pas de sélection
			bouton_supprimer_serveur->setEnabled(false);
			bouton_supprimer_serveur2->setEnabled(false);
		} else {
			if(serverModel->currentRow() == 0) {
				serverModel->setCurrentRow(0);    //sélection de la 1ere ligne (n°0)
			} else {
				//sélection de la ligne précédénte
				serverModel->setCurrentRow((serverModel->currentRow())-1);
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
	serverModel->sortItems(Qt::AscendingOrder);
}

void FenPrincipale::on_bouton_editer_clicked() {
	serverModel->setEnabled(false);
	activer_formulaire(true);
}

void FenPrincipale::on_bouton_serveur_valider_modifications_clicked() {
	serverModel->setEnabled(true);
	activer_formulaire(false);
	Server* myServer  = dynamic_cast<Server*> (serverModel->currentItem());

	miseAJour_formulaire_vers_QList(myServer);
	enregistrerConfiguration("defaut");

}

void FenPrincipale::on_bouton_configuration_importer_clicked() {
	int reponse = QMessageBox::warning(this, tr("Chargement d'une nouvelle configuration"),
									   tr("Êtes vous sûr de vouloir écraser l'ancienne configuration ?"),
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
//	maj_formulaire_action("Démarrage à distance", "Lancement de la procédure.",
//						  5, ":/images/network-offline.png");
	Server* myServer  = dynamic_cast<Server*> (this->serverModel->currentItem());
	myServer->start();
}

void FenPrincipale::on_bouton_redemarrer_clicked() {
//	maj_formulaire_action("Redémarrage à distance", "Lancement de la procédure.",
//						  5, ":/images/network-offline.png");
	Server* myServer  = dynamic_cast<Server*> (this->serverModel->currentItem());
	myServer->restart();
}


void FenPrincipale::on_bouton_arreter_clicked() {
//	maj_formulaire_action("Arrêt à distance", "Initialisation. Connexion en cours.", 0,
//						  ":/images/network-transmit.png");
	Server* myServer  = dynamic_cast<Server*> (this->serverModel->currentItem());
	myServer->shutdown();
}

void FenPrincipale::selectedServerChanged(QListWidgetItem* current, QListWidgetItem* previous) {
	Server* myPreviousServer  = dynamic_cast<Server*> (previous);
	Server* myCurrentServer = dynamic_cast<Server*> (current);

	if(myPreviousServer != NULL) {
		miseAJour_formulaire_vers_QList(myPreviousServer);
		enregistrerConfiguration("defaut");

		//this->miseAJour_formulaire_vers_QList(myPreviousServer->getId());
	}

	serverModel->setEnabled(true);

	myCurrentServer->ping();

	activer_formulaire(false);
	miseAJour_QList_vers_formulaire(myCurrentServer);
}


int FenPrincipale::miseAJourItem() {
	if(serverModel->count()!=0) //si pas d'Item, inutile de MAJ
		return true;

	//si pas de sélection, inutile aussi
	if((serverModel->selectedItems()).size() == 0)
		return true;

	Server* myCurrentServer = dynamic_cast<Server*> (this->serverModel->currentItem());

	//MAJ form->QList
	return miseAJour_formulaire_vers_QList(myCurrentServer);
}

void FenPrincipale::on_bouton_maj_auto_clicked() {
	Server* myServer = NULL;
	for (int i=0; i<serverModel->count(); i++) {
		myServer = dynamic_cast<Server*> (serverModel->item(i));
		myServer->ping();
	}
	this->printMessage(tr("Servers states have been updated !"));
//	maj_formulaire_action(tr("Mise à jour des serveur"), tr("Les états des serveurs ont été mis à jour !"), 100,
//						  ":/images/utilities-system-monitor.png");
}

void FenPrincipale::activer_formulaire(bool activer) {
	//1ère partie du formulaire
	//serveur_nom->setEnabled(activer);
	//serveur_ip->setEnabled(activer);
	//serveur_mac->setEnabled(activer);
	//serveur_sousReseau->setEnabled(activer);
	//serveur_description->setEnabled(activer);
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

/*	if(activer == false) {
		bouton_demarrer->setEnabled(activer);
		bouton_redemarrer->setEnabled(activer);
		bouton_arreter->setEnabled(activer);
	}*/
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

	Server* myServer = dynamic_cast<Server*> (this->serverModel->currentItem());
	myServer->execute(this->serveur_commande->toPlainText());

//	maj_formulaire_action("Execution à distance", "Procédure lancée.", 10,
//			  ":/images/utilities-system-monitor.png");
}

void FenPrincipale::on_bouton_stop_processus_clicked() {
	Server* myServer = dynamic_cast<Server*> (this->serverModel->currentItem());
	myServer->stopProcessus();

//	maj_formulaire_action("Execution à distance", "Procéssus arrêté", 10,
//			  ":/images/utilities-system-monitor.png");
}

void FenPrincipale::on_bouton_open_putty_clicked() {
	QProcess *putty_process = new QProcess;

	QString chemin_executable(QCoreApplication::applicationDirPath()+"/putty.exe");
	QFile file(chemin_executable);
	if(file.exists()) {
//		maj_formulaire_action("Putty", "Lancement de Putty en cours.", 10,
//							  ":/images/utilities-system-monitor.png");
		putty_process->start(chemin_executable);
//		maj_formulaire_action("Lancement de Putty", "Putty est lancé.",
//							  100, ":/images/utilities-system-monitor.png");
	} else {
		QMessageBox::warning(this, "Putty", "L'executable n'a pas été trouvé.\n"
							 "Vérifiez la présence du fichier : \n"+chemin_executable+"\n" );
	}
	this->printMessage(tr("Putty is loaded !"));
}

void FenPrincipale::on_bouton_close_putty_clicked() {
	if(putty_process == NULL || putty_process->state() == QProcess::NotRunning) {
		this->printMessage(tr("Putty was already stopped."));
		//QMessageBox::warning(this, "Putty", tr("Putty was already stopped."));
	} else {
		putty_process->kill();
		this->printMessage(tr("Putty has been stopped."));
//		maj_formulaire_action("Putty", tr("Putty has been stopped."), 10,
//							  ":/images/utilities-system-monitor.png");
	}
	putty_process = NULL;
}


void FenPrincipale::on_bouton_send_message_clicked() {
	Sender mySender(PORT, this);
	mySender.sendMessage(this->serveur_commande->toPlainText());
}

void FenPrincipale::about() {
	About *about = new About(ver, QVariant(QDate::currentDate().year()).toString());
	about->show();
}

void FenPrincipale::demarrage_automatique_activer() {
	QSettings setting("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	setting.setValue(QString(NOM_LOGICIEL()), '"'+ QDir::convertSeparators(QCoreApplication::applicationFilePath()) +'"');
}

void FenPrincipale::demarrage_automatique_desactiver() {
	QSettings setting("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	setting.remove(QString(NOM_LOGICIEL()));
}

void FenPrincipale::processCommandLineArguments() {
	if(this->app == NULL) {
		return;
	}

	int argc = app->argc();
	char** argv = app->argv();

	for(int i = 0;i < argc; i++) {
		if(QString(argv[i]) == QString("-m") && i < argc) {
			Sender mySender(PORT, this);
			mySender.sendMessage(QString(argv[i+1]));
		}
	}

}

void FenPrincipale::printConsoleMessage(QString message) {
	this->console->setPlainText(this->console->toPlainText() + message + "\n");
}
