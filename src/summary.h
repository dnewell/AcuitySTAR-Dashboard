#ifndef SUMMARYFILL_H
#define SUMMARYFILL_H

#include <QVector>
#include <QString>
//#include <QCoreApplication>
#include <QtSql/QtSql>
#include <QDebug>
#include <iostream>
#include "QDebug"

class Summary
{
public:
    //Summary();
    QVector<QString> getFaculty(QString, QString, int, int, QString);
    QVector<double> getTier3(QString, QString, QString, int, int, QString);
    QVector<double> getTier2(QString, QString, int, int, QString);
    QVector<double> getTier1(QString, int, int, QString);
    QVector<double> getTier1Filter(QString, QString, int, int, QString);
};

#endif // SUMMARYFILL_H
