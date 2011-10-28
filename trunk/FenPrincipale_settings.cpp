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

void FenPrincipale::saveSettings() {
    //QSettings sync_settings (QSettings::IniFormat, QSettings::UserScope, "Louis VICAINNE", "Vladiconnect");

    QString lang = sync_settings->value("lang", "English").toString();
    bool dont_ask_on_quit = sync_settings->value("dont_ask_on_quit").toBool();
    bool minimise_on_quit = sync_settings->value("minimise_on_quit").toBool();
    sync_settings->clear();
    sync_settings->setValue("lang", lang);
    sync_settings->setValue("dont_ask_on_quit", dont_ask_on_quit);
    sync_settings->setValue("minimise_on_quit", minimise_on_quit);
    sync_settings->setValue("disable_tray_messages", actionDisable_tray_messages->isChecked());
    sync_settings->setValue("run_hidden", run_hidden);
    //sync_settings->setValue("temp_path", raw_temp_path);
    sync_settings->setValue("pos", this->pos());
    sync_settings->setValue("size", this->size());
    sync_settings->setValue("ver", QVariant(f_ver).toString());
#ifdef Q_WS_MAC
    sync_settings->setValue("macx_brushedmetalstyle", actionBrushedMetalStyle->isChecked());
#endif
}

void FenPrincipale::readSettings() {
    QSettings settings ("Louis VICAINNE", "Vladiconnect");
#ifdef Q_WS_MAC
    actionBrushedMetalStyle->setChecked(sync_settings->value("macx_brushedmetalstyle", settings.value("macx_brushedmetalstyle", false)).toBool());
    if (actionBrushedMetalStyle->isChecked()) this->setAttribute(Qt::WA_MacBrushedMetal);
    this->setUnifiedTitleAndToolBarOnMac(!actionBrushedMetalStyle->isChecked());
#endif

    actionDisable_tray_messages->setChecked(sync_settings->value("disable_tray_messages").toBool());
    run_hidden = sync_settings->value("run_hidden", false).toBool();
    //temp_path = dir.absolutePath();
    this->move(sync_settings->value("pos", (settings.value("pos", this->pos()))).toPoint());
    this->resize(sync_settings->value("size", (settings.value("size", this->size()))).toSize());
    actionRun_hidden->setChecked(run_hidden);
    trayIconVisible(!run_hidden);
}

