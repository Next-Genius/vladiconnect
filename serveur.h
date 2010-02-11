#ifndef SERVEUR_H
#define SERVEUR_H
#include <QtGui>

class serveur {

    public:
       serveur(QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp);
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

#endif // SERVEUR_H
