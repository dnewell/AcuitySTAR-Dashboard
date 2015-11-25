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
    QVector<QString> getFaculty(QString, QString, int, int, QString);
    QVector<double> getTier3(QString, QString, QString, int, int, QString);
    QVector<double> getTier2(QString, QString, int, int, QString);
    QVector<double> getTier1(QString, int, int, QString);
    QVector<double> getTier1Filter(QString, QString, int, int, QString);
};

#endif // SUMMARYFILL_H
