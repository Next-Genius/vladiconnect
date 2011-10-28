#ifndef PUTTY_H
#define PUTTY_H
#include <QtGui>

class Putty
{
    public:
    enum ParametrePutty {
        REDEMARRER,
        ARRETER,
        EXECUTER
    };

    enum Os {
        WINDOWS_XP,
        WINDOWS_7,
        LINUX
    };
    Putty(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int os);
static int commande(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int os, int parametre);
int commande_windows(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int parametre);
static void ouvrir_putty();

protected:
    QString m_hote;
    QString m_utilisateur;
    QString m_mdp;
    int m_os;
};


#endif // PUTTY_H
