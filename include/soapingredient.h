#ifndef SOAPINGREDIENT_H
#define SOAPINGREDIENT_H
#include <QJsonObject>
#include <QString>
#include "oil.h"

class SoapIngredient
{
public:
    SoapIngredient(const QString &name, double weight, double mass);

    Oil get_oil() const;
    QString get_name() const;

    double get_mass() const;
    double get_weight() const;

    void set_mass(double new_mass);
    void set_weight(double new_weight);

    QJsonObject to_json() const;

    static SoapIngredient from_json(const QJsonObject &obj);

private:
    QString name;
    double weight;
    double mass;
};

#endif // SOAPINGREDIENT_H
