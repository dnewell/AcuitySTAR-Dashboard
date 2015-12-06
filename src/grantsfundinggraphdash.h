#ifndef GRANTSFUNDINGGRAPHDASH_H
#define GRANTSFUNDINGGRAPHDASH_H

#include <QDialog>
#include "ui_grantsfundinggraphdash.h"
#include <summary.h>
#include <qcustomplot.h>
#include <db.h>
#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QtSql/QtSql>
#include <QDebug>
#include <iostream>
#include <algorithm>
#include <piechart.h>

namespace Ui {
class GrantsFundingGraphDash;
}

class GrantsFundingGraphDash : public QDialog
{
    Q_OBJECT

public:
    explicit GrantsFundingGraphDash(QWidget *parent = 0);
    ~GrantsFundingGraphDash();
private slots:
    void make_graph1(int startDate,int endDate);

    void on_graphBtn_clicked();

    void on_pieBtn_clicked();
    void printPieButton();
    void printBarButton();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GrantsFundingGraphDash *ui;
    double totalsGrants[2];
    QString labelsGrants[2];
    double totalsGrantsPie[2];
    QString labelsGrantsPie[2];
};

#endif // GRANTSFUNDINGGRAPHDASH_H
