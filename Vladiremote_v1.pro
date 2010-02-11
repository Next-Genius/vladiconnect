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
    FenPrincipale_configuration.cpp
FORMS += FenPrincipale.ui
HEADERS += FenPrincipale.h \
    serveur.h
OTHER_FILES += 
