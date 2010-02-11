#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "FenPrincipale.h"

/*
  Clic sur ping -> appartition fenetre juste retour de ping



  */

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.quitOnLastWindowClosed();
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);
    app.setApplicationName("VladiConnect");
    app.setApplicationVersion("v 0.0001");
    FenPrincipale fenetre;
    fenetre.show();



    return app.exec();
}

