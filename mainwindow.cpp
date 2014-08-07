#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    weight_unit(Grams),
    lye_type(NaOH),
    sort_increasing(true),
    ui(new Ui::MainWindow),
    oils("oils.sqlite")
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    ui->sort_by_property->addItems(Oil::keys);

    sort_oils_by(tr("Name"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggle_sort_order() {
    sort_increasing = !sort_increasing;
    if(sort_increasing) {
        ui->sort_order_incdec_button->setText(tr("increasing"));
    } else {
        ui->sort_order_incdec_button->setText(tr("decreasing"));
    }
    sort_oils_by(ui->sort_by_property->currentText());
}

void MainWindow::sort_oils_by(const QString &key) {
    ui->oil_list->clear();

    for(auto &oil : oils.get_sorted_oils(key, sort_increasing)) {
        ui->oil_list->addItem(oil.get_name());
    }
}
