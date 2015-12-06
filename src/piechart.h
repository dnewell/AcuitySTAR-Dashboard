#ifndef PIECHART_H
#define PIECHART_H

#include <QDialog>
#include "ui_piechart.h"
#include "nightcharts.h"
#include <QWidget>
#include <QPainter>
#include "QPaintEvent"
#include "QColor"

namespace Ui {
class PieChart;
}

class PieChart : public QDialog
{
    Q_OBJECT

public:
    explicit PieChart(QString labels[], double values[], int valLength, int labLength, QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);

    ~PieChart();

private:
    Ui::PieChart *ui;
    double *vals;
    QString *labs;
    int valsLength;
    int labsLength;

};

#endif // PIECHART_H
