#include <QObject>
#include "soapproperties.h"

QHash<QString,double> SoapProperties::calculate(OilDatabase &db, QList<const SoapIngredient> *ingredients) {
    QHash<QString,double> retval;

    for(QString key : Oil::keys) {
        if(key == QObject::tr("Name")) {
            continue;
        }

        retval[key] = calculate_property(db, ingredients, key);
    }

    return retval;
}

double SoapProperties::calculate_property(OilDatabase &db, QList<const SoapIngredient> *ingredients, QString property) {
    double ret = 0;
    double total_weight = 0;
    for(auto it = ingredients->constBegin(); it < ingredients->constEnd(); it++) {
        Oil oil = db.get_oil(it->get_name());
        total_weight += it->get_weight();
        ret += it->get_weight() * oil.get_key(property);
    }
    return ret / total_weight;
}
