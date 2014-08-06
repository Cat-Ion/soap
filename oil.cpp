#include "oil.h"
#include <QObject>

QHash<QString,double(Oil::*)()const> Oil::name_to_getter;

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
    if(name_to_getter.size() == 0) {
        name_to_getter.insert(QObject::tr("Hardness"), &Oil::get_hardness);
        name_to_getter.insert(QObject::tr("Cleansing"), &Oil::get_cleansing);
        name_to_getter.insert(QObject::tr("Condition"), &Oil::get_condition);
        name_to_getter.insert(QObject::tr("Bubbly"), &Oil::get_bubbly);
        name_to_getter.insert(QObject::tr("Creamy"), &Oil::get_creamy);
        name_to_getter.insert(QObject::tr("Iodine"), &Oil::get_iodine);
        name_to_getter.insert(QObject::tr("INS"), &Oil::get_ins);
        name_to_getter.insert(QObject::tr("Lauric"), &Oil::get_lauric);
        name_to_getter.insert(QObject::tr("Myristic"), &Oil::get_myristic);
        name_to_getter.insert(QObject::tr("Palmitic"), &Oil::get_palmitic);
        name_to_getter.insert(QObject::tr("Stearic"), &Oil::get_stearic);
        name_to_getter.insert(QObject::tr("Ricinoleic"), &Oil::get_ricinoleic);
        name_to_getter.insert(QObject::tr("Oleic"), &Oil::get_oleic);
        name_to_getter.insert(QObject::tr("Linoleic"), &Oil::get_linoleic);
        name_to_getter.insert(QObject::tr("Linolenic"), &Oil::get_linolenic);
    }
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
