#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void set_lye_type_naoh();
    void set_lye_type_koh();
    void set_lye_type_koh_90();

    void new_weight_grams(double);
    void new_weight_pounds(double);
    void new_weight_ounces(double);

    void set_weight_unit_grams();
    void set_weight_unit_pounds();
    void set_weight_unit_ounces();

    void sort_oils_by(const QString &key, bool ascending);

signals:
    void set_weight_grams(double);
    void set_weight_pounds(double);
    void set_weight_ounces(double);


private:
    enum WeightUnit { Grams, Pounds, Ounces } weight_unit;
    enum LyeType { NaOH, KOH, KOH_90 } lye_type;

    Ui::MainWindow *ui;
    OilDatabase oils;

    void calculate_lye();
};

#endif // MAINWINDOW_H
