/********************************************************************************
** Form generated from reading UI file 'FenPrincipale.ui'
**
** Created: Fri 12. Feb 20:32:16 2010
**      by: Qt User Interface Compiler version 4.6.0
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
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
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
#include "qlistewidget_serveur.h"

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
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_3;
    QLabel *label_9;
    QLineEdit *serveur_utilisateur;
    QLabel *label_10;
    QLineEdit *serveur_mdp;
    QComboBox *serveur_os;
    QLabel *label_8;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *layout_liste_serveurs;
    qlistewidget_serveur *liste_serveur;
    QPushButton *bouton_ajouter_serveur;
    QPushButton *bouton_supprimer_serveur2;
    QPushButton *bouton_trier_serveur;
    QPushButton *bouton_configuration_importer;
    QPushButton *bouton_configuration_exporter;
    QPushButton *bouton_maj_auto;
    QGroupBox *groupBox_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_6;
    QLineEdit *serveur_nom;
    QLabel *label_7;
    QLineEdit *serveur_ip;
    QLabel *label;
    QLineEdit *serveur_mac;
    QLabel *label_3;
    QLineEdit *serveur_sousReseau;
    QCheckBox *serveurActiverArret;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTextEdit *serveur_description;
    QVBoxLayout *verticalLayout_3;
    QPushButton *bouton_editer;
    QPushButton *bouton_serveur_valider_modifications;
    QPushButton *bouton_supprimer_serveur;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget;
    QGridLayout *_2;
    QPushButton *bouton_demarrer;
    QPushButton *bouton_ping;
    QPushButton *bouton_arreter;
    QPushButton *bouton_redemarrer;
    QPushButton *bouton_ouvrir_putty;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *action_nom;
    QLineEdit *action_etat;
    QProgressBar *action_progression;
    QLabel *action_etat_pixmap;
    QPlainTextEdit *console;
    QLabel *label_4;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout_2;
    QLabel *label_5;
    QPlainTextEdit *serveur_commande;
    QPushButton *bouton_console;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuOutils;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FenPrincipale)
    {
        if (FenPrincipale->objectName().isEmpty())
            FenPrincipale->setObjectName(QString::fromUtf8("FenPrincipale"));
        FenPrincipale->setEnabled(true);
        FenPrincipale->resize(742, 601);
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
        centralwidget = new QWidget(FenPrincipale);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(700, 450));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setGeometry(QRect(190, 190, 231, 111));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 20, 211, 82));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_9 = new QLabel(verticalLayoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_9);

        serveur_utilisateur = new QLineEdit(verticalLayoutWidget_2);
        serveur_utilisateur->setObjectName(QString::fromUtf8("serveur_utilisateur"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, serveur_utilisateur);

        label_10 = new QLabel(verticalLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_10);

        serveur_mdp = new QLineEdit(verticalLayoutWidget_2);
        serveur_mdp->setObjectName(QString::fromUtf8("serveur_mdp"));
        serveur_mdp->setEchoMode(QLineEdit::Password);

        formLayout_3->setWidget(2, QFormLayout::FieldRole, serveur_mdp);

        serveur_os = new QComboBox(verticalLayoutWidget_2);
        serveur_os->setObjectName(QString::fromUtf8("serveur_os"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, serveur_os);

        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_8);


        verticalLayout->addLayout(formLayout_3);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 3, 171, 371));
        layout_liste_serveurs = new QVBoxLayout(verticalLayoutWidget);
        layout_liste_serveurs->setObjectName(QString::fromUtf8("layout_liste_serveurs"));
        layout_liste_serveurs->setContentsMargins(0, 0, 0, 0);
        liste_serveur = new qlistewidget_serveur(verticalLayoutWidget);
        liste_serveur->setObjectName(QString::fromUtf8("liste_serveur"));

        layout_liste_serveurs->addWidget(liste_serveur);

        bouton_ajouter_serveur = new QPushButton(verticalLayoutWidget);
        bouton_ajouter_serveur->setObjectName(QString::fromUtf8("bouton_ajouter_serveur"));

        layout_liste_serveurs->addWidget(bouton_ajouter_serveur);

        bouton_supprimer_serveur2 = new QPushButton(verticalLayoutWidget);
        bouton_supprimer_serveur2->setObjectName(QString::fromUtf8("bouton_supprimer_serveur2"));

        layout_liste_serveurs->addWidget(bouton_supprimer_serveur2);

        bouton_trier_serveur = new QPushButton(verticalLayoutWidget);
        bouton_trier_serveur->setObjectName(QString::fromUtf8("bouton_trier_serveur"));

        layout_liste_serveurs->addWidget(bouton_trier_serveur);

        bouton_configuration_importer = new QPushButton(verticalLayoutWidget);
        bouton_configuration_importer->setObjectName(QString::fromUtf8("bouton_configuration_importer"));

        layout_liste_serveurs->addWidget(bouton_configuration_importer);

        bouton_configuration_exporter = new QPushButton(verticalLayoutWidget);
        bouton_configuration_exporter->setObjectName(QString::fromUtf8("bouton_configuration_exporter"));

        layout_liste_serveurs->addWidget(bouton_configuration_exporter);

        bouton_maj_auto = new QPushButton(verticalLayoutWidget);
        bouton_maj_auto->setObjectName(QString::fromUtf8("bouton_maj_auto"));
        bouton_maj_auto->setAutoRepeat(true);

        layout_liste_serveurs->addWidget(bouton_maj_auto);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(190, 0, 541, 181));
        horizontalLayoutWidget = new QWidget(groupBox_2);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 521, 151));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_6 = new QLabel(horizontalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        serveur_nom = new QLineEdit(horizontalLayoutWidget);
        serveur_nom->setObjectName(QString::fromUtf8("serveur_nom"));
        serveur_nom->setEnabled(false);
        serveur_nom->setReadOnly(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, serveur_nom);

        label_7 = new QLabel(horizontalLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        serveur_ip = new QLineEdit(horizontalLayoutWidget);
        serveur_ip->setObjectName(QString::fromUtf8("serveur_ip"));
        serveur_ip->setEnabled(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, serveur_ip);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        serveur_mac = new QLineEdit(horizontalLayoutWidget);
        serveur_mac->setObjectName(QString::fromUtf8("serveur_mac"));
        serveur_mac->setEnabled(false);

        formLayout->setWidget(2, QFormLayout::FieldRole, serveur_mac);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        serveur_sousReseau = new QLineEdit(horizontalLayoutWidget);
        serveur_sousReseau->setObjectName(QString::fromUtf8("serveur_sousReseau"));
        serveur_sousReseau->setEnabled(false);
        serveur_sousReseau->setMinimumSize(QSize(110, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, serveur_sousReseau);

        serveurActiverArret = new QCheckBox(horizontalLayoutWidget);
        serveurActiverArret->setObjectName(QString::fromUtf8("serveurActiverArret"));
        serveurActiverArret->setEnabled(true);
        serveurActiverArret->setChecked(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, serveurActiverArret);


        horizontalLayout_2->addLayout(formLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        serveur_description = new QTextEdit(horizontalLayoutWidget);
        serveur_description->setObjectName(QString::fromUtf8("serveur_description"));
        serveur_description->setEnabled(false);

        verticalLayout_2->addWidget(serveur_description);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        bouton_editer = new QPushButton(horizontalLayoutWidget);
        bouton_editer->setObjectName(QString::fromUtf8("bouton_editer"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("debug/images/document-edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouton_editer->setIcon(icon1);
        bouton_editer->setIconSize(QSize(30, 30));

        verticalLayout_3->addWidget(bouton_editer);

        bouton_serveur_valider_modifications = new QPushButton(horizontalLayoutWidget);
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

        bouton_supprimer_serveur = new QPushButton(horizontalLayoutWidget);
        bouton_supprimer_serveur->setObjectName(QString::fromUtf8("bouton_supprimer_serveur"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouton_supprimer_serveur->setIcon(icon3);
        bouton_supprimer_serveur->setIconSize(QSize(30, 30));

        verticalLayout_3->addWidget(bouton_supprimer_serveur);


        horizontalLayout_2->addLayout(verticalLayout_3);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 380, 131, 171));
        gridLayoutWidget = new QWidget(groupBox_3);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 111, 141));
        _2 = new QGridLayout(gridLayoutWidget);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(0, 0, 0, 0);
        bouton_demarrer = new QPushButton(gridLayoutWidget);
        bouton_demarrer->setObjectName(QString::fromUtf8("bouton_demarrer"));

        _2->addWidget(bouton_demarrer, 0, 0, 1, 1);

        bouton_ping = new QPushButton(gridLayoutWidget);
        bouton_ping->setObjectName(QString::fromUtf8("bouton_ping"));
        bouton_ping->setAutoRepeat(true);

        _2->addWidget(bouton_ping, 5, 0, 1, 1);

        bouton_arreter = new QPushButton(gridLayoutWidget);
        bouton_arreter->setObjectName(QString::fromUtf8("bouton_arreter"));

        _2->addWidget(bouton_arreter, 1, 0, 1, 1);

        bouton_redemarrer = new QPushButton(gridLayoutWidget);
        bouton_redemarrer->setObjectName(QString::fromUtf8("bouton_redemarrer"));

        _2->addWidget(bouton_redemarrer, 2, 0, 1, 1);

        bouton_ouvrir_putty = new QPushButton(gridLayoutWidget);
        bouton_ouvrir_putty->setObjectName(QString::fromUtf8("bouton_ouvrir_putty"));

        _2->addWidget(bouton_ouvrir_putty, 6, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(430, 190, 301, 111));
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 281, 75));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        action_nom = new QLabel(layoutWidget);
        action_nom->setObjectName(QString::fromUtf8("action_nom"));
        action_nom->setStyleSheet(QString::fromUtf8("font: 75 10pt \"Comic Sans MS\";"));

        verticalLayout_5->addWidget(action_nom);

        action_etat = new QLineEdit(layoutWidget);
        action_etat->setObjectName(QString::fromUtf8("action_etat"));
        action_etat->setEnabled(false);
        action_etat->setCursor(QCursor(Qt::ArrowCursor));
        action_etat->setReadOnly(false);

        verticalLayout_5->addWidget(action_etat);

        action_progression = new QProgressBar(layoutWidget);
        action_progression->setObjectName(QString::fromUtf8("action_progression"));
        action_progression->setEnabled(true);
        action_progression->setValue(0);

        verticalLayout_5->addWidget(action_progression);


        horizontalLayout->addLayout(verticalLayout_5);

        action_etat_pixmap = new QLabel(layoutWidget);
        action_etat_pixmap->setObjectName(QString::fromUtf8("action_etat_pixmap"));
        action_etat_pixmap->setMaximumSize(QSize(60, 60));
        action_etat_pixmap->setPixmap(QPixmap(QString::fromUtf8("../network-offline.png")));
        action_etat_pixmap->setScaledContents(true);
        action_etat_pixmap->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(action_etat_pixmap);

        console = new QPlainTextEdit(centralwidget);
        console->setObjectName(QString::fromUtf8("console"));
        console->setGeometry(QRect(150, 390, 581, 161));
        console->setStyleSheet(QString::fromUtf8("font: 8pt \"Courier New\";"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 370, 46, 13));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(190, 310, 361, 73));
        formLayout_2 = new QFormLayout(formLayoutWidget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_5);

        serveur_commande = new QPlainTextEdit(formLayoutWidget);
        serveur_commande->setObjectName(QString::fromUtf8("serveur_commande"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, serveur_commande);

        bouton_console = new QPushButton(centralwidget);
        bouton_console->setObjectName(QString::fromUtf8("bouton_console"));
        bouton_console->setGeometry(QRect(560, 310, 71, 71));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(634, 360, 91, 23));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(634, 310, 91, 23));
        FenPrincipale->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FenPrincipale);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 742, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuOutils = new QMenu(menubar);
        menuOutils->setObjectName(QString::fromUtf8("menuOutils"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        FenPrincipale->setMenuBar(menubar);
        statusbar = new QStatusBar(FenPrincipale);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setCursor(QCursor(Qt::BlankCursor));
        FenPrincipale->setStatusBar(statusbar);
#ifndef QT_NO_SHORTCUT
        label_6->setBuddy(serveur_nom);
        label_7->setBuddy(serveur_ip);
        label->setBuddy(serveur_mac);
        label_3->setBuddy(serveur_sousReseau);
        label_2->setBuddy(serveur_description);
        label_4->setBuddy(console);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(serveur_nom, serveur_ip);
        QWidget::setTabOrder(serveur_ip, bouton_demarrer);
        QWidget::setTabOrder(bouton_demarrer, bouton_ping);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuOutils->menuAction());
        menubar->addAction(menu->menuAction());
        menuFichier->addAction(actionSauver_la_configuration);
        menuFichier->addAction(actionCharger_une_configuration);
        menuFichier->addAction(actionImprimer_la_configuration);
        menuFichier->addSeparator();
        menuFichier->addAction(actionOuvrir_Putty);
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menuOutils->addAction(actionOptions);

        retranslateUi(FenPrincipale);
        QObject::connect(serveur_ip, SIGNAL(lostFocus()), FenPrincipale, SLOT(miseAJourItem()));
        QObject::connect(serveur_nom, SIGNAL(lostFocus()), FenPrincipale, SLOT(miseAJourItem()));
        QObject::connect(serveur_mac, SIGNAL(lostFocus()), FenPrincipale, SLOT(miseAJourItem()));
        QObject::connect(serveur_sousReseau, SIGNAL(lostFocus()), FenPrincipale, SLOT(miseAJourItem()));
        QObject::connect(pushButton, SIGNAL(clicked()), console, SLOT(clear()));
        QObject::connect(actionOuvrir_Putty, SIGNAL(activated()), FenPrincipale, SLOT(lower()));

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
        actionQuitter->setText(QApplication::translate("FenPrincipale", "Quitter", 0, QApplication::UnicodeUTF8));
        actionQuitter->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionSauver_la_configuration->setText(QApplication::translate("FenPrincipale", "Sauver la configuration", 0, QApplication::UnicodeUTF8));
        actionSauver_la_configuration->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionCharger_une_configuration->setText(QApplication::translate("FenPrincipale", "Charger une configuration", 0, QApplication::UnicodeUTF8));
        actionCharger_une_configuration->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionImprimer_la_configuration->setText(QApplication::translate("FenPrincipale", "Imprimer la configuration", 0, QApplication::UnicodeUTF8));
        actionImprimer_la_configuration->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionOuvrir_Putty->setText(QApplication::translate("FenPrincipale", "Ouvrir Putty", 0, QApplication::UnicodeUTF8));
        actionOuvrir_Putty->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("FenPrincipale", "Param\303\250tres d'arr\303\252t \303\240 distance", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FenPrincipale", "Nom d'utilisateur", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FenPrincipale", "Mot de passe", 0, QApplication::UnicodeUTF8));
        serveur_os->clear();
        serveur_os->insertItems(0, QStringList()
         << QApplication::translate("FenPrincipale", "Windows XP", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenPrincipale", "Windows 7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenPrincipale", "Linux", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("FenPrincipale", "Autre", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        serveur_os->setToolTip(QApplication::translate("FenPrincipale", "Choisissez le syst\303\250me d'exploitation de la machine", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("FenPrincipale", "Syst\303\250me \n"
"d'exploitation", 0, QApplication::UnicodeUTF8));
        bouton_ajouter_serveur->setText(QApplication::translate("FenPrincipale", "Ajouter un serveur", 0, QApplication::UnicodeUTF8));
        bouton_supprimer_serveur2->setText(QApplication::translate("FenPrincipale", "Supprimer le serveur", 0, QApplication::UnicodeUTF8));
        bouton_trier_serveur->setText(QApplication::translate("FenPrincipale", "Trier les serveurs", 0, QApplication::UnicodeUTF8));
        bouton_configuration_importer->setText(QApplication::translate("FenPrincipale", "Importer la configuration", 0, QApplication::UnicodeUTF8));
        bouton_configuration_exporter->setText(QApplication::translate("FenPrincipale", "Exporter la configuration", 0, QApplication::UnicodeUTF8));
        bouton_maj_auto->setText(QApplication::translate("FenPrincipale", "Mise \303\240 jour de l'\303\251tat \n"
"des serveurs", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("FenPrincipale", "Propri\303\251t\303\251s du serveur", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FenPrincipale", "Nom du serveur", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("FenPrincipale", "Adresse IP", 0, QApplication::UnicodeUTF8));
        serveur_ip->setInputMask(QApplication::translate("FenPrincipale", "999.999.999.999; ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FenPrincipale", "Adresse MAC", 0, QApplication::UnicodeUTF8));
        serveur_mac->setInputMask(QApplication::translate("FenPrincipale", ">HH:HH:HH:HH:HH:HH; ", 0, QApplication::UnicodeUTF8));
        serveur_mac->setText(QApplication::translate("FenPrincipale", ":::::", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("FenPrincipale", "Masque de \n"
"sous-r\303\251seau", 0, QApplication::UnicodeUTF8));
        serveur_sousReseau->setInputMask(QApplication::translate("FenPrincipale", "999.999.999.999; ", 0, QApplication::UnicodeUTF8));
        serveur_sousReseau->setText(QApplication::translate("FenPrincipale", "1...", 0, QApplication::UnicodeUTF8));
        serveurActiverArret->setText(QApplication::translate("FenPrincipale", "Activer l'arr\303\252t \n"
"de la machine", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FenPrincipale", "Description", 0, QApplication::UnicodeUTF8));
        bouton_editer->setText(QApplication::translate("FenPrincipale", "Editer les \n"
"param\303\250tres\n"
" du serveur", 0, QApplication::UnicodeUTF8));
        bouton_serveur_valider_modifications->setText(QApplication::translate("FenPrincipale", "Valider les\n"
" modifications\n"
" du serveur", 0, QApplication::UnicodeUTF8));
        bouton_supprimer_serveur->setText(QApplication::translate("FenPrincipale", "Supprimer \n"
" le serveur", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("FenPrincipale", "Actions \303\240 distance", 0, QApplication::UnicodeUTF8));
        bouton_demarrer->setText(QApplication::translate("FenPrincipale", "D\303\251marrer", 0, QApplication::UnicodeUTF8));
        bouton_ping->setText(QApplication::translate("FenPrincipale", "Tester le ping", 0, QApplication::UnicodeUTF8));
        bouton_ping->setShortcut(QApplication::translate("FenPrincipale", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        bouton_arreter->setText(QApplication::translate("FenPrincipale", "Arr\303\252ter", 0, QApplication::UnicodeUTF8));
        bouton_redemarrer->setText(QApplication::translate("FenPrincipale", "Red\303\251marrer", 0, QApplication::UnicodeUTF8));
        bouton_ouvrir_putty->setText(QApplication::translate("FenPrincipale", "Ouvrir Putty", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("FenPrincipale", "Progression de la derni\303\250re action", 0, QApplication::UnicodeUTF8));
        action_nom->setText(QApplication::translate("FenPrincipale", "Nom de l'action", 0, QApplication::UnicodeUTF8));
        action_etat_pixmap->setText(QString());
        console->setPlainText(QString());
        label_4->setText(QApplication::translate("FenPrincipale", "Console :", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FenPrincipale", "Commande :", 0, QApplication::UnicodeUTF8));
        bouton_console->setText(QApplication::translate("FenPrincipale", "Executer\n"
" la commande \n"
" \303\240 distance", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FenPrincipale", "Vider l'\303\251cran", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("FenPrincipale", "Bouton", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("FenPrincipale", "Fichier", 0, QApplication::UnicodeUTF8));
        menuOutils->setTitle(QApplication::translate("FenPrincipale", "Outils", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("FenPrincipale", "?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FenPrincipale: public Ui_FenPrincipale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPALE_H
