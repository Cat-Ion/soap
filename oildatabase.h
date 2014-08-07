#ifndef OILDATABASE_H
#define OILDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QHash>
#include <QList>
#include "oil.h"

class OilDatabase
{
public:
    OilDatabase(const QString &file);

    Oil get_oil(const QString &name);
    QList<Oil> get_oils();
    QList<Oil> get_sorted_oils(const QString &key, bool ascending);
private:
    QSqlDatabase db;
    QHash<QString,Oil> oils;
};

#endif // OILDATABASE_H
