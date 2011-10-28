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

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "FenPrincipale.h"

/*
Barre d'état : se modifie et donne + d'infos lorsque on pointe un bouton

*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Louis VICAINNE");
    app.setApplicationName("VladiConnect");
    app.setApplicationVersion("v 0.511");
    app.setWindowIcon(QIcon(":/images/icone.png"));

    QFileInfo file_info (app.arguments().at(0));
    QDir dir (file_info.dir()); QSettings * sync_settings;

    #ifdef PORTABLE_APP
        dir.cdUp(); dir.cdUp();
        dir.cd("Data"); dir.cd("settings");
    #endif

    if (dir.exists("Vladiconnect.ini")) {
        sync_settings = new QSettings (dir.absoluteFilePath("Vladiconnect.ini"), QSettings::IniFormat);
    } else {
        sync_settings = new QSettings (QSettings::IniFormat, QSettings::UserScope, "Louis VICAINNE", "Vladiconnect");
    }

    QString lang = sync_settings->value("lang").toString();
    if (lang.isEmpty()) {
        lang = QLocale::languageToString(QLocale::system().language());
        sync_settings->setValue("lang", lang);
    }

    if (lang == "C") {
        lang = "English";
        sync_settings->setValue("lang", lang);
    }

	if (lang != "English") {
		QTranslator * translator = new QTranslator;
		QString locale = QLocale::system().name().section('_', 0, 0);

		if(translator->load(QString(":/lang/vladiconnect_") + locale + ".qm")) {


		} else {
			//Le pack de langue n'a pu être chargé !
			return -2;
		}
        //translator->load(QString(":/lang/vladiconnect_%1.qm").arg(lang.replace(" ", "_")));
		app.installTranslator(translator);
	}

	FenPrincipale *fenetre = new FenPrincipale(sync_settings, &app);
    if (fenetre->runHidden() && app.arguments().count() <= 1)
        fenetre->hide();
    else
        fenetre->show();

    return app.exec();
}

