#include "FenPrincipale.h"

FenPrincipale::FenPrincipale() {
    setupUi(this);
    this->setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/icone.png"));
    this->setWindowTitle(QString(NOM_LOGICIEL())+" - v"+QString::number(VERSION_LOGICIEL()));
    actionQuitter->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    //connect(actionQuitter, SIGNAL(hovered()), app, SLOT(quit()));
    //charger la liste des serveurs (vers QList<serveur> + copie des noms dans QListString
    chargerConfiguration("defaut");

    QSize taille_icone(30,30);
    bouton_editer->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/document-edit.png"));
    bouton_editer->setIconSize(taille_icone);

    serveur_os->addItem("Windows XP");
    serveur_os->addItem("Windows 7");
    serveur_os->addItem("Linux");

    bouton_serveur_valider_modifications->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/dialog-ok.png"));
    bouton_serveur_valider_modifications->setIconSize(taille_icone);

    bouton_supprimer_serveur->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/delete.png"));
    bouton_supprimer_serveur->setIconSize(taille_icone);

    QObject::connect(actionCharger_une_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_importer_clicked()));
    QObject::connect(actionSauver_la_configuration, SIGNAL(triggered()), this, SLOT(on_bouton_configuration_exporter_clicked()));
    QObject::connect(actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
}


void FenPrincipale::maj_formulaire_action(QString titre, QString etat, int progression, QString icone) {
    action_nom->setText(titre);
    action_etat->setText(etat);
    action_progression->setValue(progression);
    action_etat_pixmap->setPixmap(QPixmap(icone));
}

int FenPrincipale::miseAJour_QList_vers_formulaire(int numero_serveur) {    //vérifié 1
    serveur_nom->setText(m_liste[numero_serveur].getNom());
    serveur_ip->setText(m_liste[numero_serveur].getIp());
    serveur_mac->setText(m_liste[numero_serveur].getMac());
    serveur_sousReseau->setText(m_liste[numero_serveur].getSousReseau());
    serveur_description->setText(m_liste[numero_serveur].getDescription());
    serveur_os->setEditText(m_liste[numero_serveur].getOs());
    serveur_utilisateur->setText(m_liste[numero_serveur].getUtilisateur());
    serveur_mdp->setText(m_liste[numero_serveur].getMdp());

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
    return 0;
}

int FenPrincipale::miseAJour_formulaire_vers_QList(int numero_serveur) {
    m_liste[numero_serveur].setIp(serveur_ip->text());
    m_liste[numero_serveur].setMac(serveur_mac->text());
    m_liste[numero_serveur].setSousReseau(serveur_sousReseau->text());
    m_liste[numero_serveur].setDescription(serveur_description->toPlainText());
    m_liste[numero_serveur].setOs(serveur_os->currentText());
    m_liste[numero_serveur].setUtilisateur(serveur_utilisateur->text());
    m_liste[numero_serveur].setMdp(serveur_mdp->text());
    ping(m_liste[numero_serveur].getIp(), liste_serveur->currentRow());
    return 0;
}

void FenPrincipale::on_bouton_ping_clicked() {
    bouton_ping->setEnabled(false); //on désactive le ping temporairement
    maj_formulaire_action("Vérification de connexion", "Initialisation du ping", 10,
                          QCoreApplication::applicationDirPath() + "/images/network-transmit.png");
    ping(serveur_ip->text(), liste_serveur->currentRow(),1);
    action_etat->setText("Ping en cours");
    /*
    int ligne = liste_serveur->currentRow();

    if(action_progression->value() > 70) {
        //layout de action en cours mis à jour via signal de fin de QProcess
        (*(liste_serveur->item(ligne))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
        bouton_demarrer->setEnabled(false);
        bouton_arreter->setEnabled(true);
        bouton_redemarrer->setEnabled(true);

    } else {
        (*(liste_serveur->item(ligne))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
        bouton_demarrer->setEnabled(true);
        bouton_arreter->setEnabled(false);
        bouton_redemarrer->setEnabled(false);

    }*/

    bouton_ping->setEnabled(true); //on réactive le ping
}


void FenPrincipale::on_bouton_arreter_clicked() {
    maj_formulaire_action("Arrêt à distance", "Initialisation. Connexion en cours.", 5,
                          QCoreApplication::applicationDirPath() + "/images/network-transmit.png");

    /*
    int nbre_lignes = m_liste.count();
    for (int i=0 ; i < nbre_lignes; i++) {
        QMessageBox::critical(this, "Déletion d'un serveur", "Rang du suivant n°"+QString::number(i)+" nom:"+m_liste[i].getNom());

    }*/
    action_progression->setValue(50);
}

