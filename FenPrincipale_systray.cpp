/*******************************************************************
 This file is part of Vladiconnect
 Copyright (C) 2009-2010 Louis VICAINNE (louis.vicainne@gmail.com)

 Vladiconnect is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public Licence
 as published by the Free Software Foundation; either version 2
 of the Licence, or (at your option) any later version.

 Vladiconnect is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public Licence for more details.

 You should have received a copy of the GNU General Public Licence
 along with VladiConnect; if not, write to the Free Software Foundation,
 Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
********************************************************************/
#include "FenPrincipale.h"


// +++ Tray icon +++


void FenPrincipale::createTrayIcon()
{
     QMenu * trayIconMenu = new QMenu(this);
     /*trayIconMenu->addAction(syncAction);
     trayIconMenu->addAction(syncAllAction);
     trayIconMenu->addMenu(menuOptions);
     trayIconMenu->addSeparator();*/
     trayIconMenu->addAction(minimizeAction);
     trayIconMenu->addAction(maximizeAction);
     trayIconMenu->addSeparator();
     trayIconMenu->addAction(quitAction);

     trayIcon = new QSystemTrayIcon(this);
     trayIcon->setIcon(QIcon(QString::fromUtf8(":/images/icone.png")));
     trayIcon->setToolTip("Vladiconnect");
     trayIcon->setContextMenu(trayIconMenu);
     connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
             this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
}

void FenPrincipale::trayIconVisible(bool visible)
{
     minimizeAction->setEnabled(visible);
     maximizeAction->setEnabled(!visible);
     /*syncAction->setEnabled(true);
     syncAllAction->setEnabled(true);*/
}

void FenPrincipale::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::MiddleClick:
        case QSystemTrayIcon::DoubleClick:
                if (this->isHidden()) {
                        this->show();
                }
                else {
                    this->showTrayMessage("Reduction de Vladiconnect", QString::fromLatin1(NOM_LOGICIEL())+" a été réduit. Il continue toutefois de travailler en arrière plan.");
                        this->hide();
                }
                break;
    case QSystemTrayIcon::Context:
        trayIcon->contextMenu()->show();
        break;
    default:
        break;
    }
}

bool FenPrincipale::showTrayMessage(QString title, QString message)
{
        if (!actionDisable_tray_messages->isChecked()) {
                trayIcon->showMessage(title, message);
                return true;
        } else return false;
}

void FenPrincipale::closeEvent(QCloseEvent* event)
{
    if (skip_close_event) {
        trayIcon->hide();
        event->accept();
        return;
    }
    if (!no_closedialogue) {
#ifdef Q_WS_MAC
        event->ignore();
        this->hide();
        return;
#else
        if (!closeDialogue()) {
            event->ignore();
            return;
        }
#endif
    }
    this->hide();
}



void FenPrincipale::showEvent(QShowEvent *)
{
    shown_manually = true;
    trayIconVisible(true);
}

void FenPrincipale::hideEvent(QHideEvent *)
{
    saveSettings();
    trayIconVisible(false);
}

void FenPrincipale::createTrayActions()
{
     minimizeAction = new QAction(tr("&Hide"), this);
     connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
     //connect(minimizeAction, SIGNAL(triggered()), this, SLOT(minimizeTrayIcon()));

	 maximizeAction = new QAction(tr("S&how"), this);
     connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

     restoreAction = new QAction(tr("&Restore"), this);
     connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
     maximizeAction = new QAction(tr("S&how"), this);
     connect(maximizeAction, SIGNAL(triggered()), this, SLOT(show()));
     //connect(maximizeAction, SIGNAL(triggered()), this, SLOT(maximizeTrayIcon()));

     quitAction = new QAction(tr("&Quit"), this);
     connect(quitAction, SIGNAL(triggered()), this, SLOT(closeApp()));
}

void FenPrincipale::printMessage(QString myMessage, QString title) {
	this->showTrayMessage(title, myMessage); //Pop up
	this->statusBar()->showMessage(myMessage, 2000); //Barre d'état
}

// --- Tray icon ---
