/********************************************************************************
** Form generated from reading UI file 'FenPrincipale.ui'
**
** Created: Fri Oct 28 14:29:16 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENPRINCIPALE_H
#define UI_FENPRINCIPALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenPrincipale
{
public:
    QAction *actionOptions;
    QAction *actionQuitter;
    QAction *actionSauver_la_configuration;
    QAction *actionCharger_une_configuration;
    QAction *actionImprimer_la_configuration;
    QAction *actionOuvrir_Putty;
    QAction *action;
    QAction *actionAbout;
    QAction *actionRun_hidden;
    QAction *actionDisable_tray_messages;
    QAction *actionChanger_de_langue;
    QAction *actionReduire_fermeture_fenetre;
    QAction *actionV_rifier_les_mises_jour;
    QAction *actionAide;
    QAction *actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *layout_liste_serveurs;
    QListWidget *serverModel;
    QPushButton *bouton_ajouter_serveur;
    QPushButton *bouton_supprimer_serveur2;
    QPushButton *bouton_trier_serveur;
    QPushButton *bouton_configuration_importer;
    QPushButton *bouton_configuration_exporter;
    QPushButton *bouton_maj_auto;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *serveur_nom;
    QLineEdit *serveur_ip;
    QLabel *label_7;
    QLineEdit *serveur_sousReseau;
    QLineEdit *serveur_mac;
    QLabel *label;
    QLabel *label_3;
    QCheckBox *serveurActiverArret;
    QTextEdit *serveur_description;
    QVBoxLayout *verticalLayout_3;
    QPushButton *bouton_editer;
    QPushButton *bouton_serveur_valider_modifications;
    QPushButton *bouton_supprimer_serveur;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QComboBox *serveur_os;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *serveur_utilisateur;
    QLabel *label_10;
    QLineEdit *serveur_mdp;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout;
    QPushButton *bouton_open_putty;
    QPushButton *bouton_close_putty;
    QPushButton *bouton_ping;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *action_nom;
    QLineEdit *action_etat;
    QProgressBar *action_progression;
    QLabel *action_etat_pixmap;
    QGridLayout *gridLayout_9;
    QLabel *label_4;
    QPlainTextEdit *console;
    QLabel *label_5;
    QPushButton *bouton_send_message;
    QPushButton *bouton_console;
    QPushButton *pushButton;
    QPlainTextEdit *serveur_commande;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *bouton_demarrer;
    QPushButton *bouton_arreter;
    QPushButton *bouton_redemarrer;
    QPushButton *bouton_stop_processus;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuOutils;
    QMenu *menu;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FenPrincipale)
    {
        if (FenPrincipale->objectName().isEmpty())
            FenPrincipale->setObjectName(QString::fromUtf8("FenPrincipale"));
        FenPrincipale->setEnabled(true);
        FenPrincipale->resize(700, 683);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../icone.png"), QSize(), QIcon::Normal, QIcon::Off);
        FenPrincipale->setWindowIcon(icon);
        FenPrincipale->setAutoFillBackground(false);
        actionOptions = new QAction(FenPrincipale);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionQuitter = new QAction(FenPrincipale);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionQuitter->setEnabled(true);
        actionSauver_la_configuration = new QAction(FenPrincipale);
        actionSauver_la_configuration->setObjectName(QString::fromUtf8("actionSauver_la_configuration"));
        actionCharger_une_configuration = new QAction(FenPrincipale);
        actionCharger_une_configuration->setObjectName(QString::fromUtf8("actionCharger_une_configuration"));
        actionImprimer_la_configuration = new QAction(FenPrincipale);
        actionImprimer_la_configuration->setObjectName(QString::fromUtf8("actionImprimer_la_configuration"));
        actionImprimer_la_configuration->setEnabled(false);
        actionOuvrir_Putty = new QAction(FenPrincipale);
        actionOuvrir_Putty->setObjectName(QString::fromUtf8("actionOuvrir_Putty"));
        actionOuvrir_Putty->setEnabled(false);
        action = new QAction(FenPrincipale);
        action->setObjectName(QString::fromUtf8("action"));
        actionAbout = new QAction(FenPrincipale);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionRun_hidden = new QAction(FenPrincipale);
        actionRun_hidden->setObjectName(QString::fromUtf8("actionRun_hidden"));
        actionRun_hidden->setCheckable(true);
        actionDisable_tray_messages = new QAction(FenPrincipale);
        actionDisable_tray_messages->setObjectName(QString::fromUtf8("actionDisable_tray_messages"));
        actionDisable_tray_messages->setCheckable(true);
        actionChanger_de_langue = new QAction(FenPrincipale);
        actionChanger_de_langue->setObjectName(QString::fromUtf8("actionChanger_de_langue"));
        actionReduire_fermeture_fenetre = new QAction(FenPrincipale);
        actionReduire_fermeture_fenetre->setObjectName(QString::fromUtf8("actionReduire_fermeture_fenetre"));
        actionReduire_fermeture_fenetre->setCheckable(true);
        actionV_rifier_les_mises_jour = new QAction(FenPrincipale);
        actionV_rifier_les_mises_jour->setObjectName(QString::fromUtf8("actionV_rifier_les_mises_jour"));
        actionAide = new QAction(FenPrincipale);
        actionAide->setObjectName(QString::fromUtf8("actionAide"));
        actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur = new QAction(FenPrincipale);
        actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur->setObjectName(QString::fromUtf8("actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur"));
        actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur->setCheckable(true);
        actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur->setChecked(true);
        widget = new QWidget(FenPrincipale);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(700, 500));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        layout_liste_serveurs = new QVBoxLayout();
        layout_liste_serveurs->setObjectName(QString::fromUtf8("layout_liste_serveurs"));
        serverModel = new QListWidget(widget);
        serverModel->setObjectName(QString::fromUtf8("serverModel"));

        layout_liste_serveurs->addWidget(serverModel);

        bouton_ajouter_serveur = new QPushButton(widget);
        bouton_ajouter_serveur->setObjectName(QString::fromUtf8("bouton_ajouter_serveur"));

        layout_liste_serveurs->addWidget(bouton_ajouter_serveur);

        bouton_supprimer_serveur2 = new QPushButton(widget);
        bouton_supprimer_serveur2->setObjectName(QString::fromUtf8("bouton_supprimer_serveur2"));

        layout_liste_serveurs->addWidget(bouton_supprimer_serveur2);

        bouton_trier_serveur = new QPushButton(widget);
        bouton_trier_serveur->setObjectName(QString::fromUtf8("bouton_trier_serveur"));

        layout_liste_serveurs->addWidget(bouton_trier_serveur);

        bouton_configuration_importer = new QPushButton(widget);
        bouton_configuration_importer->setObjectName(QString::fromUtf8("bouton_configuration_importer"));

        layout_liste_serveurs->addWidget(bouton_configuration_importer);

        bouton_configuration_exporter = new QPushButton(widget);
        bouton_configuration_exporter->setObjectName(QString::fromUtf8("bouton_configuration_exporter"));

        layout_liste_serveurs->addWidget(bouton_configuration_exporter);

        bouton_maj_auto = new QPushButton(widget);
        bouton_maj_auto->setObjectName(QString::fromUtf8("bouton_maj_auto"));
        bouton_maj_auto->setAutoRepeat(true);

        layout_liste_serveurs->addWidget(bouton_maj_auto);


        gridLayout->addLayout(layout_liste_serveurs, 0, 0, 4, 2);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setEnabled(true);
        groupBox_2->setMaximumSize(QSize(16777215, 185));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 2, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        serveur_nom = new QLineEdit(groupBox_2);
        serveur_nom->setObjectName(QString::fromUtf8("serveur_nom"));
        serveur_nom->setReadOnly(false);

        gridLayout_3->addWidget(serveur_nom, 0, 1, 1, 1);

        serveur_ip = new QLineEdit(groupBox_2);
        serveur_ip->setObjectName(QString::fromUtf8("serveur_ip"));
        serveur_ip->setInputMask(QString::fromUtf8("999.999.999.999; "));

        gridLayout_3->addWidget(serveur_ip, 1, 1, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        serveur_sousReseau = new QLineEdit(groupBox_2);
        serveur_sousReseau->setObjectName(QString::fromUtf8("serveur_sousReseau"));
        serveur_sousReseau->setMinimumSize(QSize(110, 0));
        serveur_sousReseau->setInputMask(QString::fromUtf8("999.999.999.999; "));

        gridLayout_3->addWidget(serveur_sousReseau, 3, 1, 1, 1);

        serveur_mac = new QLineEdit(groupBox_2);
        serveur_mac->setObjectName(QString::fromUtf8("serveur_mac"));
        serveur_mac->setInputMask(QString::fromUtf8(">HH:HH:HH:HH:HH:HH; "));

        gridLayout_3->addWidget(serveur_mac, 2, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);

        serveurActiverArret = new QCheckBox(groupBox_2);
        serveurActiverArret->setObjectName(QString::fromUtf8("serveurActiverArret"));
        serveurActiverArret->setChecked(true);

        gridLayout_3->addWidget(serveurActiverArret, 4, 0, 1, 2);

        serveur_description = new QTextEdit(groupBox_2);
        serveur_description->setObjectName(QString::fromUtf8("serveur_description"));

        gridLayout_3->addWidget(serveur_description, 1, 2, 4, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        bouton_editer = new QPushButton(groupBox_2);
        bouton_editer->setObjectName(QString::fromUtf8("bouton_editer"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("debug/images/document-edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouton_editer->setIcon(icon1);
        bouton_editer->setIconSize(QSize(30, 30));

        verticalLayout_3->addWidget(bouton_editer);

        bouton_serveur_valider_modifications = new QPushButton(groupBox_2);
        bouton_serveur_valider_modifications->setObjectName(QString::fromUtf8("bouton_serveur_valider_modifications"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        bouton_serveur_valider_modifications->setFont(font);
        bouton_serveur_valider_modifications->setLayoutDirection(Qt::LeftToRight);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("debug/images/dialog-ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouton_serveur_valider_modifications->setIcon(icon2);
        bouton_serveur_valider_modifications->setIconSize(QSize(30, 30));
        bouton_serveur_valider_modifications->setAutoRepeat(false);

        verticalLayout_3->addWidget(bouton_serveur_valider_modifications);

        bouton_supprimer_serveur = new QPushButton(groupBox_2);
        bouton_supprimer_serveur->setObjectName(QString::fromUtf8("bouton_supprimer_serveur"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouton_supprimer_serveur->setIcon(icon3);
        bouton_supprimer_serveur->setIconSize(QSize(30, 30));

        verticalLayout_3->addWidget(bouton_supprimer_serveur);


        gridLayout_3->addLayout(verticalLayout_3, 0, 3, 5, 1);


        gridLayout->addWidget(groupBox_2, 0, 3, 2, 3);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        serveur_os = new QComboBox(groupBox);
        serveur_os->setObjectName(QString::fromUtf8("serveur_os"));

        gridLayout_4->addWidget(serveur_os, 0, 2, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 0, 0, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 1, 0, 1, 1);

        serveur_utilisateur = new QLineEdit(groupBox);
        serveur_utilisateur->setObjectName(QString::fromUtf8("serveur_utilisateur"));

        gridLayout_4->addWidget(serveur_utilisateur, 1, 2, 1, 1);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 2, 0, 1, 1);

        serveur_mdp = new QLineEdit(groupBox);
        serveur_mdp->setObjectName(QString::fromUtf8("serveur_mdp"));
        serveur_mdp->setEchoMode(QLineEdit::Password);

        gridLayout_4->addWidget(serveur_mdp, 2, 2, 1, 1);


        gridLayout->addWidget(groupBox, 2, 3, 1, 1);

        groupBox_5 = new QGroupBox(widget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMaximumSize(QSize(16777215, 125));
        verticalLayout = new QVBoxLayout(groupBox_5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        bouton_open_putty = new QPushButton(groupBox_5);
        bouton_open_putty->setObjectName(QString::fromUtf8("bouton_open_putty"));

        verticalLayout->addWidget(bouton_open_putty);

        bouton_close_putty = new QPushButton(groupBox_5);
        bouton_close_putty->setObjectName(QString::fromUtf8("bouton_close_putty"));

        verticalLayout->addWidget(bouton_close_putty);

        bouton_ping = new QPushButton(groupBox_5);
        bouton_ping->setObjectName(QString::fromUtf8("bouton_ping"));
        bouton_ping->setAutoRepeat(true);

        verticalLayout->addWidget(bouton_ping);


        gridLayout->addWidget(groupBox_5, 4, 0, 1, 1);

        groupBox_4 = new QGroupBox(widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy2);
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        action_nom = new QLabel(groupBox_4);
        action_nom->setObjectName(QString::fromUtf8("action_nom"));
        action_nom->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Comic Sans MS\";"));

        verticalLayout_5->addWidget(action_nom);

        action_etat = new QLineEdit(groupBox_4);
        action_etat->setObjectName(QString::fromUtf8("action_etat"));
        action_etat->setEnabled(false);
        action_etat->setCursor(QCursor(Qt::ArrowCursor));
        action_etat->setReadOnly(false);

        verticalLayout_5->addWidget(action_etat);

        action_progression = new QProgressBar(groupBox_4);
        action_progression->setObjectName(QString::fromUtf8("action_progression"));
        action_progression->setEnabled(true);
        action_progression->setValue(0);

        verticalLayout_5->addWidget(action_progression);


        horizontalLayout->addLayout(verticalLayout_5);

        action_etat_pixmap = new QLabel(groupBox_4);
        action_etat_pixmap->setObjectName(QString::fromUtf8("action_etat_pixmap"));
        action_etat_pixmap->setMaximumSize(QSize(60, 60));
        action_etat_pixmap->setPixmap(QPixmap(QString::fromUtf8("../network-offline.png")));
        action_etat_pixmap->setScaledContents(true);
        action_etat_pixmap->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(action_etat_pixmap);


        gridLayout_6->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox_4, 4, 3, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);

        gridLayout_9->addWidget(label_4, 2, 0, 1, 1);

        console = new QPlainTextEdit(widget);
        console->setObjectName(QString::fromUtf8("console"));
        sizePolicy.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy);
        console->setStyleSheet(QString::fromUtf8("font: 8pt \"Courier New\";"));

        gridLayout_9->addWidget(console, 3, 0, 1, 5);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);

        gridLayout_9->addWidget(label_5, 0, 0, 2, 1);

        bouton_send_message = new QPushButton(widget);
        bouton_send_message->setObjectName(QString::fromUtf8("bouton_send_message"));

        gridLayout_9->addWidget(bouton_send_message, 0, 3, 1, 1);

        bouton_console = new QPushButton(widget);
        bouton_console->setObjectName(QString::fromUtf8("bouton_console"));

        gridLayout_9->addWidget(bouton_console, 1, 3, 1, 1);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_9->addWidget(pushButton, 2, 3, 1, 1);

        serveur_commande = new QPlainTextEdit(widget);
        serveur_commande->setObjectName(QString::fromUtf8("serveur_commande"));
        serveur_commande->setMaximumSize(QSize(16777215, 40));

        gridLayout_9->addWidget(serveur_commande, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_9, 5, 0, 1, 6);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        bouton_demarrer = new QPushButton(groupBox_3);
        bouton_demarrer->setObjectName(QString::fromUtf8("bouton_demarrer"));

        verticalLayout_4->addWidget(bouton_demarrer);

        bouton_arreter = new QPushButton(groupBox_3);
        bouton_arreter->setObjectName(QString::fromUtf8("bouton_arreter"));

        verticalLayout_4->addWidget(bouton_arreter);

        bouton_redemarrer = new QPushButton(groupBox_3);
        bouton_redemarrer->setObjectName(QString::fromUtf8("bouton_redemarrer"));

        verticalLayout_4->addWidget(bouton_redemarrer);

        bouton_stop_processus = new QPushButton(groupBox_3);
        bouton_stop_processus->setObjectName(QString::fromUtf8("bouton_stop_processus"));

        verticalLayout_4->addWidget(bouton_stop_processus);


        gridLayout->addWidget(groupBox_3, 4, 1, 1, 1);

        FenPrincipale->setCentralWidget(widget);
        menubar = new QMenuBar(FenPrincipale);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 700, 25));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuOutils = new QMenu(menubar);
        menuOutils->setObjectName(QString::fromUtf8("menuOutils"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        FenPrincipale->setMenuBar(menubar);
        statusbar = new QStatusBar(FenPrincipale);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setCursor(QCursor(Qt::BlankCursor));
        FenPrincipale->setStatusBar(statusbar);
#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(serveur_description);
        label_6->setBuddy(serveur_nom);
        label_7->setBuddy(serveur_ip);
        label->setBuddy(serveur_mac);
        label_3->setBuddy(serveur_sousReseau);
        label_4->setBuddy(console);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(action_etat, serverModel);
        QWidget::setTabOrder(serverModel, bouton_ajouter_serveur);
        QWidget::setTabOrder(bouton_ajouter_serveur, bouton_supprimer_serveur2);
        QWidget::setTabOrder(bouton_supprimer_serveur2, bouton_trier_serveur);
        QWidget::setTabOrder(bouton_trier_serveur, bouton_configuration_importer);
        QWidget::setTabOrder(bouton_configuration_importer, bouton_configuration_exporter);
        QWidget::setTabOrder(bouton_configuration_exporter, bouton_maj_auto);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuOutils->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menu->menuAction());
        menuFichier->addAction(actionSauver_la_configuration);
        menuFichier->addAction(actionCharger_une_configuration);
        menuFichier->addAction(actionImprimer_la_configuration);
        menuFichier->addSeparator();
        menuFichier->addAction(actionOuvrir_Putty);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menu->addAction(actionAide);
        menu->addAction(actionV_rifier_les_mises_jour);
        menu->addAction(actionAbout);
        menuOptions->addAction(actionRun_hidden);
        menuOptions->addAction(actionDisable_tray_messages);
        menuOptions->addAction(actionReduire_fermeture_fenetre);
        menuOptions->addSeparator();
        menuOptions->addAction(actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur);
        menuOptions->addSeparator();
        menuOptions->addAction(actionChanger_de_langue);

        retranslateUi(FenPrincipale);
        QObject::connect(pushButton, SIGNAL(clicked()), console, SLOT(clear()));

        QMetaObject::connectSlotsByName(FenPrincipale);
    } // setupUi

    void retranslateUi(QMainWindow *FenPrincipale)
    {
        FenPrincipale->setWindowTitle(QApplication::translate("FenPrincipale", "VladiConnect v1", 0, QApplication::UnicodeUTF8));
        actionOptions->setText(QApplication::translate("FenPrincipale", "Pr\303\251f\303\251rences", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOptions->setToolTip(QApplication::translate("FenPrincipale", "Pr\303\251f\303\251rences", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOptions->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("FenPrincipale", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuitter->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionSauver_la_configuration->setText(QApplication::translate("FenPrincipale", "Save", 0, QApplication::UnicodeUTF8));
        actionSauver_la_configuration->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionCharger_une_configuration->setText(QApplication::translate("FenPrincipale", "Load", 0, QApplication::UnicodeUTF8));
        actionCharger_une_configuration->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionImprimer_la_configuration->setText(QApplication::translate("FenPrincipale", "Print configuration", 0, QApplication::UnicodeUTF8));
        actionImprimer_la_configuration->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionOuvrir_Putty->setText(QApplication::translate("FenPrincipale", "Open Putty", 0, QApplication::UnicodeUTF8));
        actionOuvrir_Putty->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("FenPrincipale", "About", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("FenPrincipale", "About", 0, QApplication::UnicodeUTF8));
        actionRun_hidden->setText(QApplication::translate("FenPrincipale", "Run hidden", 0, QApplication::UnicodeUTF8));
        actionDisable_tray_messages->setText(QApplication::translate("FenPrincipale", "D\303\251sactiver les messages de la barre d'\303\251tat", 0, QApplication::UnicodeUTF8));
        actionChanger_de_langue->setText(QApplication::translate("FenPrincipale", "Change langage", 0, QApplication::UnicodeUTF8));
        actionReduire_fermeture_fenetre->setText(QApplication::translate("FenPrincipale", "R\303\251duire lorsque je ferme la fen\303\252tre", 0, QApplication::UnicodeUTF8));
        actionV_rifier_les_mises_jour->setText(QApplication::translate("FenPrincipale", "Check updates", 0, QApplication::UnicodeUTF8));
        actionAide->setText(QApplication::translate("FenPrincipale", "Help", 0, QApplication::UnicodeUTF8));
        actionAide->setShortcut(QApplication::translate("FenPrincipale", "F1", 0, QApplication::UnicodeUTF8));
        actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur->setText(QApplication::translate("FenPrincipale", "Run Vladiconnect when the computer starts", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLancer_VladiConnect_au_d_marrage_de_l_ordinateur->setToolTip(QApplication::translate("FenPrincipale", "Run Vladiconnect when the computer starts", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        bouton_ajouter_serveur->setText(QApplication::translate("FenPrincipale", "Add", 0, QApplication::UnicodeUTF8));
        bouton_supprimer_serveur2->setText(QApplication::translate("FenPrincipale", "Delete", 0, QApplication::UnicodeUTF8));
        bouton_trier_serveur->setText(QApplication::translate("FenPrincipale", "Sort", 0, QApplication::UnicodeUTF8));
        bouton_configuration_importer->setText(QApplication::translate("FenPrincipale", "Import the configuration", 0, QApplication::UnicodeUTF8));
        bouton_configuration_exporter->setText(QApplication::translate("FenPrincipale", "Export the configuration", 0, QApplication::UnicodeUTF8));
        bouton_maj_auto->setText(QApplication::translate("FenPrincipale", "Update", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FenPrincipale", "Properties", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FenPrincipale", "Description", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FenPrincipale", "Name", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FenPrincipale", "IP address", 0, QApplication::UnicodeUTF8));
        serveur_sousReseau->setText(QApplication::translate("FenPrincipale", "...", 0, QApplication::UnicodeUTF8));
        serveur_mac->setText(QApplication::translate("FenPrincipale", ":::::", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FenPrincipale", "MAC address", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FenPrincipale", "Subnet mask", 0, QApplication::UnicodeUTF8));
        serveurActiverArret->setText(QApplication::translate("FenPrincipale", "Activer l'arr\303\252t de la machine", 0, QApplication::UnicodeUTF8));
        bouton_editer->setText(QApplication::translate("FenPrincipale", "Editer les \n"
"param\303\250tres\n"
" du serveur", 0, QApplication::UnicodeUTF8));
        bouton_serveur_valider_modifications->setText(QApplication::translate("FenPrincipale", "Valider les\n"
" modifications\n"
" du serveur", 0, QApplication::UnicodeUTF8));
        bouton_supprimer_serveur->setText(QApplication::translate("FenPrincipale", "Supprimer \n"
" le serveur", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FenPrincipale", "Remote control properties", 0, QApplication::UnicodeUTF8));
        serveur_os->clear();
        serveur_os->insertItems(0, QStringList()
         << QApplication::translate("FenPrincipale", "Windows XP", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenPrincipale", "Windows 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenPrincipale", "Linux", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenPrincipale", "Other", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        serveur_os->setToolTip(QApplication::translate("FenPrincipale", "Choisissez le syst\303\250me d'exploitation de la machine", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("FenPrincipale", "Operating system", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FenPrincipale", "Login", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FenPrincipale", "Pass", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("FenPrincipale", "Local control", 0, QApplication::UnicodeUTF8));
        bouton_open_putty->setText(QApplication::translate("FenPrincipale", "Open Putty", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        bouton_close_putty->setWhatsThis(QApplication::translate("FenPrincipale", "Le lancement de WinSent permet de recevoir des messages qui transietent par le r\303\251seau en temps r\303\251\303\251l.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        bouton_close_putty->setText(QApplication::translate("FenPrincipale", "Close Putty", 0, QApplication::UnicodeUTF8));
        bouton_ping->setText(QApplication::translate("FenPrincipale", "Ping", 0, QApplication::UnicodeUTF8));
        bouton_ping->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("FenPrincipale", "Progression de la derni\303\250re action", 0, QApplication::UnicodeUTF8));
        action_nom->setText(QApplication::translate("FenPrincipale", "Nom de l'action", 0, QApplication::UnicodeUTF8));
        action_etat_pixmap->setText(QString());
        label_4->setText(QApplication::translate("FenPrincipale", "Console :", 0, QApplication::UnicodeUTF8));
        console->setPlainText(QString());
        label_5->setText(QApplication::translate("FenPrincipale", "Command :", 0, QApplication::UnicodeUTF8));
        bouton_send_message->setText(QApplication::translate("FenPrincipale", "Send message", 0, QApplication::UnicodeUTF8));
        bouton_console->setText(QApplication::translate("FenPrincipale", "Execute commande", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FenPrincipale", "Clear", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FenPrincipale", "Remote control", 0, QApplication::UnicodeUTF8));
        bouton_demarrer->setText(QApplication::translate("FenPrincipale", "Start", 0, QApplication::UnicodeUTF8));
        bouton_arreter->setText(QApplication::translate("FenPrincipale", "Shutdown", 0, QApplication::UnicodeUTF8));
        bouton_redemarrer->setText(QApplication::translate("FenPrincipale", "Restart", 0, QApplication::UnicodeUTF8));
        bouton_stop_processus->setText(QApplication::translate("FenPrincipale", "Stop current actions", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("FenPrincipale", "File", 0, QApplication::UnicodeUTF8));
        menuOutils->setTitle(QApplication::translate("FenPrincipale", "Tools", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("FenPrincipale", "Help", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("FenPrincipale", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FenPrincipale: public Ui_FenPrincipale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPALE_H
