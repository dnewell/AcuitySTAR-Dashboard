#ifndef YEAR_H
#define YEAR_H
#include <QVector>
#include "entry.h"

class Year
{
public:

    int date;
    double tothours;
    int totstudents;

    QVector<Entry> list;

    Year();
    Year(int, double, int);
};

#endif // YEAR_H
