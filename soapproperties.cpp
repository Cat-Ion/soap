#include <QObject>
#include "soapproperties.h"

QHash<QString,double> SoapProperties::calculate(OilDatabase &db, QList<const SoapIngredient> *ingredients) {
    QHash<QString,double> retval;

    double total_weight = 0;

    for(QString key : Oil::keys) {
        if(key == QObject::tr("Name")) {
            continue;
        }

        retval[key] = 0;
    }

    for(auto it = ingredients->constBegin(); it < ingredients->constEnd(); it++) {
        Oil oil = db.get_oil(it->get_name());
        double weight = it->get_weight();
        total_weight += it->get_weight();

        for(QString key : Oil::keys) {
            if(key == QObject::tr("Name")) {
                continue;
            }

            retval[key] += weight * oil.get_key(key);
        }
    }

    for(auto key : retval.keys()) {
        retval[key] /= total_weight;
    }

    return retval;
}
