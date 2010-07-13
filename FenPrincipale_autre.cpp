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

void FenPrincipale::changeTemp()
{
   /* //QString text = getPathDialogue(true, temp_path);
    MTPathDialogue * dialogue = new MTPathDialogue(this);
    QString text = dialogue->getPath(true, raw_temp_path);
    if (text.isEmpty()) return;
    raw_temp_path = text;
    QDir dir (raw_temp_path);
    temp_path = dir.absolutePath();
    loadTempSettings();*/
}

bool FenPrincipale::closeDialogue()
{
    QSettings settings ("Louis VICAINNE", "Vladiconnect");
    if (sync_settings->value("dont_ask_on_quit", settings.value("dont_ask_on_quit")).toBool()==true) {
        if (sync_settings->value("minimise_on_quit", settings.value("minimise_on_quit")).toBool()==true) {
            minimizeAction->trigger();
            return false;
        } else if (sync_settings->value("minimise_on_quit", settings.value("minimise_on_quit")).toBool()==false) {
            return true;
        }
    }
    QDialog * cl_dialogue = new QDialog (this, Qt::Dialog);
    cl_dialogue->setWindowModality(Qt::WindowModal);
    //cl_dialogue->setAttribute(Qt::WA_DeleteOnClose);
    cl_dialogue->setWindowTitle(tr("Quit Synkron"));
    QGridLayout * cl_glayout = new QGridLayout (cl_dialogue);
    cl_glayout->setMargin(4); cl_glayout->setSpacing(10);
    QLabel * cl_label = new QLabel (cl_dialogue);
    cl_label->setText(tr("Are you sure you want to quit?"));
    cl_label->setAlignment(Qt::AlignHCenter);
    cl_glayout->addWidget(cl_label, 0, 0);
    QCheckBox * rm_minimise = new QCheckBox(cl_dialogue);
    rm_minimise->setText(tr("Do not ask me again"));
    rm_minimise->setChecked(true);
    cl_glayout->addWidget(rm_minimise, 1, 0);
    QHBoxLayout * hlayout = new QHBoxLayout;
    hlayout->addStretch();
    QPushButton * close_btn = new QPushButton (cl_dialogue);
    close_btn->setText(tr("&Quit"));
    connect(close_btn, SIGNAL(released()), cl_dialogue, SLOT(accept()));
    hlayout->addWidget(close_btn);
    QPushButton * minimise_btn = new QPushButton (cl_dialogue);
    minimise_btn->setText(tr("&Minimise"));
    connect(minimise_btn, SIGNAL(released()), cl_dialogue, SLOT(reject()));
    hlayout->addWidget(minimise_btn);
    hlayout->addStretch();
    cl_glayout->addLayout(hlayout, 2, 0);
    switch (cl_dialogue->exec()) {
        case 0: // Minimise
            sync_settings->setValue("dont_ask_on_quit", rm_minimise->isChecked());
            sync_settings->setValue("minimise_on_quit", true);
            this->showTrayMessage(tr("Réduction de VladiConnect"),tr("VladiConnect continue toutefois de fonctionner"));
            minimizeAction->trigger();
            return false;
            break;
        case 1: // Quit
            sync_settings->setValue("dont_ask_on_quit", rm_minimise->isChecked());
            sync_settings->setValue("minimise_on_quit", false);
            return true;
            break;
    }
    return true;
}
