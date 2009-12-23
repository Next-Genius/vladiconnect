#include "serveur.h"

serveur::serveur(QString nom, QString ip, QString mac, QString sousReseau) {
    //vérfier format ip, mac et sous reseau
    m_nom = nom;
    m_ip = ip;
    m_mac = mac;
    m_sousReseau = sousReseau;
    m_description = "";
    m_connecte = false;

}

bool serveur::setNom(QString nom) {
    m_nom = nom;
    return true;
}

bool serveur::setIp(QString ip) {
    m_ip = ip;
    return true;
}

bool serveur::setMac(QString mac) {
    m_mac = mac;
    return true;
}

bool serveur::setDescription(QString description) {
    m_description = description;
    return true;
}
bool serveur::setSousReseau(QString sousReseau) {
    m_sousReseau = sousReseau;
    return true;
}

bool serveur::setConnecte(bool connecte) {
    m_connecte = connecte;
    return true;
}

QString serveur::getNom() {
    return m_nom;
}

QString serveur::getIp() {
    return m_ip;
}
QString serveur::getMac() {
    return m_mac;
}
QString serveur::getSousReseau() {
    return m_sousReseau;
}
QString serveur::getDescription() {
    return m_description;
}
bool serveur::getConnecte() {
    return m_connecte;
}

void serveur::out() {
    QMessageBox::information(0, "Fichier", "Serveur : \n nom : " +m_nom+ "\n ip : " + m_ip+"\n mac :"+m_mac+" ous avez sélectionné :\n");
}

