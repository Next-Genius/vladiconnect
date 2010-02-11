#include "FenPrincipale.h"
//Tout le code pour gérer l'import/export de la configuration


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
                m_liste.append(serveur(nom, dom_serveur_Element.attribute("ip"), dom_serveur_Element.attribute("mac"), dom_serveur_Element.attribute("sousreseau"), dom_serveur_Element.attribute("os"), dom_serveur_Element.attribute("utilisateur"), dom_serveur_Element.attribute("mdp")));
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
    enregistrerConfiguration("defaut");
    return true;
}


int FenPrincipale::enregistrerConfiguration(QString chemin_fichier) {   //vérifié 1
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
        dom_serveur.setAttribute("os",m_liste[i].getOs());
        dom_serveur.setAttribute("utilisateur",m_liste[i].getUtilisateur());
        dom_serveur.setAttribute("mdp",m_liste[i].getMdp());

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




