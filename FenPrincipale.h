#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include <QtGui>
#include <QtNetwork>
#include <QtXml>
#include "ui_FenPrincipale.h"
#include "serveur.h"
#include "processus.h"
#define NOM_AUTEUR() "Vladiyork"
#define NOM_LOGICIEL() "VladiConnect"
#define VERSION_LOGICIEL() 0.476
#define ENVIRONNEMENT 1
//Environnement : 1 = Win ; 2 Linux

class FenPrincipale : public QMainWindow, private Ui::FenPrincipale
{
    Q_OBJECT

    public:
        FenPrincipale();
        int EnregistrerConfiguration(QString chemin_fichier=QFileDialog::getSaveFileName(0, "Enregistrer", QString("configuration"), "Fichier de configuration xml (*.xml"));
        int chargerConfiguration(QString chemin_fichier =QFileDialog::getOpenFileName(0, "Ouvrir un fichier de configuration", QString(), "Fichier de configuration xml (*.xml)"));
        int miseAJour_QList_vers_formulaire(int numero_serveur);
        int miseAJour_formulaire_vers_QList(int numero_serveur);
        int ping(QString ip, int numero_m_liste =0, int parametre = 0);
        int wol(QString sousReseau, QString mac, int numero_m_liste, int parametre);
        void maj_formulaire_action(QString titre, QString etat, int progression, QString icone);
        void activer_formulaire(bool activer);

    public slots:
        void on_bouton_ping_clicked();
        void on_bouton_arreter_clicked();
        void on_bouton_editer_clicked();
        void on_bouton_ajouter_serveur_clicked();
        void on_bouton_supprimer_serveur_clicked();
        void on_bouton_serveur_valider_modifications_clicked();
        void on_bouton_configuration_importer_clicked();
        void on_bouton_configuration_exporter_clicked();
        void on_liste_serveur_itemSelectionChanged();
        void on_bouton_demarrer_clicked();
        int miseAJourItem();
        void fin_processus(int exitCode,QProcess::ExitStatus statut);
        void sortie_processus();
        void on_bouton_maj_auto_clicked();
        void on_serveur_activerArret_stateChanged(Qt::CheckState state);

    private:
        QList<serveur> m_liste;
        //QList<processus> m_liste_processusm_liste_processus;
        //QProcess processus;
        //processus pro10;
        QList<QProcess*> m_liste_processus;
};

#endif // FENPRINCIPALE_H

