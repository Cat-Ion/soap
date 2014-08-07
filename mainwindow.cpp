#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
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

    for(auto quality : Oil::qualities) {
        int index = Oil::qualities.indexOf(quality);

        QList<QLineEdit*> list;
        list.append(new QLineEdit());
        list.append(new QLineEdit());

        QLineEdit *one = list[0],
                  *all = list[1];
        one->setReadOnly(true);
        all->setReadOnly(true);

        oil_key_fields.insert(quality, list);

        ((QGridLayout*)(ui->qualities_groupbox->layout()))->addWidget(new QLabel(quality), 1 + index, 0);
        ((QGridLayout*)(ui->qualities_groupbox->layout()))->addWidget(one, 1 + index, 1);
        ((QGridLayout*)(ui->qualities_groupbox->layout()))->addWidget(all, 1 + index, 2);
    }

    for(auto fatty_acid : Oil::fatty_acids) {
        int index = Oil::fatty_acids.indexOf(fatty_acid);

        QList<QLineEdit*> list;
        list.append(new QLineEdit());
        list.append(new QLineEdit());

        QLineEdit *one = list[0],
                  *all = list[1];
        one->setReadOnly(true);
        all->setReadOnly(true);

        oil_key_fields.insert(fatty_acid, list);

        ((QGridLayout*)(ui->acids_groupbox->layout()))->addWidget(new QLabel(fatty_acid), 1 + index, 0);
        ((QGridLayout*)(ui->acids_groupbox->layout()))->addWidget(one, 1 + index, 1);
        ((QGridLayout*)(ui->acids_groupbox->layout()))->addWidget(all, 1 + index, 2);
    }

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

void MainWindow::show_current_oil_properties(const QString &oil_name) {
    Oil oil = oils.get_oil(oil_name);

    for(auto key: Oil::keys) {
        if(key == tr("Name")) continue;
        oil_key_fields[key][0]->setText(QString::number(oil.get_key(key), 'g', 3));
    }
}
