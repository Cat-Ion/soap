#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QLineEdit>
#include <QListWidgetItem>
#include <QModelIndex>
#include "oildatabase.h"
#include "soapmixer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void refresh_soap();
    void show_current_oil_properties(const QString &oil);
    void sort_oils_by(const QString &key);
    void toggle_sort_order();

private slots:
    void add_list_item_to_soap(QListWidgetItem *);

signals:


private:
    enum WeightUnit { Grams, Pounds, Ounces } weight_unit;
    bool sort_increasing;

    Ui::MainWindow *ui;
    OilDatabase oils;
    QHash<QString,QList<QLineEdit*> > oil_key_fields;
    SoapMixer soap;

};

#endif // MAINWINDOW_H
