#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    weight_unit(Grams),
    lye_type(NaOH),
    ui(new Ui::MainWindow),
    oils("oils.sqlite")
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    sort_oils_by(tr("Hardness"), false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_lye_type_naoh()   { lye_type = NaOH;   calculate_lye(); }
void MainWindow::set_lye_type_koh()    { lye_type = KOH;    calculate_lye(); }
void MainWindow::set_lye_type_koh_90() { lye_type = KOH_90; calculate_lye(); }

void MainWindow::set_weight_unit_grams() { weight_unit = Grams; }

void MainWindow::new_weight_grams(double v) {
    if(weight_unit == Grams) {
        emit set_weight_pounds(v/453.592);
        emit set_weight_ounces(v/28.3495);
    }
}

void MainWindow::set_weight_unit_pounds() { weight_unit = Pounds; }

void MainWindow::new_weight_pounds(double v) {
    if(weight_unit == Pounds) {
        emit set_weight_grams(v*453.592);
        emit set_weight_ounces(v*16);
    }
}

void MainWindow::set_weight_unit_ounces() { weight_unit = Ounces; }

void MainWindow::new_weight_ounces(double v) {
    if(weight_unit == Ounces) {
        emit set_weight_grams(v*28.3495);
        emit set_weight_pounds(v/16);
    }
}
void MainWindow::calculate_lye() {

}

void MainWindow::sort_oils_by(const QString &key, bool ascending) {
    QList<Oil> oil_list = oils.get_oils();

    ui->oil_list->clear();

    if(key == tr("Name")) {
        std::sort(oil_list.begin(),
                  oil_list.end(),
                  [ascending](const Oil &a, const Oil &b) { return (a.get_name() < b.get_name()) == ascending; });
    } else {
        Oil::Getter get_key = Oil::get_getter(key);
        std::sort(oil_list.begin(),
                  oil_list.end(),
                  [get_key, ascending](const Oil &a, const Oil &b) {
            return ((a.*get_key)() < (b.*get_key)()) == ascending; });
    }

    for(auto &oil : oil_list) {
        ui->oil_list->addItem(oil.get_name());
    }
}
