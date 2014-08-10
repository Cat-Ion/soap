#include "soapmixer.h"
#include "soapproperties.h"
#include <QDebug>

SoapMixer::SoapMixer()
    : QAbstractListModel(),
      oils(),
      lye_type(NaOH),
      weight_unit(Grams),
      water_type(Ratio),
      mass(500),
      super_fat(5),
      water(2),
      weight_sum(0)
{
}

int SoapMixer::rowCount(const QModelIndex &parent) const {
    return oils.size();
}

int SoapMixer::columnCount(const QModelIndex &parent) const {
    return SoapMixer::ColumnType::Number;
}

QVariant SoapMixer::data(const QModelIndex &index, int role) const {
    if(!index.isValid()) {
        return QVariant();
    }
    if(index.row() > oils.size() ||
       index.column() >= SoapMixer::ColumnType::Number) {
        return QVariant();
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole) {
        switch(index.column()) {
        case Name: return oils[index.row()].get_name();
        case Weight: return oils[index.row()].get_weight();
        case Mass: return oils[index.row()].get_mass();
        }
    }
    return QVariant();
}

QVariant SoapMixer::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role != Qt::DisplayRole) {
        return QVariant();
    }

    if(orientation == Qt::Horizontal) {
        switch(section) {
        case SoapMixer::ColumnType::Name: return QString("Name");
        case SoapMixer::ColumnType::Weight: return QString("Weight");
        case SoapMixer::ColumnType::Mass: return QString("Mass");
        }
    }
    if(orientation == Qt::Vertical) {
        return QString("Row %1").arg(section + 1);
    }

    return QVariant();
}

Qt::ItemFlags SoapMixer::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    if(index.column() == SoapMixer::ColumnType::Name) {
        return QAbstractItemModel::flags(index);
    } else {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }
}

bool SoapMixer::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() &&
            index.row() < oils.size() &&
            role == Qt::EditRole) {
        switch(index.column()) {
        case Weight:
            set_oil_weight(index.row(), value.toDouble());
            break;

        case Mass:
            set_oil_mass(index.row(), value.toDouble());
            break;

        default:
            return false;
        }


        return true;
    }
    return false;
}

double SoapMixer::calculate_lye_amount() const {
    return mass * SoapProperties::calculate_property(get_oils(), tr("Sap")) * sap_multiplier() * (1.-super_fat/100.);
}

double SoapMixer::calculate_water_amount() const {
    switch(water_type) {
    case Percentage:
        return mass * water / 100;
    case Ratio:
        return calculate_lye_amount() * water;
    case Concentration:
        return calculate_lye_amount() / water * 100;
    default:
        return 0;
    }
}

SoapMixer::LyeType SoapMixer::get_lye_type() const {
    return lye_type;
}

void SoapMixer::set_lye_type(SoapMixer::LyeType new_type) {
    lye_type = new_type;
    emit_signals();
}

SoapMixer::WeightUnit SoapMixer::get_weight_unit() const {
    return weight_unit;
}

void SoapMixer::set_weight_unit(WeightUnit new_unit) {
    weight_unit = new_unit;
}

QList<const SoapIngredient> *SoapMixer::get_oils() const {
    return reinterpret_cast<QList<const SoapIngredient> *> (const_cast<QList<SoapIngredient> *>(&oils));
}

void SoapMixer::add_oil(const QString &oil) {
    if(oils.size() == 0) {
        beginInsertRows(QModelIndex(), oils.size(), oils.size());
        oils.append(SoapIngredient(oil, 1, mass));

        recalculate_indices();
        recalculate_weight_sum();
        endInsertRows();
    } else if(!oil_to_index.contains(oil)) {
        beginInsertRows(QModelIndex(), oils.size(), oils.size());
        oils.append(SoapIngredient(oil, 0, 0));

        recalculate_indices();
        endInsertRows();
    }
}

void SoapMixer::remove_oil(int index) {
    beginRemoveRows(QModelIndex(), index, index);
    oils.removeAt(index);

    recalculate_weight_sum();
    recalculate_indices();
    endRemoveRows();
}

void SoapMixer::remove_oil(QModelIndex index) {
    if(index.isValid() && index.row() >= 0 && index.row() < oils.size()) {
        remove_oil(index.row());
    }
}

void SoapMixer::remove_oil(const QString &oil) {
    if(oil_to_index.contains(oil)) {
        remove_oil(oil_to_index[oil]);
    }
}

double SoapMixer::get_oil_mass(int index) const {
    return get_oil_weight(index) * mass / weight_sum;
}

