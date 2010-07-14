#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include <QtGui>
#include <QtNetwork>
#include <QtXml>

#include <QCloseEvent>
#include "ui_FenPrincipale.h"
#include "putty.h"
#include "cryptage.h"
#include "about.h"
#include "wol.h"

#define NOM_AUTEUR() "Vladiyork"
#define NOM_LOGICIEL() "VladiConnect"
#define VERSION_LOGICIEL() 0.511
#define ENVIRONNEMENT 1
//Environnement : 1 = Win ; 2 Linux

class FenPrincipale : public QMainWindow, private Ui::FenPrincipale
{
    Q_OBJECT

public:
    FenPrincipale(QSettings *);
    void setValueAction(int value);
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
    bool skip_close_event;
    bool runHidden() { return run_hidden; }
    bool shownManually() { return shown_manually; }

    QSettings * sync_settings;
    QSettings * temp_settings;;

private slots:
    //Autre
    bool closeDialogue();
    void closeApp() { no_closedialogue = true; this->close(); }
    void changeTemp();
    void setRunHidden(bool b) { run_hidden = b; }

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
    void on_bouton_open_putty_clicked();
    void on_bouton_close_putty_clicked();
    void on_bouton_winsent_clicked();
    void on_serveurActiverArret_stateChanged(int state);
    int miseAJourItem();
    void fin_processus(int exitCode,QProcess::ExitStatus statut);
    void sortie_processus_wol();
    void putty_retour();
    void putty_fin(int exitCode,QProcess::ExitStatus exitStatus);
    void about ();

    //TrayIcon
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayIconVisible(bool);
    bool showTrayMessage(QString, QString);

    //Demarrage automatique
    void demarrage_automatique_activer ();
    void demarrage_automatique_desactiver ();

    void closeEvent(QCloseEvent* event);




private:
    float f_ver;
    QString ver;
    bool run_hidden;
    bool no_closedialogue;
    bool shown_manually;

    void createTrayActions();
    void createTrayIcon();
    void saveSettings();
    void readSettings();
    //void attendre(int secondes);
    QList<QProcess*> m_liste_processus;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QProcess *putty_process;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
};


#endif // FENPRINCIPALE_H

