#include "item_serveur.h"
/*
item_serveur::item_serveur(QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp) {
    //vérfier format ip, mac et sous reseau
    QListWidgetItem(nom);
    m_nom = nom;
    m_ip = ip;
    m_mac = mac;
    m_sousReseau = sousReseau;
    m_description = "";
    m_connecte = false;
    m_os = os;
    m_utilisateur = utilisateur+"1";
    m_mdp = mdp;

}*/

item_serveur::item_serveur(QListWidget *widget_liste, QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp) {
    //vérfier format ip, mac et sous reseau
    if(nom == "") {
        return;
    }
    QListWidgetItem(nom, widget_liste);
    this->setText(nom);
    m_nom = nom;
    m_ip = ip;
    m_mac = mac;
    m_sousReseau = sousReseau;
    m_description = "";
    m_connecte = false;
    m_os = os;
    m_utilisateur = utilisateur;
    m_mdp = mdp;

}

item_serveur::item_serveur(QListWidgetItem *widget_item) {
    m_nom = "nom54";
    //m_ip = "ip";
    //m_mac = "mac";
    m_sousReseau = "sousReseau";
    m_description = "";
    m_connecte = false;
    m_os = "os";
    m_utilisateur = "utilisateur";
    m_mdp = "mdp";

}

bool item_serveur::setNom(QString nom) {
    m_nom = nom;
    return true;
}

bool item_serveur::setIp(QString ip) {
    m_ip = ip;
    return true;
}

bool item_serveur::setMac(QString mac) {
    m_mac = mac;
    return true;
}

bool item_serveur::setDescription(QString description) {
    m_description = description;
    return true;
}
bool item_serveur::setSousReseau(QString sousReseau) {
    m_sousReseau = sousReseau;
    return true;
}

bool item_serveur::setConnecte(bool connecte) {
    m_connecte = connecte;
    return true;
}

bool item_serveur::setOs(QString os) {
    m_os = os;
    return true;
}

bool item_serveur::setUtilisateur(QString utilisateur) {
    m_utilisateur = utilisateur;
    return true;
}

bool item_serveur::setMdp(QString mdp) {
    m_mdp = mdp;
    return true;
}

QString item_serveur::getNom() {
    return m_nom;
}

QString item_serveur::getIp() {
    return m_ip;
}
QString item_serveur::getMac() {
    return m_mac;
}
QString item_serveur::getSousReseau() {
    return m_sousReseau;
}
QString item_serveur::getDescription() {
    return m_description;
}
QString item_serveur::getOs() {
    return m_os;
}
QString item_serveur::getUtilisateur() {
    return m_utilisateur;
}
QString item_serveur::getMdp() {
    return m_mdp;
}
bool item_serveur::getConnecte() {
    return m_connecte;
}

void item_serveur::out() {
    //QMessageBox::information(0, "Fichier", "Serveur : \n nom : " +m_nom+ "\n ip : " + m_ip+"\n mac :"+m_mac+" ous avez sélectionné :\n");
}