void FenPrincipale::on_bouton_editer_clicked() {    //validé
    liste_serveur->setEnabled(false);
    activer_formulaire(true);
}

void FenPrincipale::on_bouton_ajouter_serveur_clicked() {   //verifié 1
    QString nom;
    if((liste_serveur->findItems(QString("Nouveau serveur"),Qt::MatchExactly|Qt::MatchCaseSensitive)).size() != 0) {
        for(int i=1; i < (*liste_serveur).count()+1 ;i++) {
            if((liste_serveur->findItems("Nouveau serveur (" +QString::number(i)+ ")",Qt::MatchExactly|Qt::MatchCaseSensitive)).size() == 0) {
                nom = "Nouveau serveur ("+QString::number(i)+")";
                i = (*liste_serveur).count(); //liste_serveur->count();
            }
        }
    } else {
        nom = "Nouveau serveur";
    }

    m_liste.append(serveur(nom, "192.168..", "", "192.168.1.255", "Windows 7", "", ""));
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
        QMessageBox::critical(this, "Déletion d'un serveur", "Une erreur s'est produite lors de la suppression du serveur sélectionné : la liste est vide !");
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
        m_liste.removeAt(ligne);
    }
}

void FenPrincipale::on_bouton_serveur_valider_modifications_clicked() { //validé
    liste_serveur->setEnabled(true);
    activer_formulaire(false);
        //modifs du nom du serveur
        (liste_serveur->currentItem())->setText(serveur_nom->text());
        m_liste[liste_serveur->currentRow()].setNom(serveur_nom->text());
    miseAJour_formulaire_vers_QList(liste_serveur->currentRow());
    enregistrerConfiguration("defaut");
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
    enregistrerConfiguration();
}

void FenPrincipale::on_liste_serveur_itemSelectionChanged() {
    liste_serveur->setEnabled(true);
    if(!m_liste.isEmpty()) {
        QString retour="1";
        QString contenu((liste_serveur->currentItem())->text());
        for(int i=0 ; i<m_liste.size() ; i++) {
            if(m_liste[i].getNom() == contenu) {
                ping(m_liste[i].getIp(), i, 3);
                activer_formulaire(false);

                if(miseAJour_QList_vers_formulaire(i) == 0)
                    retour = "0";

                i = m_liste.size(); //fin de la boucle
            }
        }
        if(retour != "0") {
            QMessageBox::information(this, "Elément sélectionné", "Le changement de sélection de serveur a rencontré une erreur (l'item n'a pas été retrouvé).\nFermeture du programme");
            qApp->exit(-2); //fin de l'appli : 1er code de retour d'appli
        }
    }
}

void FenPrincipale::on_bouton_demarrer_clicked() {
    maj_formulaire_action("Démarrage à distance", "Lancement de la procédure.", 5, QCoreApplication::applicationDirPath() + "/images/network-offline.png");
    wol(serveur_sousReseau->text(), serveur_mac->text(), liste_serveur->currentRow(),0);
}

int FenPrincipale::miseAJourItem() {    //vérifié 1
    if(m_liste.isEmpty())
        return true;

    //si pas d'Item, inutile de MAJ
    if((liste_serveur->selectedItems()).size() == 0)
        return true;

    //MAJ form->QList
    if(miseAJour_formulaire_vers_QList(liste_serveur->currentRow()) == true)
        return true;
    //sinon
    return false;
}

void FenPrincipale::on_bouton_maj_auto_clicked() {
    //  QMessageBox::information(this, "Ti","Repeat");
    int nombreServeurs = m_liste.count();
    for (int i=0; i<nombreServeurs; i++) {
        //ping(m_liste[i].getIp());
        //inutile de ping pour le moment

    }
}

void FenPrincipale::activer_formulaire(bool activer) {
    //1ère partie du formaulaire
    serveur_nom->setEnabled(activer);
    serveur_ip->setEnabled(activer);
    serveur_mac->setEnabled(activer);
    serveur_sousReseau->setEnabled(activer);
    serveur_description->setEnabled(activer);
    //serveur_activerArret->setEnabled(activer);

    //liste_serveur -> pas de modifications

    /*
    bouton_demarrer->setEnabled(activer);
    bouton_redemarrer->setEnabled(activer);
    bouton_arreter->setEnabled(activer);*/
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
void FenPrincipale::on_serveur_activerArret_stateChanged(Qt::CheckState state) {
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
