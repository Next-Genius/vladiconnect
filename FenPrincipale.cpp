#include "FenPrincipale.h"

FenPrincipale::FenPrincipale() {
    setupUi(this);
    this->setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/icone.png"));
    this->setWindowTitle(QString(NOM_LOGICIEL())+" - v"+QString::number(VERSION_LOGICIEL()));
    actionQuitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    //connect(actionQuitter, SIGNAL(hovered()), app, SLOT(quit()));
    //charger la liste des serveurs (vers QList<serveur> + copie des noms dans QListString
    //chargerConfiguration(QFile(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichier configuration (*.xml *.ini)")));
    chargerConfiguration("defaut");
    QSize taille_icone(30,30);
    bouton_editer->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/document-edit.png"));
    bouton_editer->setIconSize(taille_icone);
    os->addItem("Windows XP");
    os->addItem("Windows 7");
    os->addItem("Linux");
    bouton_serveur_valider_modifications->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/dialog-ok.png"));
    bouton_serveur_valider_modifications->setIconSize(taille_icone);

    bouton_supprimer_serveur->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/delete.png"));
    bouton_supprimer_serveur->setIconSize(taille_icone);
    QObject::connect(actionCharger_une_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_importer_clicked()));
    QObject::connect(actionSauver_la_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_exporter_clicked()));
    QObject::connect(actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    //QObject::connect(&processus, SIGNAL(finished(int, QProcess::ExitStatus )), this, SLOT(fin_processus(int,QProcess::ExitStatus)));



//définir fichier de conf courant pour pouvoir sauvegarder

}

