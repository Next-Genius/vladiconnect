TEMPLATE = app
QT += network \
    xml

# Input
SOURCES += main.cpp \
    FenPrincipale.cpp \
    FenPrincipale_wol.cpp \
    FenPrincipale_ping.cpp \
    FenPrincipale_configuration.cpp \
    item_serveur.cpp \
    FenPrincipale_putty.cpp \
    putty.cpp \
    FenPrincipale_systray.cpp
FORMS += FenPrincipale.ui \
    about.ui
HEADERS += FenPrincipale.h \
    item_serveur.h \
    putty.h
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
RESOURCES += ressources.qrc
