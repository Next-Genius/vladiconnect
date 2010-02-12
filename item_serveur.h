#ifndef ITEM_SERVEUR_H
#define ITEM_SERVEUR_H
#include <QListWidgetItem>

class item_serveur : public QListWidgetItem
{

public:
    //item_serveur(QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp);
    item_serveur(QListWidget *widget_liste, QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp);
    item_serveur(QListWidgetItem *widget_item);
    bool setNom(QString nom);
    bool setIp(QString ip);
    bool setMac(QString mac);
    bool setSousReseau(QString sousReseau);
    bool setDescription(QString description);
    bool setConnecte(bool connecte);
    bool setOs(QString os);
    bool setUtilisateur(QString utilisateur);
    bool setMdp(QString mdp);
    QString getNom();
    QString getIp();
    QString getMac();
    QString getSousReseau();
    QString getDescription();
    QString getOs();
    QString getUtilisateur();
    QString getMdp();
    bool getConnecte();

    void out();

protected:
    QString m_nom;
    QString m_ip;
    QString m_mac;
    QString m_sousReseau;
    QString m_description;
    QString m_os;
    QString m_utilisateur;
    QString m_mdp;
    bool m_connecte;

};

#endif // ITEM_SERVEUR_H
