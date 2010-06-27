#include "item_serveur.h"


item_serveur::item_serveur(QListWidget *widget_liste, QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp) {
    //vérfier format ip, mac et sous reseau
    /*if(nom == "") {
        return;
    }*/
    QListWidgetItem(nom, widget_liste);
    this->setText(nom);
    this->setData(0, nom);
    this->setData(1, ip);
    this->setData(2, mac);
    this->setData(3, sousReseau);
    this->setData(4, "");
    this->setData(5, false);
    this->setData(6, os);
    this->setData(7, utilisateur);
    this->setData(8, mdp);
    //this->setData(9, nom);

}





