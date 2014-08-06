#include "oilwidget.h"
#include "ui_oilwidget.h"

OilWidget::OilWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OilWidget)
{
    ui->setupUi(this);
}

OilWidget::~OilWidget()
{
    delete ui;
}
