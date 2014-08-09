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
};

#endif // SOAPPROPERTIES_H
