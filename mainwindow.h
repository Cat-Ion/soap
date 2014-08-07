#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>
#include <QLineEdit>
#include "oildatabase.h"

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
    void show_current_oil_properties(const QString &oil);
    void toggle_sort_order();
    void sort_oils_by(const QString &key);

signals:


private:
    enum WeightUnit { Grams, Pounds, Ounces } weight_unit;
    enum LyeType { NaOH, KOH, KOH_90 } lye_type;
    bool sort_increasing;

    Ui::MainWindow *ui;
    OilDatabase oils;
    QHash<QString,QList<QLineEdit*> > oil_key_fields;

    void calculate_lye();
};

#endif // MAINWINDOW_H
