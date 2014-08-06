#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QTranslator translator;
    QApplication a(argc, argv);
    translator.load("soap_de");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
