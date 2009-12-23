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
    processus.cpp
FORMS += FenPrincipale.ui
HEADERS += FenPrincipale.h \
    serveur.h \
    processus.h
OTHER_FILES += 