double SoapMixer::get_oil_mass(const QString &oil) const {
    return get_oil_weight(oil) * mass / weight_sum;
}

void SoapMixer::set_oil_mass(int index, double new_mass) {
    if(oils.size() != 1) {
        mass -= oils[index].get_mass();
        weight_sum -= oils[index].get_weight();

        oils[index].set_mass(new_mass);
        oils[index].set_weight(new_mass/mass * weight_sum);

        weight_sum += new_mass/mass * weight_sum;
        mass += new_mass;
    } else {
        oils[index].set_mass(new_mass);
        oils[index].set_weight(1);

        mass = new_mass;
    }


    recalculate_weight_sum();
    emit mass_changed(mass);
    emit dataChanged(this->index(index, ColumnType::Weight),
                     this->index(index, ColumnType::Mass));
}

void SoapMixer::set_oil_mass(const QString &oil, double new_mass) {
    if(!oil_to_index.contains(oil)) {
        add_oil(oil);
    }
    set_oil_mass(oil_to_index[oil], new_mass);
}

double SoapMixer::get_oil_weight(int index) const {
    return oils[index].get_weight();
}

double SoapMixer::get_oil_weight(const QString &oil) const {
    if(oil_to_index.contains(oil)) {
        return get_oil_weight(oil_to_index[oil]);
    } else {
        return 0;
    }
}

void SoapMixer::set_oil_weight(int index, double new_weight) {
    oils[index].set_weight(new_weight);
    recalculate_weight_sum();
    recalculate_masses();
    emit dataChanged(this->index(0, ColumnType::Mass),
                     this->index(oils.size()-1, ColumnType::Mass));
    emit dataChanged(this->index(index, ColumnType::Weight),
                     this->index(index, ColumnType::Weight));
}

void SoapMixer::set_oil_weight(const QString &oil, double new_weight) {
    if(!oil_to_index.contains(oil)) {
        add_oil(oil);
    }
    set_oil_weight(oil_to_index[oil], new_weight);
}

double SoapMixer::get_super_fat() const {
    return super_fat;
}

void SoapMixer::set_super_fat(double new_super_fat) {
    super_fat = new_super_fat;
    emit_signals();
}

double SoapMixer::get_total_mass() const {
    return mass;
}

void SoapMixer::set_total_mass(double new_mass) {
    mass = new_mass;
    recalculate_masses();
    emit mass_changed(new_mass);
}

double SoapMixer::get_water() const {
    return water;
}

void SoapMixer::set_water(double new_water) {
    water = new_water;
    emit_signals();
}

SoapMixer::WaterType SoapMixer::get_water_type() const {
    return water_type;
}

void SoapMixer::set_water_type(WaterType new_water_type) {
    water_type = new_water_type;
    emit_signals();
}

void SoapMixer::emit_signals() {
    double lye_amount = calculate_lye_amount();
    double water_amount = calculate_water_amount();
    emit lye_amount_changed(lye_amount);
    emit lye_amount_changed(QString("%1 %2").arg(lye_amount, 0, 'g', 3).arg(unit_name()));
    emit water_amount_changed(water_amount);
    emit water_amount_changed(QString("%1 %2").arg(water_amount, 0, 'g', 3).arg(unit_name()));
}

void SoapMixer::recalculate_indices() {
    oil_to_index.clear();
    for(int i = 0; i < oils.size(); i++) {
        oil_to_index[oils[i].get_name()] = i;
    }
}

void SoapMixer::recalculate_masses() {
    for(SoapIngredient &oil : oils) {
        oil.set_mass(oil.get_weight() * mass / weight_sum);
    }
    emit dataChanged(this->index(0, ColumnType::Mass),
                     this->index(oils.size()-1, ColumnType::Mass));
    emit_signals();
}

void SoapMixer::recalculate_weight_sum() {
    weight_sum = std::accumulate(oils.constBegin(),
                                 oils.constEnd(),
                                 0.0,
                                 [](const double &a, const SoapIngredient &b) {
                                     return a + b.get_weight();
                                 });
    emit_signals();
}

double SoapMixer::sap_multiplier() const {
    switch(lye_type) {
    case NaOH:
        return 1./1.403;
    case KOH:
        return 1;
    case KOH_90:
        return 1./0.9;
    default:
        return 0;
    }
}

QString SoapMixer::unit_name() const {
    switch(weight_unit) {
    case Grams: return tr("g");
    case Pounds: return tr("lb");
    case Ounces: return tr("oz");
    default: return tr("");
    }
}
