#include <QJsonArray>
#include <QObject>
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "oildatabase.h"

QHash<QString,Oil> OilDatabase::oils;

void OilDatabase::load_database(const QString &file) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(file);
    db.open();

    QSqlQuery query(db);
    if(!query.exec("SELECT name, hardness, cleansing, condition, bubbly, creamy, iodine, sap, ins, lauric, myristic, palmitic, stearic, ricinoleic, oleic, linoleic, linolenic FROM \"oils\" ORDER BY name;")) {
        qDebug() << query.lastError().text();
    }

    while(query.next()) {
        oils.insert(query.value(0).toString(),
                    Oil(query.value(0).toString(),
                        query.value(1).toDouble(),
                        query.value(2).toDouble(),
                        query.value(3).toDouble(),
                        query.value(4).toDouble(),
                        query.value(5).toDouble(),
                        query.value(6).toDouble(),
                        query.value(7).toDouble(),
                        query.value(8).toDouble(),
                        query.value(9).toDouble(),
                        query.value(10).toDouble(),
                        query.value(11).toDouble(),
                        query.value(12).toDouble(),
                        query.value(13).toDouble(),
                        query.value(14).toDouble(),
                        query.value(15).toDouble(),
                        query.value(16).toDouble()
                        ));
    }
}

void OilDatabase::add_oil(const QJsonObject &data) {
    if(data["name"] == QJsonValue::Undefined || data["data"].toArray().size() < 16 || has_oil(data["name"].toString())) {
        return;
    }

    QJsonArray properties = data["data"].toArray();

    oils.insert(data["name"].toString(),
                Oil(data["name"].toString(),
                    properties[0].toDouble(),
                    properties[1].toDouble(),
                    properties[2].toDouble(),
                    properties[3].toDouble(),
                    properties[4].toDouble(),
                    properties[5].toDouble(),
                    properties[6].toDouble(),
                    properties[7].toDouble(),
                    properties[8].toDouble(),
                    properties[9].toDouble(),
                    properties[10].toDouble(),
                    properties[11].toDouble(),
                    properties[12].toDouble(),
                    properties[13].toDouble(),
                    properties[14].toDouble(),
                    properties[15].toDouble()));
}

Oil OilDatabase::get_oil(const QString &name) {
    return oils[name];
}

QList<Oil> OilDatabase::get_oils() {
    return oils.values();
}

QList<Oil> OilDatabase::get_sorted_oils(const QString &key, bool ascending) {
    QList<Oil> oils = get_oils();

    if(key == QObject::tr("Name")) {
        std::sort(oils.begin(),
                  oils.end(),
                  [ascending](const Oil &a, const Oil &b) {
            return (a.get_name() < b.get_name()) == ascending;
        });
    } else {
        Oil::Getter get_key = Oil::get_getter(key);

        std::sort(oils.begin(),
                  oils.end(),
                  [get_key, ascending](const Oil &a, const Oil &b) {
            auto ak = (a.*get_key)(),
                 bk = (b.*get_key)();
            if(ak == bk) {
                return false;
            } else {
                return (ak < bk) == ascending;
            }
        });
    }
    return oils;
}

bool OilDatabase::has_oil(const QString &name) {
    return oils.contains(name);
}

QJsonObject OilDatabase::oil_to_json(const QString &name) {
    QJsonObject ret;

    if(!has_oil(name)) {
        return ret;
    }

    Oil o = get_oil(name);

    ret["name"] = o.get_name();

    QJsonArray data_array;
    data_array.append(o.get_hardness());
    data_array.append(o.get_cleansing());
    data_array.append(o.get_condition());
    data_array.append(o.get_bubbly());
    data_array.append(o.get_creamy());
    data_array.append(o.get_iodine());
    data_array.append(o.get_sap());
    data_array.append(o.get_ins());
    data_array.append(o.get_lauric());
    data_array.append(o.get_myristic());
    data_array.append(o.get_palmitic());
    data_array.append(o.get_stearic());
    data_array.append(o.get_ricinoleic());
    data_array.append(o.get_oleic());
    data_array.append(o.get_linoleic());
    data_array.append(o.get_linolenic());

    ret["data"] = data_array;

    return ret;
}
