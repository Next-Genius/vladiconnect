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

int FenPrincipale::chargerConfiguration(QString chemin_fichier) {
    if(chemin_fichier == "defaut") {
        chemin_fichier = QCoreApplication::applicationDirPath() + "/configuration.xml";
    }

    QFile file(chemin_fichier);
    QDomDocument doc("Configuration" );

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

    QString Qversion = dom_racine.attribute("version");
    double version = Qversion.toDouble();
    if(version > VERSION_LOGICIEL()) {
        QMessageBox::warning(this, "Importation d'une configuration", "Le fichier de configuration est trop récent par rapport au programme executé. Mettez à jour"+QString(NOM_LOGICIEL())+"" );
    }

    m_liste.clear(); //clear du Qlist donnees
    liste_serveur->clear(); //clear du widget
    QDomNode dom_serveur_Node = dom_racine.firstChild();
    while(!dom_serveur_Node.isNull()) {
        QDomElement dom_serveur_Element = dom_serveur_Node.toElement();
        if( !dom_serveur_Element.isNull() ) {
            if(dom_serveur_Element.tagName() == "serveur" ) {
                QString nom = dom_serveur_Element.attribute("nom");
                m_liste.append(serveur(nom, dom_serveur_Element.attribute("ip"), dom_serveur_Element.attribute("mac"), dom_serveur_Element.attribute("sousreseau")));
            }
        }

        dom_serveur_Node = dom_serveur_Node.nextSibling();
    }

    //Transfert de QList vers le widget Vue MVC
    for(int i=0 ; i<m_liste.size() ; i++) {
        liste_serveur->addItem(m_liste[i].getNom());
    }

    for(int i=0 ; i<liste_serveur->count() ; i++) {
        (*(liste_serveur->item(i))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
        ping(m_liste[i].getIp(), i, 2); //i au lieu de numero_m_liste
    }

    //liste_serveur->sortItems();
    liste_serveur->setCurrentRow(0); //sélectionne le 1er enregistrement
    EnregistrerConfiguration("defaut");
    return true;
}

int FenPrincipale::ping(QString ip, int numero_m_liste, int parametre) {
    static int numero_ping = 0;
    QProcess *process = new QProcess;
    QString arguments;

    //Limiter à un ping
    if(ENVIRONNEMENT == 1) {    //Windows
        arguments="ping "+ip+" -n 1 -w 1";
    } else {
        arguments="ping "+ip+" -c 1 -w 1";   //Linux
    }

    process->start("ping "+ip+" -n 1 -w 1");
    process->setObjectName(QString::number(numero_ping));
    process->setProperty("termine",false);
    process->setProperty("parametre",parametre);
    process->setProperty("numero_m_liste", numero_m_liste);

    m_liste_processus.insert(numero_ping,process);

    QObject::connect(m_liste_processus[numero_ping], SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(fin_processus(int,QProcess::ExitStatus)));

    numero_ping++;
    return numero_ping;
}

void FenPrincipale::maj_formulaire_action(QString titre, QString etat, int progression, QString icone) {
    action_nom->setText(titre);
    action_etat->setText(etat);
    action_progression->setValue(progression);
    action_etat_pixmap->setPixmap(QPixmap(icone));
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
    doc.appendChild(doc.createComment("Configuration "+QString(NOM_LOGICIEL())+" version "+QString::number(VERSION_LOGICIEL())+" \n "
                                      +"Créé le "+QDate::currentDate().toString()+"\n par "+NOM_AUTEUR()
                                      +"\n Ce document est au format \"xml\". "));
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
    return 0;
}

int FenPrincipale::miseAJour_formulaire_vers_QList(int numero_serveur) {
    m_liste[numero_serveur].setIp(serveur_ip->text());
    m_liste[numero_serveur].setMac(serveur_mac->text());
    m_liste[numero_serveur].setSousReseau(serveur_sousReseau->text());
    m_liste[numero_serveur].setDescription(serveur_description->toPlainText());
    ping(m_liste[numero_serveur].getIp(), liste_serveur->currentRow());
    return 0;
}

void FenPrincipale::on_bouton_ping_clicked() {
    bouton_ping->setEnabled(false); //on désactive le ping temporairement
    int avancement = 0;
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
    liste_serveur->setEnabled(true);
    if(!m_liste.isEmpty()) {
        QString retour="1";
        QString contenu((liste_serveur->currentItem())->text());
        for(int i=0 ; i<m_liste.size() ; i++) {
            if(m_liste[i].getNom() == contenu) {
                ping(m_liste[i].getIp(), i, 3);
                /*
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
                */
                activer_formulaire(false);

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
    maj_formulaire_action("Démarrage à distance", "Lancement de la procédure.", 5, QCoreApplication::applicationDirPath() + "/images/network-offline.png");
    QMessageBox::information(this, "Elément sélectionné", "Lancement démarrage");
    QUdpSocket socket1;
    //socket.bind(QHostAdress("255.255.255.0"),9,QUdpSocket::ShareAddress);
    //connect(udpSocket, SIGNAL(readyRead()), socket, SLOT(readPendingDatagrams()));
    /*

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
        chaine2[4] = 255;*/

    //    char chaine3[13] = "0016EAC06C5A";

    char chaine3[13] = "012345678901";
    /*QByteArray paquet_mac(chaine3);
        QDataStream out(&paquet_mac, QIODevice::WriteOnly);

        out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
        out << char(255); // On ajoute le message à la suite
        out << char(255);
        out << char(255);
        out << char(255);
        out << char(255);

        ffffffffffff0016eac06c5a0800450000820a4d00008011abc8c0a80106c0a801ffd8cf0009006ea1e3ffffffffffff000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
        1787	617.640852	192.168.1.6	192.168.1.255	WOL	MagicPacket for 00:00:00_00:00:00 (00:00:00:00:00:00)
lZE
Nn

ffffffffffff
0016eac06c5a
080045000082
0d2300008011
a8f2c0a80106c0a801ffe3db0009006e23c2ffffffffffff0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a
*/

    // Préparation du paquet1

    QByteArray paquet;
    paquet.fromHex("FFFFFFFFFF");

    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << chaine3; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    QHostAddress adresse("192.168.1.255");
    //socket1.writeDatagram(chaine, adresse,9);


    socket1.writeDatagram(paquet, adresse, 9);

    // Préparation du paquet2
    QByteArray paquet2;
    paquet2.fromHex("000000000000");
    /*
        QDataStream out2(&paquet2, QIODevice::WriteOnly);

        out2 << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
        out2 << "0016EAC06C5A"; // On ajoute le message à la suite

        out2.device()->seek(0); // On se replace au début du paquet
        out2 << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
*/


    /*



        out.device()->seek(0); // On se replac  au début du paquet
        out << (quint16) (paquet_mac.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message*/
QByteArray test;
test = "123456789000";
        for(int i=0; i<16;i++) {
            test += "0123456789000";
        }
        /*
ffffffffffff0016eac06c5a0800450000820a0d00008011ac08c0a80106c0a801fff4880009006e1315ffffffffffff0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a0016eac06c5a
908	88.386137	192.168.1.6	192.168.1.255	WOL	MagicPacket for Intel_c0:6c:5a (00:16:ea:c0:6c:5a)
0000   ff ff ff ff ff ff 00 16 ea c0 6c 5a 08 00 45 00  ..........lZ..E.
0010   00 82 0a 0d 00 00 80 11 ac 08 c0 a8 01 06 c0 a8  ................
0020   01 ff f4 88 00 09 00 6e 13 15 ff ff ff ff ff ff  .......n........
0030   00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0  ....lZ....lZ....
0040   6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16  lZ....lZ....lZ..
0050   ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a  ..lZ....lZ....lZ
0060   00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0  ....lZ....lZ....
0070   6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16  lZ....lZ....lZ..
0080   ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a                                                  ..lZ....lZ....lZ
0000   ff ff ff ff ff ff 00 16 ea c0 6c 5a 08 00 45 00
0010   00 82 0a 0d 00 00 80 11 ac 08 c0 a8 01 06 c0 a8
0020   01 ff f4 88 00 09 00 6e 13 15 ff ff ff ff ff ff
0030   00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0
0040   6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16
0050   ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a
0060   00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0
0070   6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a 00 16
0080   ea c0 6c 5a 00 16 ea c0 6c 5a 00 16 ea c0 6c 5a*/
    bool ok;
    QByteArray temp;
    /*
    temp = QByteArray::toInt(&ok, "0123456789000");
    socket1.writeDatagram(temp, adresse,9);
    */
    QByteArray donnees;
    //donnees = QString(QByteArray::fromHex(QDataStream::readBytes(&out, 200)));
    socket1.writeDatagram("0000000000", adresse, 9);

    QString louis;
    //test en hexa
    //louis = test.toInt(&ok, 2);


    //QMessageBox(this, "test", "Contenu : "+louis.data()); //en *char
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
        int numero_m_liste = monProcessus->property("numero_m_liste").toInt();
        int parametre = monProcessus->property("parametre").toInt();
        if(exitCode == 0) {
            m_liste[numero_m_liste].setConnecte(true);
            (*(liste_serveur->item(numero_m_liste))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
            //QMessageBox::information(this, "Ti","Ping n°"+QString::number(numero)+"\n Numero m_liste :"+QString::number(numero_m_liste)+" \nCode :"+QString::number(monProcessus->exitCode())+"\nPC Allumé");
            if(parametre == 1) {
                //mise en forme des données pour le fomulaire
                maj_formulaire_action("Connexion", "Ping terminé. Machine connectée", 100, QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png");
            } else if(parametre == 2 && numero_m_liste !=0) {

            } else if(parametre == 3 && numero_m_liste !=0) {
                m_liste[numero_m_liste].setConnecte(true);
                action_etat->setText("Connecté");
                action_nom->setText("Vérification de connexion");
                action_etat_pixmap->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/network-transmit-receive.png"));
                action_progression->setValue(100);
                bouton_arreter->setEnabled(true);
                bouton_redemarrer->setEnabled(true);
                bouton_demarrer->setEnabled(false);
            }

        } else {
            m_liste[numero_m_liste].setConnecte(false);
            (*(liste_serveur->item(numero_m_liste))).setIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/network-offline.png"));
            //QMessageBox::information(this, "Ti","Ping n°"+QString::number(numero)+"\n Numero m_liste :"+QString::number(numero_m_liste)+"\nCode :"+QString::number(monProcessus->exitCode())+"\nPC Eteint\nStatut :"+QString::number(monProcessus->exitStatus())+"\nNbre processus :"+QString::number(m_liste_processus.count()));
            if(parametre == 1) {
                //mise en forme des données pour le fomulaire
                maj_formulaire_action("Connexion", "Ping terminé. Machine déconnectée", 1, QCoreApplication::applicationDirPath() + "/images/network-offline.png");
            } else if(parametre == 3 && numero_m_liste !=0) {
                bouton_arreter->setEnabled(false);
                bouton_redemarrer->setEnabled(false);
                bouton_demarrer->setEnabled(true);
            }
        }
        monProcessus->close();
    }
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
    serveur_activerArret->setEnabled(activer);

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
    bool etat;
    if(state == Qt::Checked) {
        etat = true;
    } else {
        etat = false;
    }
    serveur_os->setEnabled(etat);
    serveur_utilisateur->setEnabled(etat);
    serveur_mdp->setEnabled(etat);
}
