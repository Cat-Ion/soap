#ifndef OILDATABASE_H
#define OILDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QHash>
#include <QList>
#include <QJsonObject>
#include "oil.h"

class OilDatabase
{
public:
    static void load_database(const QString &file);
    static void add_oil(const QJsonObject &data);
    static Oil get_oil(const QString &name);
    static QList<Oil> get_oils();
    static QList<Oil> get_sorted_oils(const QString &key, bool ascending);
    static bool has_oil(const QString &name);
    static QJsonObject oil_to_json(const QString &name);

private:
    static QHash<QString,Oil> oils;
};

#endif // OILDATABASE_H
