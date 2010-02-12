TEMPLATE = app
QT += network \
    xml
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
SOURCES += main.cpp \
    FenPrincipale.cpp \
    serveur.cpp \
    FenPrincipale_wol.cpp \
    FenPrincipale_ping.cpp \
    FenPrincipale_configuration.cpp \
    item_serveur.cpp \
    qlistewidget_serveur.cpp \
    FenPrincipale_putty.cpp \
    putty.cpp
FORMS += FenPrincipale.ui
HEADERS += FenPrincipale.h \
    serveur.h \
    item_serveur.h \
    qlistewidget_serveur.h \
    putty.h
OTHER_FILES += debug/rw.exe \
    debug/putty.exe \
    debug/plink.exe \
    debug/commande_putty.txt
