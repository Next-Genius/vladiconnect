#include "qlistewidget_serveur.h"

qlistewidget_serveur::qlistewidget_serveur ( QWidget * parent = 0 ) : QListWidget(parent) {
    //QListWidget(parent);
}

void qlistewidget_serveur::addItem_serveur(item_serveur *item) {

    this->addItem(item);

}

item_serveur * qlistewidget_serveur::currentItem_serveur() {
    QListWidgetItem * item1 = new QListWidgetItem(*(this->currentItem()));
    int ligne = this->currentRow();
    //item_serveur item3 = items[ligne];
    //item1 = this->currentItem();
    item_serveur * item = new item_serveur(item1);
    item->setNom(item1->text());
    //item->setIp("");
    //item_serveur test = items.at(this->currentRow());

    return item;
}