int FenPrincipale::chargerConfiguration(QString chemin_fichier) {
    if(chemin_fichier == "defaut") {
        chemin_fichier = QCoreApplication::applicationDirPath() + "/configuration.xml";
    }

    QFile file(chemin_fichier);

    QDomDocument doc("Configuration" );

    if( !file.open( QIODevice::ReadOnly ) )
      return -1;

    if( !doc.setContent( &file ) )
    {
      file.close();
      return -2;
    }
    file.close();

    QDomElement dom_racine = doc.documentElement();
    if( dom_racine.tagName() != "racine" )
      return -3;

    if( dom_racine.attribute("nom") != "configuration" )
      return -4;

    QString Qversion = dom_racine.attribute("version");
    double version = Qversion.toDouble();
    if(version > VERSION_LOGICIEL()) {
        QMessageBox::warning(this, "Importation d'une configuration", "Le fichier de configuration est trop récent par rapport au programme executé. Mettez à jour"+QString(NOM_LOGICIEL())+"" );
    }

    m_liste.clear(); //clear du Qlist donnees
    liste_serveur->clear(); //clear du widget

    QDomNode dom_serveur_Node = dom_racine.firstChild();
    while( !dom_serveur_Node.isNull() )
    {
      QDomElement dom_serveur_Element = dom_serveur_Node.toElement();
      if( !dom_serveur_Element.isNull() )
      {
        if( dom_serveur_Element.tagName() == "serveur" )
        {
            QString nom = dom_serveur_Element.attribute("nom");
            m_liste.append(serveur(nom, dom_serveur_Element.attribute("ip"), dom_serveur_Element.attribute("mac"), dom_serveur_Element.attribute("sousreseau")));
           // serveur.out();

            //QMessageBox::information(this, "Contact", "m_liste : "+nom + "\n" );
        }
      }

      dom_serveur_Node = dom_serveur_Node.nextSibling();
    }

    //m_liste.append(serveur("Nouveau serveur", "ip", "AB CDE FGHI21554", "sousreseau54g"));

    //Transfert de QList vers le widget Vue MVC
    for(int i=0 ; i<m_liste.size() ; i++) {
        //QListWidgetItem item(m_liste[i].getNom());
        //item.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable);
        liste_serveur->addItem(m_liste[i].getNom());

    }


    for(int i=0 ; i<liste_serveur->count() ; i++) {
        //QListWidgetItem item(m_liste[i].getNom());
        //item.setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsUserCheckable);
        (*(liste_serveur->item(i))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
        int numero = ping(m_liste[i].getIp());
        if(ping(m_liste[i].getIp()) == true) {
            (*(liste_serveur->item(i))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
        }

    }


    //liste_serveur->sortItems();
    //liste_serveur->setSelection(QRect);
    liste_serveur->setCurrentRow(0); //sélectionne le 1er enregistrement
    EnregistrerConfiguration("defaut");
    return true;
}



int FenPrincipale::ping(QString ip, int parametre = 0) {
    static int numero = 0;
    QProcess *process = new QProcess;
    QString arguments;

    //Limiter à un ping
    if(ENVIRONNEMENT == 1) {    //Windows
        arguments="ping "+ip+" -n 1 -w 1";
    } else {
        arguments="ping "+ip+" -c 1 -w 1";   //Linux
    }

    process->start("ping "+ip+" -n 1 -w 1");
    process->setObjectName(QString::number(numero));
    process->setProperty("termine",false);
//    process->setProperty("numero",test);

    m_liste_processus.insert(numero,process);

    QObject::connect(m_liste_processus[numero], SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(fin_processus(int,QProcess::ExitStatus)));

    numero++;
    return numero;
}

int FenPrincipale::EnregistrerConfiguration(QString chemin_fichier) {   //vérifié 1
    if(chemin_fichier == "defaut") {
        chemin_fichier = QCoreApplication::applicationDirPath() + "/configuration.xml";
    }
    /*QDomImplementation impl = QDomDocument().implementation();
    // document with document type
    QString name = "Configuration";
    QString publicId = "-//XADECK//DTD Stone 1.0 //EN";
    QString systemId = "http://www-imagis.imag.fr/DTD/stone1.dtd";*/
    //QDomDocument doc("Configuration_vladiconnect");
    QDomDocument doc("");
    //QDomDocument doc(impl.createDocumentType(name,publicId,systemId));

    // add some XML comment at the beginning
    doc.appendChild(doc.createComment("Configuration "+QString(NOM_LOGICIEL())+" version "+QString::number(VERSION_LOGICIEL())+" "));
    doc.appendChild(doc.createComment("Créé le "+QDate::currentDate().toString()+"\nby #NOM_AUTEUR()"));
    doc.appendChild(doc.createTextNode("\n")); // for nicer output

    // root node
    QDomElement dom_racine = doc.createElement("racine");
    dom_racine.setAttribute("nom","configuration");
    dom_racine.setAttribute("version",QString::number(VERSION_LOGICIEL()));
    doc.appendChild(dom_racine);

    for(int i=0 ; i<m_liste.size() ; i++) {
        // serveur node
        QDomElement dom_serveur = doc.createElement("serveur");
        dom_serveur.setAttribute("nom",m_liste[i].getNom());
        dom_serveur.setAttribute("ip",m_liste[i].getIp());
        dom_serveur.setAttribute("mac",m_liste[i].getMac());
        dom_serveur.setAttribute("sousReseau",m_liste[i].getSousReseau());

        // decription node
        QDomElement dom_description = doc.createElement("decription");
        dom_description.appendChild(doc.createTextNode(m_liste[i].getDescription()));
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

int FenPrincipale::miseAJour_QList_vers_formulaire(int numero_serveur) {    //vérifié 1
    serveur_nom->setText(m_liste[numero_serveur].getNom());
    serveur_ip->setText(m_liste[numero_serveur].getIp());
    serveur_mac->setText(m_liste[numero_serveur].getMac());
    serveur_sousReseau->setText(m_liste[numero_serveur].getSousReseau());
    serveur_description->setText(m_liste[numero_serveur].getDescription());


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
    }
    action_progression->setValue(0);

    return 0;
}

int FenPrincipale::miseAJour_formulaire_vers_QList(int numero_serveur) {

    /*m_liste[i].setNom(serveur_nom->text());
    int j = liste_serveur->count();
    j++;
    liste_serveur->insertItem(j, "temp");
    liste_serveur->setCurrentRow(liste_serveur->count()+1);
    //liste_serveur->insertItem(i+1, "temp");
    liste_serveur->removeItemWidget(liste_serveur->currentItem());
    liste_serveur->insertItem(i, serveur_nom->text());
    liste_serveur->setCurrentRow(i);
    //liste_serveur->removeItemWidget(&QListWidgetItem("temp"));
    liste_serveur->deleteLater();
    //liste_serveur->sortItems();*/
    m_liste[numero_serveur].setIp(serveur_ip->text());
    m_liste[numero_serveur].setMac(serveur_mac->text());
    m_liste[numero_serveur].setSousReseau(serveur_sousReseau->text());
    m_liste[numero_serveur].setDescription(serveur_description->toPlainText());
    if(ping(m_liste[numero_serveur].getIp())==true) {
        //serveur connecté
        m_liste[numero_serveur].setConnecte(true);
    } else {
        m_liste[numero_serveur].setConnecte(false);
    }


   return 0;
}

void FenPrincipale::on_bouton_ping_clicked() {
    int avancement = 0;
    action_nom->setText("Vérification de connexion");
    action_etat->setText("Initialisation du ping");
    action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit.png"));
    action_progression->setValue(0);
    int nbreping = 3;


    for (int i=0 ; i<nbreping ; i++) {
        avancement = avancement + (100/nbreping);

        if(ping(serveur_ip->text()) == true) {
            action_progression->setValue(avancement);
        }
        action_etat->setText("Ping en cours");
    }

    int ligne = liste_serveur->currentRow();

    if(action_progression->value() > 70) {
        action_progression->setValue(100);
        action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
        (*(liste_serveur->item(ligne))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
        action_etat->setText("Ping terminé. Connecté");
        m_liste[ligne].setConnecte(true);
        bouton_demarrer->setEnabled(false);
        bouton_arreter->setEnabled(true);
        bouton_redemarrer->setEnabled(true);

    } else {
    action_progression->setValue(1);
    action_etat->setText("Ping terminé. Déconnecté");
    action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
    m_liste[ligne].setConnecte(false);
    (*(liste_serveur->item(ligne))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
        bouton_demarrer->setEnabled(true);
        bouton_arreter->setEnabled(false);
        bouton_redemarrer->setEnabled(false);

}

}


void FenPrincipale::on_bouton_arreter_clicked() {
    action_nom->setText("Arrêt à distance");
    action_etat->setText("Initialisation. Connexion en cours.");
    action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit.png"));
    action_progression->setValue(0);
    int nbre_lignes = m_liste.count();

    for (int i=0 ; i < nbre_lignes; i++) {
        QMessageBox::critical(this, "Déletion d'un serveur", "Rang du suivant n°"+QString::number(i)+" nom:"+m_liste[i].getNom());
      //  m_liste[i].out();
    }
    action_progression->setValue(50);
}

void FenPrincipale::on_bouton_editer_clicked() {    //validé
    serveur_nom->setEnabled(true);
    serveur_ip->setEnabled(true);
    serveur_mac->setEnabled(true);
    serveur_sousReseau->setEnabled(true);
    serveur_description->setEnabled(true);
    bouton_serveur_valider_modifications->setEnabled(true);
    bouton_editer->setEnabled(false);
    bouton_ping->setEnabled(false);
    bouton_demarrer->setEnabled(false);
    bouton_arreter->setEnabled(false);
    bouton_redemarrer->setEnabled(false);
}

void FenPrincipale::on_bouton_ajouter_serveur_clicked() {   //verifié 1
    QString nom;
    if((liste_serveur->findItems(QString("Nouveau serveur"),Qt::MatchExactly|Qt::MatchCaseSensitive)).size() != 0) {
        for(int i=1; i < (*liste_serveur).count() ;i++) {
            QString nombre;
            nombre.setNum(i);
            if((liste_serveur->findItems("Nouveau serveur (" + nombre + ")",Qt::MatchExactly|Qt::MatchCaseSensitive)).size() == 0) {
                nom = "Nouveau serveur ("+nombre+")";
                i = (*liste_serveur).count(); //liste_serveur->count();
            }
        }
    } else {
        nom = "Nouveau serveur";
    }

    m_liste.append(serveur(nom, "192.168..", "", "192.168.1.255"));
    QListWidgetItem item(nom);



    liste_serveur->addItem(nom);


    //modifie la sélection vers le nouvel élément + scroll vers le nouvel élément pour être sûr qu'il est visualisé
    int ligne = (*liste_serveur).count();
    ligne--;
    liste_serveur->setCurrentRow((ligne));
    (*(liste_serveur->item(ligne))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
    QObject::connect(bouton_ajouter_serveur, SIGNAL(clicked()), liste_serveur, SLOT(scrollToBottom()));
}

void FenPrincipale::on_bouton_supprimer_serveur_clicked() { //vérifié 1
    if(liste_serveur->count() < 1) {
        //pas d'item donc pas de suppression

    } else {
        QListWidgetItem *item_actuel;
        item_actuel = (*liste_serveur).currentItem();
        int ligne = liste_serveur->currentRow();

        //sélection du nouveau serveur courant pour après suppression
        if(liste_serveur->count() == 1)  {  //plus de serveur donc pas de sélection
            //on_bouton_ajouter_serveur_clicked();
        } else {
            if(liste_serveur->currentRow() == 0) {
              liste_serveur->setCurrentRow(0);    //sélection de la 1ere ligne (n°0)
             } else {
                 liste_serveur->setCurrentRow((liste_serveur->currentRow())-1); //sélection de la ligne précédénte
             }
        }

         //suppression dans la vue
         delete item_actuel;

         //suppression dans Qlist
         m_liste.removeAt((ligne));
         // QMessageBox::critical(this, "Déletion d'un serveur", "Une erreur s'est produite lors de la suppression du serveur sélectionné");
     }
}

void FenPrincipale::on_bouton_serveur_valider_modifications_clicked() { //validé
    serveur_nom->setEnabled(false);
    serveur_ip->setEnabled(false);
    serveur_mac->setEnabled(false);
    serveur_sousReseau->setEnabled(false);
    serveur_description->setEnabled(false);
    bouton_serveur_valider_modifications->setEnabled(false);
    miseAJour_formulaire_vers_QList(liste_serveur->currentRow());
    EnregistrerConfiguration("defaut");
    bouton_editer->setEnabled(true);
    bouton_ping->setEnabled(true);
}

void FenPrincipale::on_bouton_configuration_importer_clicked() {    //validé
    int reponse = QMessageBox::warning(this, "Chargement d'une nouvelle configuration",
"Êtes vous sûr de vouloir écraser l'ancienne configuration ?",
QMessageBox::Yes | QMessageBox::No);

    if(reponse == QMessageBox::Yes) {
        chargerConfiguration();
    }
}

void FenPrincipale::on_bouton_configuration_exporter_clicked() {    //vérifié1
    EnregistrerConfiguration();
}

void FenPrincipale::on_liste_serveur_itemSelectionChanged() {
    if(!m_liste.isEmpty()) {
        QString retour="1";
        QString contenu((liste_serveur->currentItem())->text());
        for(int i=0 ; i<m_liste.size() ; i++) {
            if(m_liste[i].getNom() == contenu) {
                if(ping(m_liste[i].getIp()) == true) {
                    m_liste[i].setConnecte(true);
                    action_etat->setText("Connecté");
                    action_nom->setText("Vérification de connexion");
                    action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
                    action_progression->setValue(100);
                    bouton_arreter->setEnabled(true);
                    bouton_redemarrer->setEnabled(true);
                    bouton_demarrer->setEnabled(false);
                } else {
                    m_liste[i].setConnecte(false);
                    bouton_arreter->setEnabled(false);
                    bouton_redemarrer->setEnabled(false);
                    bouton_demarrer->setEnabled(true);
                }
                bouton_serveur_valider_modifications->setEnabled(false);
                bouton_editer->setEnabled(true);

                if(miseAJour_QList_vers_formulaire(i) == 0)
                    retour = "0";

                i = m_liste.size(); //fin de la boucle
            }
        }
        if(retour != "0")
            QMessageBox::information(this, "Elément sélectionné", "ERREUR 212 retour="+retour+"###");

    }
}

void FenPrincipale::on_bouton_demarrer_clicked() {
    action_nom->setText("Démarrage à distance");
    action_etat->setText("");
    action_progression->setValue(0);
    QMessageBox::information(this, "Elément sélectionné", "Lancement démarrage");

    //QSocketUdp socket();

    QUdpSocket socket1();
    //socket.bind(QHostAdress("255.255.255.0"),9,QUdpSocket::ShareAddress);
    //connect(udpSocket, SIGNAL(readyRead()), socket, SLOT(readPendingDatagrams()));


        char chaine[6]; // Tableau de 6 char pour stocker S-a-l-u-t + le \0

        chaine[0] = 255;
        chaine[1] = 255;
        chaine[2] = 255;
        chaine[3] = 255;
        chaine[4] = 255;

        char chaine2[6]; // Tableau de 6 char pour stocker S-a-l-u-t + le \0

        chaine2[0] = 255;
        chaine2[1] = 255;
        chaine2[2] = 255;
        chaine2[3] = 255;
        chaine2[4] = 255;


        QByteArray paquet_mac;
        QDataStream out(&paquet_mac, QIODevice::WriteOnly);

        out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
        out << char(255); // On ajoute le message à la suite
        out << char(255);
        out << char(255);
        out << char(255);
        out << char(255);
        out.device()->seek(0); // On se replace au début du paquet
        out << (quint16) (paquet_mac.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
       /* QHostAdress adresse("255.255.255.0");
        socket1.writeDatagram(chaine, adresse,9);
        for(int i=0; i<16;i++) {
            socket1.writeDatagram(paquet_mac, adresse,9);
        }*/

}

int FenPrincipale::miseAJourItem() {    //vérifié 1
    if(m_liste.isEmpty())
        return true;

    //si pas d'Item, inutile de MAJ
    if((liste_serveur->selectedItems()).size() == 0)
        return true;

    //MAJ form->QList
    if(miseAJour_formulaire_vers_QList(liste_serveur->currentRow()) == 0)
        return true;
    //sinon
    return false;
}
/*
void FenPrincipale::chargement_arriere_plan_slot() {
    QMessageBox::critical(this, "Elément sélectionné", "Arrière plan");
}*/

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
        int numero = nom.toInt();
        if(exitCode == 0) {
           // m_liste[numero].setConnecte(true);
            //(*(liste_serveur->item(numero))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
            QMessageBox::information(this, "Ti","Ping n°"+QString::number(numero)+"\n Code :"+QString::number(monProcessus->exitCode())+"\nPC Allumé\nStatut :"+QString::number(monProcessus->exitStatus()));
        } else {
           // m_liste[numero].setConnecte(false);
            //(*(liste_serveur->item(numero))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
            QMessageBox::information(this, "Ti","Ping n°"+QString::number(numero)+"\n Code :"+QString::number(monProcessus->exitCode())+"\nPC Eteint\nStatut :"+QString::number(monProcessus->exitStatus())+"\nNbre processus :"+QString::number(m_liste_processus.count()));
        }
        //monProcessus->close();
        //QMessageBox::information(this, "Ti","Fin processus : \n"+QString::number(i)+"\nStatut :"+QString::number(statut));


    }
}

void FenPrincipale::on_bouton_maj_auto_clicked() {
    QMessageBox::information(this, "Ti","Repeat");
    int nombreServeurs = m_liste.count();
    for (int i=0; i<nombreServeurs; i++) {
        ping(m_liste[i].getIp());


    }




}

