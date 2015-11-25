#include "piechart.h"
#include "ui_piechart.h"
#include "nightcharts.h"
#include <QWidget>
#include <QPainter>
#include "QPaintEvent"
#include "QColor"

PieChart::PieChart(QString labels[], double values[], int valLength, int labLength, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
    vals = values;
    labs = labels;
    valsLength = valLength;
    labsLength = labLength;
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
        PieChart.setCords(200,200,this->width()/1.5,this->height()/1.5);
        int color4 = 50;
        int color2 = 0;
        int color3 = 0;

        double sum =0;
        for(int i =0; i<valsLength;i++){
            sum = sum + *vals;
            vals++;
        }

        vals-=valsLength;

        for(int i =0; i<valsLength;i++){
            QColor color = QColor(color3, color4, color2);


            color4+=5;
            color2+=5;
            color3+=5;


            double portion = *vals / sum;
            portion *= 100;
            PieChart.addPiece(*labs,color,portion);
            vals++;
            labs++;
        }

        vals-=valsLength;
        labs-=valsLength;

        PieChart.draw(&painter);
        PieChart.drawLegend(&painter);
}
