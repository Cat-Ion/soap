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
    enum LyeType { NaOH = 0, KOH = 1, KOH_90 = 2 };
    enum WeightUnit { Grams = 0, Pounds = 1, Ounces = 2 };
    enum WaterType { Percentage = 0, Concentration = 1, Ratio = 2 };

    SoapMixer();

    // Needed to implement QAbstractListModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation = Qt::Vertical, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    double calculate_lye_amount() const;
    double calculate_water_amount() const;

    LyeType get_lye_type() const;
    QList<const SoapIngredient> *get_oils() const;
    double get_oil_mass(int index) const;
    double get_oil_mass(const QString &oil) const;
    double get_oil_weight(int index) const;
    double get_oil_weight(const QString &oil) const;
    double get_super_fat() const;
    double get_total_mass() const;
    double get_water() const;
    WaterType get_water_type() const;
    WeightUnit get_weight_unit() const;

    void set_lye_type(LyeType new_type);
    void set_oil_mass(int index, double new_mass);
    void set_oil_mass(const QString &oil, double new_mass);
    void set_oil_weight(int index, double new_weight);
    void set_oil_weight(const QString &oil, double new_weight);
    void set_water_type(WaterType new_water_type);
    void set_weight_unit(WeightUnit new_unit);
    QString unit_name_long(bool uppercase = false) const;
    QString unit_name_short() const;

    void save_to_file(QString filename) const;
    bool load_from_file(QString filename);

public slots:
    void add_oil(const QString &oil);
    void remove_oil(const QString &oil);
    void remove_oil(int index);
    void remove_oil(QModelIndex index);
    void set_super_fat(double new_super_fat);
    void set_total_mass(double new_mass);
    void set_water(double new_water);

signals:
    void mass_changed(double);
    void lye_amount_changed(double);
    void lye_amount_changed(QString);
    void water_amount_changed(double);
    void water_amount_changed(QString);

private:
    enum ColumnType {
        Name = 0,
        Weight = 1,
        Mass = 2,
        Number = 3
    };

    QHash<QString,int> oil_to_index;
    QList<SoapIngredient> oils;

    LyeType lye_type;
    WeightUnit weight_unit;
    WaterType water_type;

    double mass;
    double super_fat;
    double water;
    double weight_sum;

    void emit_signals();
    void recalculate_indices();
    void recalculate_masses();
    void recalculate_weight_sum();
    double sap_multiplier() const;
};

#endif // SOAPMIXER_H
