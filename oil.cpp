#include "oil.h"
#include <QObject>


QHash<QString,Oil::Getter> init_ntg() {
    QHash<QString, Oil::Getter> ntg;
    ntg.insert(QObject::tr("Hardness"), &Oil::get_hardness);
    ntg.insert(QObject::tr("Cleansing"), &Oil::get_cleansing);
    ntg.insert(QObject::tr("Condition"), &Oil::get_condition);
    ntg.insert(QObject::tr("Bubbly"), &Oil::get_bubbly);
    ntg.insert(QObject::tr("Creamy"), &Oil::get_creamy);
    ntg.insert(QObject::tr("Iodine"), &Oil::get_iodine);
    ntg.insert(QObject::tr("INS"), &Oil::get_ins);
    ntg.insert(QObject::tr("Lauric"), &Oil::get_lauric);
    ntg.insert(QObject::tr("Myristic"), &Oil::get_myristic);
    ntg.insert(QObject::tr("Palmitic"), &Oil::get_palmitic);
    ntg.insert(QObject::tr("Stearic"), &Oil::get_stearic);
    ntg.insert(QObject::tr("Ricinoleic"), &Oil::get_ricinoleic);
    ntg.insert(QObject::tr("Oleic"), &Oil::get_oleic);
    ntg.insert(QObject::tr("Linoleic"), &Oil::get_linoleic);
    ntg.insert(QObject::tr("Linolenic"), &Oil::get_linolenic);

    return ntg;
}

const QHash<QString,Oil::Getter> Oil::name_to_getter = init_ntg();

QList<QString> init_keys() {
    QList<QString> l = init_ntg().keys();
    std::sort(l.begin(), l.end());
    l.insert(0, QObject::tr("Name"));
    return l;
}

const QList<QString> Oil::keys = init_keys();

QList<QString> init_fatty_acids() {
    QList<QString> l;
    l.append(QObject::tr("Lauric"));
    l.append(QObject::tr("Myristic"));
    l.append(QObject::tr("Palmitic"));
    l.append(QObject::tr("Stearic"));
    l.append(QObject::tr("Ricinoleic"));
    l.append(QObject::tr("Oleic"));
    l.append(QObject::tr("Linoleic"));
    l.append(QObject::tr("Linolenic"));
    return l;
}

QList<QString> init_qualities() {
    QList<QString> l;
    l.append(QObject::tr("Hardness"));
    l.append(QObject::tr("Cleansing"));
    l.append(QObject::tr("Condition"));
    l.append(QObject::tr("Bubbly"));
    l.append(QObject::tr("Creamy"));
    l.append(QObject::tr("Iodine"));
    l.append(QObject::tr("INS"));

    return l;
}

const QList<QString> Oil::fatty_acids = init_fatty_acids();

const QList<QString> Oil::qualities = init_qualities();



Oil::Oil(QString name,
         double hardness,
         double cleansing,
         double condition,
         double bubbly,
         double creamy,
         double iodine,
         double ins,
         double lauric,
         double myristic,
         double palmitic,
         double stearic,
         double ricinoleic,
         double oleic,
         double linoleic,
         double linolenic)
    : name(name),
      hardness(hardness),
      cleansing(cleansing),
      condition(condition),
      bubbly(bubbly),
      creamy(creamy),
      iodine(iodine),
      ins(ins),
      lauric(lauric),
      myristic(myristic),
      palmitic(palmitic),
      stearic(stearic),
      ricinoleic(ricinoleic),
      oleic(oleic),
      linoleic(linoleic),
      linolenic(linolenic)
{
}

Oil::Oil() {}

Oil::Getter Oil::get_getter(const QString &k) {
    return name_to_getter.value(k, &Oil::get_zero);
}

QString Oil::get_name() const { return name; }
double Oil::get_hardness() const { return hardness; }
double Oil::get_cleansing() const { return cleansing; }
double Oil::get_condition() const { return condition; }
double Oil::get_bubbly() const { return bubbly; }
double Oil::get_creamy() const { return creamy; }
double Oil::get_iodine() const { return iodine; }
double Oil::get_ins() const { return ins; }
double Oil::get_lauric() const { return lauric; }
double Oil::get_myristic() const { return myristic; }
double Oil::get_palmitic() const { return palmitic; }
double Oil::get_stearic() const { return stearic; }
double Oil::get_ricinoleic() const { return ricinoleic; }
double Oil::get_oleic() const { return oleic; }
double Oil::get_linoleic() const { return linoleic; }
double Oil::get_linolenic() const { return linolenic; }
double Oil::get_zero() const { return 0; }
double Oil::get_key(const QString &k) const {
    return (this->*get_getter(k))();
}
