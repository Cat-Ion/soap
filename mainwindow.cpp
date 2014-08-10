#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soapproperties.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    weight_unit(Grams),
    sort_increasing(true),
    ui(new Ui::MainWindow),
    oils("oils.sqlite")
{
    ui->setupUi(this);

    ui->sort_by_property->addItems(Oil::keys);

    ui->ingredient_table->setSelectionMode(QListView::SingleSelection);

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

        ((QGridLayout*)(ui->tab_properties->layout()))->addWidget(new QLabel(quality), 1 + index, 0);
        ((QGridLayout*)(ui->tab_properties->layout()))->addWidget(one, 1 + index, 1);
        ((QGridLayout*)(ui->tab_properties->layout()))->addWidget(all, 1 + index, 2);

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

        ((QGridLayout*)(ui->tab_fatty_acids->layout()))->addWidget(new QLabel(fatty_acid), 1 + index, 0);
        ((QGridLayout*)(ui->tab_fatty_acids->layout()))->addWidget(one, 1 + index, 1);
        ((QGridLayout*)(ui->tab_fatty_acids->layout()))->addWidget(all, 1 + index, 2);
    }

    sort_oils_by(tr("Name"));

    ui->ingredient_table->setModel(&soap);
    ui->ingredient_table->setFixedWidth(400);
    ui->ingredient_table->verticalHeader()->hide();
    ui->ingredient_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->ingredient_table->setColumnWidth(0, 280);
    ui->ingredient_table->setColumnWidth(1, 60);
    ui->ingredient_table->setColumnWidth(2, 60);
    ui->ingredient_table->installEventFilter(this);

    connect(ui->oil_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(add_list_item_to_soap(QListWidgetItem*)));

    connect(ui->weight_grams, SIGNAL(valueChanged(double)),
            &soap, SLOT(set_total_mass(double)));

    connect(&soap, SIGNAL(mass_changed(double)),
            ui->weight_grams, SLOT(setValue(double)));
    connect(&soap, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(refresh_soap()));

    connect(ui->ingredient_table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(show_current_oil_properties_from_ingredients(QModelIndex)));

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
    qDebug() << "1" << oils.get_oils().size();
    sort_oils_by(ui->sort_by_property->currentText());
}

void MainWindow::sort_oils_by(const QString &key) {
    QList<Oil> sorted_oils = oils.get_sorted_oils(key, sort_increasing);

    QListWidgetItem *current = ui->oil_list->currentItem();
    QString current_oil;
    if(current) {
        current_oil = current->text();
    }

    ui->oil_list->clear();

    for(auto &oil : sorted_oils) {
        ui->oil_list->addItem(QString(oil.get_name()));
        if(oil.get_name() == current_oil) {
            ui->oil_list->setCurrentRow(ui->oil_list->count()-1);
        }
    }
}

void MainWindow::show_current_oil_properties(const QString &oil_name) {
    if(oil_name == tr("")) {
        for(auto key: Oil::keys) {
            if(key == tr("Name")) {
                continue;
            }
            oil_key_fields[key][0]->setText("");
        }
    } else {
        Oil oil = oils.get_oil(oil_name);

        for(auto key: Oil::keys) {
            if(key == tr("Name")) continue;
            oil_key_fields[key][0]->setText(QString::number(oil.get_key(key), 'g', 3));
        }
    }
}

void MainWindow::show_current_oil_properties_from_ingredients(QModelIndex index) {
    if(soap.get_oils()->size() == 0 ||
       !index.isValid()) {
        return;
    }
    show_current_oil_properties(soap.get_oils()->at(index.row()).get_name());
}

void MainWindow::add_list_item_to_soap(QListWidgetItem *i) {
    soap.add_oil(i->text());
}

void MainWindow::refresh_soap() {
    QHash<QString,double> properties = SoapProperties::calculate(oils, soap.get_oils());
    for(auto key : properties.keys()) {
        oil_key_fields[key][1]->setText(QString::number(properties[key], 'g', 3));
    }
}

bool MainWindow::eventFilter(QObject *o, QEvent *e) {
    if(o == ui->ingredient_table && e->type() == QEvent::KeyPress) {
        QKeyEvent *k = static_cast<QKeyEvent*> (e);
        if(k->key() == Qt::Key_Delete) {
            if(ui->ingredient_table->selectionModel()->selection().indexes().size() > 0) {
                soap.remove_oil(ui->ingredient_table->selectionModel()->selection().indexes()[0]);
                return true;
            }
        }
    }
    return QObject::eventFilter(o, e);
}
