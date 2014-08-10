#ifndef OILDATABASE_H
#define OILDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QHash>
#include <QList>
#include "oil.h"

class OilDatabase
{
public:
    static void load_database(const QString &file);
    static Oil get_oil(const QString &name);
    static QList<Oil> get_oils();
    static QList<Oil> get_sorted_oils(const QString &key, bool ascending);
private:
    static QHash<QString,Oil> oils;
};

#endif // OILDATABASE_H
