#ifndef SOAPPROPERTIES_H
#define SOAPPROPERTIES_H
#include <QHash>
#include <QList>
#include "oildatabase.h"
#include "soapingredient.h"

class SoapProperties
{
public:
    static QHash<QString,double> calculate(OilDatabase &db, QList<const SoapIngredient> *ingredients);
    static double calculate_property(OilDatabase &db, QList<const SoapIngredient> *ingredients, QString property);
};

#endif // SOAPPROPERTIES_H
