#ifndef OILWIDGET_H
#define OILWIDGET_H

#include <QWidget>
#include <QAbstractItemDelegate>

namespace Ui {
class OilWidget;
}

class OilWidget : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    OilWidget(QWidget *parent = 0);
    ~OilWidget();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    Ui::OilWidget *ui;
};

#endif // OILWIDGET_H
