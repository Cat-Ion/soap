#ifndef OIL_H
#define OIL_H
#include <QString>
#include <QHash>

class Oil
{
public:
    typedef double (Oil::*Getter)()const;

    Oil(QString name,
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
        double linolenic);
    Oil();

    QString get_name() const;
    double get_hardness() const;
    double get_cleansing() const;
    double get_condition() const;
    double get_bubbly() const;
    double get_creamy() const;
    double get_iodine() const;
    double get_ins() const;
    double get_lauric() const;
    double get_myristic() const;
    double get_palmitic() const;
    double get_stearic() const;
    double get_ricinoleic() const;
    double get_oleic() const;
    double get_linoleic() const;
    double get_linolenic() const;
    double get_key(const QString &k) const;

    static Getter get_getter(const QString &k);

private:
    QString name;
    double hardness, cleansing, condition, bubbly, creamy, iodine, ins;
    double lauric, myristic, palmitic, stearic, ricinoleic, oleic, linoleic, linolenic;

    double get_zero() const;
    static QHash<QString, Getter> name_to_getter;
};

#endif // OIL_H
