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
    void open_load_dialog();
    void open_save_dialog();
    void refresh_soap();
    void show_current_oil_properties(const QString &oil);
    void show_current_oil_properties_from_ingredients(QModelIndex);
    void sort_oils_by(const QString &key);
    void toggle_sort_order();

private slots:
    void add_list_item_to_soap(QListWidgetItem *);

    void set_soap_lye_type_naoh();
    void set_soap_lye_type_koh();
    void set_soap_lye_type_koh_90();
    void set_soap_water_type_concentration();
    void set_soap_water_type_percentage();
    void set_soap_water_type_ratio();

signals:


private:
    bool sort_increasing;

    Ui::MainWindow *ui;
    QHash<QString,QList<QLineEdit*> > oil_key_fields;
    SoapMixer soap;

    bool eventFilter(QObject *, QEvent *);

};

#endif // MAINWINDOW_H
