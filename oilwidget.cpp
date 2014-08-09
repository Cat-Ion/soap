#include "oilwidget.h"
#include "ui_oilwidget.h"

OilWidget::OilWidget(QWidget *parent) :
    QAbstractItemDelegate(parent),
    ui(new Ui::OilWidget())
{
}

OilWidget::~OilWidget()
{
    delete ui;
}

