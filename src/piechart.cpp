#include "piechart.h"
#include "ui_piechart.h"
#include "nightcharts.h"
#include <QWidget>
#include <QPainter>

PieChart::PieChart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
}

PieChart::~PieChart()
{
    delete ui;
}

void PieChart::paintEvent(QPaintEvent *e)
{



    QWidget::paintEvent(e);
    QPainter painter;
    QFont font;
    painter.begin(this);
    Nightcharts PieChart;
    PieChart.setType(Nightcharts::Pie);
    PieChart.setLegendType(Nightcharts::Round);
    PieChart.setCords(100,100,this->width()/1.5,this->height()/1.5);
    PieChart.addPiece("Item1",Qt::red,34);
    PieChart.addPiece("Item2",Qt::green,27);
    PieChart.addPiece("Item3",Qt::cyan,14);
    PieChart.addPiece("Item4",Qt::yellow,7);
    PieChart.addPiece("Item5",Qt::blue,4);
    PieChart.addPiece("Item5",Qt::blue,4);
    PieChart.addPiece("Item5",Qt::blue,4);
    PieChart.draw(&painter);
    PieChart.drawLegend(&painter);
}
