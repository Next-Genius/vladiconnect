TEMPLATE = app
QT += network \
    xml

DEFINES += CLINUX

# Input
HEADERS += about.h \
    cryptage.h \
    FenPrincipale.h \
    process.h \
    putty.h \
    receiver.h \
    sender.h \
    udpsocket.h \
    wol.h \
    server.h \
    configuration.h \
    ping.h
FORMS += about.ui \
    FenPrincipale.ui
SOURCES += about.cpp \
    cryptage.cpp \
    FenPrincipale.cpp \
    FenPrincipale_autre.cpp \
    FenPrincipale_configuration.cpp \
    FenPrincipale_settings.cpp \
    FenPrincipale_systray.cpp \
    main.cpp \
    process.cpp \
    putty.cpp \
    receiver.cpp \
    sender.cpp \
    udpsocket.cpp \
    wol.cpp \
    server.cpp \
    configuration.cpp \
    ping.cpp
OTHER_FILES += debug/putty.exe \
    debug/plink.exe \
    debug/commande_putty.txt
DESTDIR = ../debug.win32/
win32 { 
    # If not commented, the following line ensures that Synkron is compiled
    # as a portable app. More info at portableapps.com
    # DEFINES += PORTABLE_APP
    OBJECTS_DIR = .build.win32/
    MOC_DIR = .build.win32/
    RCC_DIR = .build.win32/
    RC_FILE = Vladiconnect.rc
}

LIBS += C:\QtSDK\mingw\lib\libws2_32.a # lien direct vers la lib (ici pour Windows) pour le wol
RESOURCES += ressources.qrc
TRANSLATIONS += vladiconnect_en.ts \
    vladiconnect_fr.ts
