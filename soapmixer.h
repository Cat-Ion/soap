#ifndef SOAPMIXER_H
#define SOAPMIXER_H
#include <QAbstractListModel>
#include <QHash>
#include <QList>
#include "oildatabase.h"
#include "soapingredient.h"
#include "oil.h"
class SoapMixer : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LyeType { NaOH, KOH, KOH_90 };

    SoapMixer();

    // Needed to implement QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Vertical, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    LyeType get_lye_type() const;
    QList<const SoapIngredient> *get_oils() const;
    double get_oil_mass(int index) const;
    double get_oil_mass(const QString &oil) const;
    double get_oil_weight(int index) const;
    double get_oil_weight(const QString &oil) const;
    double get_total_mass() const;

    void set_oil_mass(int index, double new_mass);
    void set_oil_mass(const QString &oil, double new_mass);
    void set_oil_weight(int index, double new_weight);
    void set_oil_weight(const QString &oil, double new_weight);

public slots:
    void set_lye_type(LyeType new_type);
    void add_oil(const QString &oil);
    void remove_oil(const QString &oil);
    void set_total_mass(double new_mass);

signals:
    void mass_changed(double);

private:
    enum ColumnType {
        Name = 0,
        Weight = 1,
        Mass = 2,
        Number = 3
    };

    // Contains oil:weight pairs.
    QHash<QString,int> oil_to_index;
    QList<SoapIngredient> oils;
    LyeType lye_type;

    double mass;
    double weight_sum;

    void recalculate_indices();
    void recalculate_masses();
    void recalculate_weight_sum();
};

#endif // SOAPMIXER_H
