#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "oildatabase.h"

OilDatabase::OilDatabase(const QString &file)
 : db(QSqlDatabase::addDatabase("QSQLITE"))
{
    db.setDatabaseName(file);
    db.open();

    QSqlQuery query(db);
    if(!query.exec("SELECT name, hardness, cleansing, condition, bubbly, creamy, iodine, ins, lauric, myristic, palmitic, stearic, ricinoleic, oleic, linoleic, linolenic FROM \"oils\" ORDER BY name;")) {
        qDebug() << query.lastError().text();
    }

    while(query.next()) {
        qDebug() << query.value(0).toString();
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
                        query.value(15).toDouble()
                        ));
    }

}

Oil OilDatabase::get_oil(const QString &name) {
    return oils[name];
}

QList<Oil> OilDatabase::get_oils() {
    return oils.values();
}
