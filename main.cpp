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
 along with Synkron; if not, write to the Free Software Foundation,
 Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
********************************************************************/
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "FenPrincipale.h"

/*
  Clic sur ping -> appartition fenetre juste retour de ping



*/

// +++ About +++


/*
About::About(QString ver, QString year)
{
        setupUi(this);

        QString about = "<p style=\"font-family: sans-serif; font-style:italic;\"><span style=\"font-size:12pt;\">Synkron</span><br>";
        about.append("<span style=\"font-size:8pt;\">");
    about.append(tr("Version"));
    about.append(QString(" %1</span></p><p></p>").arg(ver));
    about.append("http://synkron.sourceforge.net/");
        about.append("<p style=\"font-family: sans-serif; font-size:8pt;\">");
    about.append(tr("Synkron is a simple Qt application designed for easy folder synchronisation."));
    about.append("</p><p></p>");
        about.append("<p style=\"font-family: sans-serif; font-size:8pt;\">");
    about.append(tr("This programme is distributed under the terms of the GPL v2."));
        about.append("</p><p></p>");
        about.append(QString::fromUtf8("<p style=\"font-family: sans-serif; font-size:8pt;\">2005-%1 <span style=\"font-style:italic;\">Mat\303\272\305\241 Tomlein</span> (matus.tomlein@gmail.com)</p>").arg(year));
        about.append("<p></p><p style=\"font-family: sans-serif; font-size:8pt;\">");
        about.append(tr("The programme is provided AS IS with ABSOLUTELY NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE."));
        about.append("</p>");
#ifdef Q_WS_MAC
        about.remove("font-family: sans-serif;");
        about.replace("font-size:12pt;", "font-size:14pt;");
        about.replace("font-size:8pt;", "font-size:10pt;");
#endif
    about_synkron_tb->setHtml(about);
        QString aboutQt = "<p style=\"font-family: sans-serif; font-style:italic;\"><span style=\"font-size:12pt;\">";
    aboutQt.append(tr("About Qt"));
        aboutQt.append("</span></p><p></p><p style=\"font-family: sans-serif; font-size:8pt; font-style:italic;\">");
        aboutQt.append(tr("This programme uses Qt Open Source Edition version %1.").arg(qVersion()));
        aboutQt.append("</p><p></p><p style=\"font-family: sans-serif; font-size:8pt;\">");
        aboutQt.append(tr("Qt is a C++ toolkit for cross-platform application development."));
        aboutQt.append("</p><p></p><p style=\"font-family: sans-serif; font-size:8pt;\">");
        aboutQt.append(tr("Qt provides single-source portability across MS Windows, Mac OS X, Linux and all major commercial Unix variants. Qt is also available for embedded devices as Qtopia Core."));
        aboutQt.append("</p><p></p><p style=\"font-family: sans-serif; font-size:8pt;\">");
        aboutQt.append(tr("Qt is a Trolltech product. See <span style=\"font-style:italic;\">http://www.trolltech.com/qt/</span> for more information."));
        aboutQt.append("</p>");
#ifdef Q_WS_MAC
        aboutQt.remove("font-family: sans-serif;");
        aboutQt.replace("font-size:12pt;", "font-size:14pt;");
        aboutQt.replace("font-size:8pt;", "font-size:10pt;");
#endif
    about_qt_tb->setHtml(aboutQt);
}
*/
// --- About ---




int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    app.setOrganizationName("Louis VICAINNE");
    app.setApplicationName("VladiConnect");
    app.setApplicationVersion("v 0.4800");

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
        if (lang == "C") { lang = "English"; sync_settings->setValue("lang", lang); }
        if (lang != "English") {
                /*QTranslator * translator = new QTranslator;
                translator->load(QString(":/i18n/Synkron-%1.qm").arg(lang.replace(" ", "_")));
                app.installTranslator(translator);*/

                QString locale = QLocale::system().name();
                QTranslator translator;
                translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
                app.installTranslator(&translator);
        }



    app.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "/images/icone.png"));



    FenPrincipale fenetre;
    fenetre.show();

    /*
    MainWindow *window = new MainWindow (sync_settings);
        if (window->runHidden() && app.arguments().count() <= 1) window->hide();
        else window->show();
*/

    //app.setAppMainWindow(fenetre);
    return app.exec();
}

