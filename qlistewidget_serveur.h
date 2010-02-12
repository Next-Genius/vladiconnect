#ifndef QLISTEWIDGET_SERVEUR_H
#define QLISTEWIDGET_SERVEUR_H
#include <QListWidget>
#include "item_serveur.h"

class qlistewidget_serveur : public QListWidget {

public:
    qlistewidget_serveur ( QWidget * parent );
    void addItem_serveur(item_serveur *item);
    item_serveur * currentItem_serveur();

protected:
    QList<item_serveur*> m_liste_item() const;
};

#endif // QLISTEWIDGET_SERVEUR_H
