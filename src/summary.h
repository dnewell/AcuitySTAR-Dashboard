#ifndef SUMMARYFILL_H
#define SUMMARYFILL_H

#include <QVector>
#include <QString>
#include "year.h"
#include "entry.h"

class Summary
{
public:
    //Summary();
    QVector<Year> summaryFill(QString, int, int);
};

#endif // SUMMARYFILL_H
