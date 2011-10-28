#include "putty.h"

Putty::Putty(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int os) {

}

int Putty::commande(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int os, int parametre) {
    if(os == Putty::LINUX)
        return true;
    //if(os == Putty::WINDOWS_XP||Putty::WINDOWS_7)
        //return commande_windows(hote, utilisateur, mdp, numero_m_liste, parametre);
    return true;
}

int Putty::commande_windows(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int parametre) {
    return true;
}

void Putty::ouvrir_putty() {

}


