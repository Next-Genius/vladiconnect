#ifndef ITEM_SERVEUR_H
#define ITEM_SERVEUR_H
#include <QListWidgetItem>

class item_serveur : public QListWidgetItem
{

public:
    item_serveur(QListWidget *widget_liste, QString nom, QString ip, QString mac, QString sousReseau, QString os, QString utilisateur, QString mdp);
};

#endif // ITEM_SERVEUR_H
