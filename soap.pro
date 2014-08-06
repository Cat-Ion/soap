#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T02:34:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = soap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oilwidget.cpp \
    oildatabase.cpp \
    oil.cpp

HEADERS  += mainwindow.h \
    oilwidget.h \
    oildatabase.h \
    oil.h

FORMS    += mainwindow.ui \
    oilwidget.ui

TRANSLATIONS = soap_de.ts

OTHER_FILES += \
    soap_de.ts
