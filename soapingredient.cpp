#include "soapingredient.h"
#include "oildatabase.h"

SoapIngredient::SoapIngredient(const QString &name, double weight, double mass)
    : name(name),
      weight(weight),
      mass(mass)
{
}

void SoapIngredient::set_mass(double new_mass) {
    if(new_mass < 0) new_mass = 0;
    mass = new_mass;
}

void SoapIngredient::set_weight(double new_weight) {
    if(new_weight < 0) new_weight = 0;
    weight = new_weight;
}

Oil SoapIngredient::get_oil() const {
    return OilDatabase::get_oil(name);
}

QString SoapIngredient::get_name() const {
    return name;
}

double SoapIngredient::get_mass() const {
    return mass;
}

double SoapIngredient::get_weight() const {
    return weight;
}

QJsonObject SoapIngredient::to_json() const {
    QJsonObject ret;

    ret["oil"] = get_name();
    ret["weight"] = get_weight();

    return ret;
}

SoapIngredient SoapIngredient::from_json(const QJsonObject &obj) {
    return SoapIngredient(obj["oil"].toString(), obj["weight"].toDouble(), 0);
}
