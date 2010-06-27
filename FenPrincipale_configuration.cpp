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

    liste_serveur->clear(); //clear du widget
    QDomNode dom_serveur_Node = dom_racine.firstChild();
    while(!dom_serveur_Node.isNull()) {
        QDomElement dom_serveur_Element = dom_serveur_Node.toElement();
        if( !dom_serveur_Element.isNull() ) {
            if(dom_serveur_Element.tagName() == "serveur" ) {
                QListWidgetItem *item2 = new QListWidgetItem(liste_serveur);
                item2->setText(dom_serveur_Element.attribute("nom"));
                item2->setData(100, dom_serveur_Element.attribute("ip"));
                item2->setData(200, dom_serveur_Element.attribute("mac"));
                item2->setData(300, dom_serveur_Element.attribute("sousreseau"));
                if(dom_serveur_Element.hasChildNodes()) {
                    item2->setData(400, "A"+dom_serveur_Element.firstChildElement().toText().data());
                } else {
                    item2->setData(400, "Pas de description");
                }

                item2->setData(600, dom_serveur_Element.attribute("os"));
                item2->setData(700, dom_serveur_Element.attribute("utilisateur"));
                item2->setData(800, dom_serveur_Element.attribute("mdp"));

                item2->setIcon(QIcon(":/images/network-offline.png"));
                liste_serveur->addItem(item2);

                int i;
                i = liste_serveur->count();

                //ping(liste_serveur->item(i)->data(100).toString(), i, 2);

            }
        }

        dom_serveur_Node = dom_serveur_Node.nextSibling();
    }

    liste_serveur->setCurrentRow(0); //sélectionne le 1er enregistrement
    return true;
}

int FenPrincipale::enregistrerConfiguration(QString chemin_fichier) {
    if(chemin_fichier == "defaut") {
        chemin_fichier = QCoreApplication::applicationDirPath() + "/configuration.xml";
        statusBar()->showMessage("Enregistrement de la configuration...", 2000);
    }
    /*QDomImplementation impl = QDomDocument().implementation();
    // document with document type
    QString name = "Configuration";
    QString publicId = "-//XADECK//DTD Stone 1.0 //EN";
    QString systemId = "http://www-imagis.imag.fr/DTD/stone1.dtd";*/
    //QDomDocument doc("Configuration_vladiconnect");
    QDomDocument doc("");
    //QDomDocument doc(impl.createDocumentType(name,publicId,systemId));

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

    for(int i=0 ; i<liste_serveur->count() ; i++) {
        // serveur node
        QDomElement dom_serveur = doc.createElement("serveur");
        dom_serveur.setAttribute("nom",liste_serveur->item(i)->text());
        dom_serveur.setAttribute("ip",liste_serveur->item(i)->data(100).toString());
        dom_serveur.setAttribute("mac",liste_serveur->item(i)->data(200).toString());
        dom_serveur.setAttribute("sousReseau",liste_serveur->item(i)->data(300).toString());
        dom_serveur.setAttribute("os",liste_serveur->item(i)->data(600).toString());
        dom_serveur.setAttribute("utilisateur",liste_serveur->item(i)->data(700).toString());
        dom_serveur.setAttribute("mdp",liste_serveur->item(i)->data(800).toString());

        // decription node
        QDomElement dom_description = doc.createElement("decription");
        dom_description.appendChild(doc.createTextNode(liste_serveur->item(i)->data(400).toString()));
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




