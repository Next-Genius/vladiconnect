#ifndef SERVEUR_H
#define SERVEUR_H
#include <QtGui>

class serveur {

    public:
       serveur(QString nom, QString ip, QString mac, QString sousReseau);
       bool setNom(QString nom);
       bool setIp(QString ip);
       bool setMac(QString mac);
       bool setSousReseau(QString sousReseau);
       bool setDescription(QString description);
       bool setConnecte(bool connecte);
       QString getNom();
       QString getIp();
       QString getMac();
       QString getSousReseau();
       QString getDescription();
       bool getConnecte();

       void out();

    protected:
       QString m_nom;
       QString m_ip;
       QString m_mac;
       QString m_sousReseau;
       QString m_description;
       bool m_connecte;

};

#endif // SERVEUR_H
