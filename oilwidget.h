#ifndef OILWIDGET_H
#define OILWIDGET_H

#include <QWidget>

namespace Ui {
class OilWidget;
}

class OilWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OilWidget(QWidget *parent = 0);
    ~OilWidget();

private:
    Ui::OilWidget *ui;
};

#endif // OILWIDGET_H
