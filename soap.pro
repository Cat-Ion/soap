#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T02:34:20
#
#-------------------------------------------------

QT       += core gui sql widgets

windows: {
    CONFIG += c++11
}

linux: {
    QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall
}

TARGET = soap
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    oildatabase.cpp \
    oil.cpp \
    soapmixer.cpp \
    soapingredient.cpp \
    soapproperties.cpp

HEADERS  += mainwindow.h \
    oildatabase.h \
    oil.h \
    soapmixer.h \
    soapingredient.h \
    soapproperties.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES +=
