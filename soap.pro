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

DESTDIR = bin
TARGET = soap
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/oildatabase.cpp \
    src/oil.cpp \
    src/soapmixer.cpp \
    src/soapingredient.cpp \
    src/soapproperties.cpp

HEADERS  += include/mainwindow.h \
    include/oildatabase.h \
    include/oil.h \
    include/soapmixer.h \
    include/soapingredient.h \
    include/soapproperties.h

INCLUDEPATH += "include"

FORMS    += forms/mainwindow.ui

OTHER_FILES +=

RESOURCES +=
