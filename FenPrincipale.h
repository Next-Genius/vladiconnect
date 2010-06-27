#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include <QtGui>
#include <QtNetwork>
#include <QtXml>

#include <QCloseEvent>

#include "ui_FenPrincipale.h"
#include "item_serveur.h"
#include "serveur.h"
#include "putty.h"
#define NOM_AUTEUR() "Vladiyork"
#define NOM_LOGICIEL() "VladiConnect"
#define VERSION_LOGICIEL() 0.485
#define ENVIRONNEMENT 1
//Environnement : 1 = Win ; 2 Linux

class FenPrincipale : public QMainWindow, private Ui::FenPrincipale
{
    Q_OBJECT

    public:

        FenPrincipale();
        int enregistrerConfiguration(QString chemin_fichier=QFileDialog::getSaveFileName(0, "Enregistrer", QString("configuration"), "Fichier de configuration xml (*.xml"));
        int chargerConfiguration(QString chemin_fichier =QFileDialog::getOpenFileName(0, "Ouvrir un fichier de configuration", QString(), "Fichier de configuration xml (*.xml)"));
        int miseAJour_QList_vers_formulaire(int numero_serveur);
        int miseAJour_formulaire_vers_QList(int numero_serveur);
        int ping(QString ip, int numero_m_liste =0, int parametre = 0);
        int wol(QString sousReseau, QString mac, int numero_m_liste, int parametre = 0);
        int putty_commande(QString hote, QString utilisateur, QString mdp, int numero_m_liste, int parametre);
        void maj_formulaire_action(QString titre, QString etat, int progression, QString icone);
        void activer_formulaire(bool activer);
        void initialisation_executables();

    public slots:
        void on_bouton_ping_clicked();
        void on_bouton_arreter_clicked();
        void on_bouton_editer_clicked();
        void on_bouton_ajouter_serveur_clicked();
        void on_bouton_supprimer_serveur_clicked();
        void on_bouton_supprimer_serveur2_clicked();
        void on_bouton_trier_serveur_clicked();
        void on_bouton_console_clicked();
        void on_bouton_serveur_valider_modifications_clicked();
        void on_bouton_configuration_importer_clicked();
        void on_bouton_configuration_exporter_clicked();
        void on_liste_serveur_itemSelectionChanged();
        void on_bouton_demarrer_clicked();
        void on_bouton_maj_auto_clicked();
        void on_bouton_ouvrir_putty_clicked();
        void on_serveurActiverArret_stateChanged(int state);
        int miseAJourItem();
        void fin_processus(int exitCode,QProcess::ExitStatus statut);
        void sortie_processus_wol();
        void putty_retour();
        void putty_fin(int exitCode,QProcess::ExitStatus exitStatus);
        void about ();

        void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
        void trayIconVisible(bool);
        bool showTrayMessage(QString, QString);

        void closeEvent(QCloseEvent* event);


private:
        void createTrayActions();
        void createTrayIcon();

        QList<QProcess*> m_liste_processus;

        QAction *minimizeAction;
        QAction *maximizeAction;
        QAction *restoreAction;
        QAction *quitAction;

        QSystemTrayIcon *trayIcon;
        QMenu *trayIconMenu;
};
/*
class About : public QDialog, private Ui::About
{
    Q_OBJECT

public:
    About(QString, QString);
};
*/
#endif // FENPRINCIPALE_H

