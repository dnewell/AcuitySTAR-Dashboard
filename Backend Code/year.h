#ifndef YEAR_H
#define YEAR_H
#include <QVector>
#include "entry.h"

class Year
{
public:

    int date;
    int tothours;
    int totstudents;
    QVector<Entry> list;

    Year();
    Year(int, int, int);
};

#endif // YEAR_H
