TEMPLATE = app
QT += network \
    xml

# Input
SOURCES += main.cpp \
    FenPrincipale.cpp \
    FenPrincipale_wol.cpp \
    FenPrincipale_ping.cpp \
    FenPrincipale_configuration.cpp \
    FenPrincipale_putty.cpp \
    putty.cpp \
    FenPrincipale_systray.cpp \
    FenPrincipale_settings.cpp \
    about.cpp \
    FenPrincipale_autre.cpp \
    cryptage.cpp \
    wol.cpp
FORMS += FenPrincipale.ui \
    about.ui
HEADERS += FenPrincipale.h \
    putty.h \
    about.h \
    cryptage.h \
    wol.h
OTHER_FILES += debug/rw.exe \
    debug/putty.exe \
    debug/plink.exe \
    debug/commande_putty.txt
DESTDIR = ./
win32 {
    # If not commented, the following line ensures that Synkron is compiled
    # as a portable app. More info at portableapps.com
    # DEFINES += PORTABLE_APP
    OBJECTS_DIR = .build.win32/
    MOC_DIR = .build.win32/
    RCC_DIR = .build.win32/
    RC_FILE = Vladiconnect.rc
}
LIBS += C:\Qt\2009.05\mingw\lib\libws2_32.a #lien direct vers la lib (ici pour Windows)
RESOURCES += ressources.qrc
TRANSLATIONS = vladiconnect_English.ts \
    vladiconnect_French.ts