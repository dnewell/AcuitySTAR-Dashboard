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
    double portion;
    QWidget::paintEvent(e);
        QPainter painter;
        painter.begin(this);
        Nightcharts PieChart;
        PieChart.setType(Nightcharts::Pie);
        PieChart.setLegendType(Nightcharts::Round);
        PieChart.setCords(200,200,this->width()/1.5,this->height()/1.5);


        double sum =0;
        for(int i =0; i<valsLength;i++){
            sum = sum + *vals;
            vals++;
        }

        vals-=valsLength;

        for(int i =0; i<valsLength;i++){
            QColor color;
            if(i==0){
             color = QColor("Green");

            }else if(i==1){
                 color = QColor("Blue");

            }else if(i==2){
             color = QColor("Orange");

            }else if(i==3){
             color = QColor("Red");

            } else if(i==4){
             color = QColor("Purple");

            }else{
                color = QColor("Green");
            }


            portion = *vals / sum;
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
