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
//Tout le code pour gérer l'import/export de la configuration


int FenPrincipale::chargerConfiguration(QString chemin_fichier) {
	if(chemin_fichier == "defaut") {
		chemin_fichier = QCoreApplication::applicationDirPath() + "/configuration.xml";
	}

	statusBar()->showMessage("Chargement de la configuration...", 2000);

	QFile file(chemin_fichier);
	QDomDocument doc("Configuration");

	if( !file.open( QIODevice::ReadOnly ) )
		return -1;

	if( !doc.setContent( &file ) ) {
		file.close();
		return -2;
	}

	file.close();

	QDomElement dom_racine = doc.documentElement();
	if( dom_racine.tagName() != "racine" )
		return -3;

	if( dom_racine.attribute("nom") != "configuration" )
		return -4;

	double version = dom_racine.attribute("version").toDouble();
	if(version > VERSION_LOGICIEL()) {
		QMessageBox::warning(this, "Importation d'une configuration",
							 "Le fichier de configuration est trop récent par"
							 "rapport au programme executé.\n"
							 "Mettez à jour "+QString(NOM_LOGICIEL())+" vers la version "+version+" !");
	}

	serverModel->clear(); //clear du widget
	QDomNode dom_serveur_Node = dom_racine.firstChild();
	while(!dom_serveur_Node.isNull()) {
		QDomElement dom_serveur_Element = dom_serveur_Node.toElement();
		if( !dom_serveur_Element.isNull() ) {
			if(dom_serveur_Element.tagName() == "serveur" ) {
				Server* myServer = new Server(serverModel);
				myServer->setName(dom_serveur_Element.attribute("nom"));
				myServer->setIp(dom_serveur_Element.attribute("ip"));
				myServer->setMac(dom_serveur_Element.attribute("mac"));
				myServer->setSubnetmask(dom_serveur_Element.attribute("sousreseau"));

				if(dom_serveur_Element.hasChildNodes()) {
					myServer->setDescription(dom_serveur_Element.firstChild().toElement().text());
				} else {
					myServer->setDescription("Pas de description");
				}

				myServer->setOsFromString(dom_serveur_Element.attribute("os"));
				myServer->setUser(dom_serveur_Element.attribute("utilisateur"));
				myServer->setPassword(cryptage::decrypte(dom_serveur_Element.attribute("mdp"), "Cle")); //décryptage

				myServer->setOff();
				myServer->ping();
				serverModel->addItem(myServer);
				QObject::connect(myServer, SIGNAL(error(QString)), this, SLOT(printMessage(QString)));
				QObject::connect(myServer, SIGNAL(output(QString)), this, SLOT(printConsoleMessage(QString)));

			}
		}

		dom_serveur_Node = dom_serveur_Node.nextSibling();
	}

	serverModel->setCurrentRow(0); //sélectionne le 1er enregistrement

	return true;
}

int FenPrincipale::enregistrerConfiguration(QString chemin_fichier) {
	if(chemin_fichier == "defaut") {
		chemin_fichier = QCoreApplication::applicationDirPath() + "/configuration.xml";
		statusBar()->showMessage("Enregistrement de la configuration...", 2000);
	}

	QDomDocument doc("");

	doc.appendChild(doc.createComment("Configuration "+QString(NOM_LOGICIEL())
									  +" version "+QString::number(VERSION_LOGICIEL())+" \n "
									  +"Créé le "+QDate::currentDate().toString()+"\n par "+NOM_AUTEUR()
									  +"\n Ce document est au format \"xml\". "));
	doc.appendChild(doc.createTextNode("\n")); // for nicer output

	// root node
	QDomElement dom_racine = doc.createElement("racine");
	dom_racine.setAttribute("nom","configuration");
	dom_racine.setAttribute("version",QString::number(VERSION_LOGICIEL()));
	doc.appendChild(dom_racine);

	for(int i=0 ; i<serverModel->count() ; i++) {
		// serveur node
		Server* myServer = dynamic_cast<Server*> (this->serverModel->item(i));
		QDomElement dom_serveur = doc.createElement("serveur");
		dom_serveur.setAttribute("nom",myServer->getName());
		dom_serveur.setAttribute("ip",myServer->getIp());
		dom_serveur.setAttribute("mac",myServer->getMac());
		dom_serveur.setAttribute("sousReseau",myServer->getSubnetmask());
		dom_serveur.setAttribute("os",myServer->getOsToString());
		dom_serveur.setAttribute("utilisateur",myServer->getUser());
		dom_serveur.setAttribute("mdp",cryptage::crypte(myServer->getPassword(),"Cle")); //enregistrement avec cryptage clé : Cle


		// decription node
		QDomElement dom_description = doc.createElement("description");
		dom_description.appendChild(doc.createTextNode(myServer->getDescription()));
		dom_serveur.appendChild(dom_description);
		dom_racine.appendChild(dom_serveur);
	}


	QFile fichier_sauvegarde(chemin_fichier);
	if (fichier_sauvegarde.open(QFile::WriteOnly)) {
		QTextStream out(&fichier_sauvegarde);
		out << doc.toString();
		return true;
	} else return false;
}




