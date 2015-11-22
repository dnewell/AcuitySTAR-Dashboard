#include "dialog.h"
#include "ui_dialog.h"
#include <year.h>
#include <summary.h>
#include <qcustomplot.h>
#include <db.h>

//This code actually generates the graph, look at this
//qcustomplot.cpp is supplied by qcustomplot, do not touch that
Dialog::Dialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//    Dialog::make_graph1(2009,2015);
//     //Dialog::make_graph2(ui->fromCB->currentText().toInt(),ui->toCB->currentText().toInt());
//     this->setWindowTitle("Pretty Graph");

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_graphBtn_clicked()
{
    ui->bar_graph->clearPlottables();
    Dialog::make_graph1(ui->fromCB->currentText().toInt(),ui->toCB->currentText().toInt());
     Dialog::make_graph2(ui->fromCB->currentText().toInt(),ui->toCB->currentText().toInt());
     ui->bar_graph->replot();
     this->setWindowTitle("Pretty Graph");
}

//draws graph 1
void Dialog::make_graph1(int startDate,int endDate)
{

    //get data for graph
    Summary* grabber = new Summary();

    QVector<Year> underVec= grabber->summaryFill("Undergraduate Medical Education",startDate,endDate);
    QVector<Year> continuingVec= grabber->summaryFill("Continuing Medical Education",startDate,endDate);
    QVector<Year> postVec = grabber->summaryFill("Postgraduate Medical Education",startDate,endDate);
    QVector<Year> otherVec= grabber->summaryFill("Other",startDate,endDate);

    int totHoursP = 0;
    int totStudentsP = 0;
    int totHoursU = 0;
    int totStudentsU = 0;
    int totHoursC = 0;
    int totStudentsC = 0;
    int totHoursO = 0;
    int totStudentsO = 0;

    //calculate Header Totals
    for(int m=0; m < (int)postVec.size(); m++) {
        totHoursP = totHoursP + postVec[m].tothours;
        totStudentsP = totStudentsP + postVec[m].totstudents;
        totHoursU = totHoursU + underVec[m].tothours;
        totStudentsU = totStudentsU + underVec[m].totstudents;
        totHoursC = totHoursC + continuingVec[m].tothours;
        totStudentsC = totStudentsC + continuingVec[m].totstudents;
        totHoursO = totHoursO + otherVec[m].tothours;
        totStudentsO = totStudentsO + otherVec[m].totstudents;
    }





    // create empty bar chart objects:
    QCPBars *postBar = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);

    ui->bar_graph->addPlottable(postBar);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    postBar->setName("Postgraduate Medical Education");
    pen.setColor(QColor(255, 131, 0));
    postBar->setPen(pen);
    postBar->setBrush(QColor(255, 131, 0, 50));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;
    labels << "PME" << "UME" << "CME" << "Other" ;
    ui->bar_graph->xAxis->setAutoTicks(false);
    ui->bar_graph->xAxis->setAutoTickLabels(false);
    ui->bar_graph->xAxis->setTickVector(ticks);
    ui->bar_graph->xAxis->setTickVectorLabels(labels);
    ui->bar_graph->xAxis->grid()->setVisible(true);


    // prepare y axis:
    ui->bar_graph->yAxis->setAutoTicks(true);
    ui->bar_graph->yAxis->setAutoTickLabels(true);

    // Compares totals to determine max range

    int tempTotHours = 0;


        if(totStudentsP > tempTotHours)
            tempTotHours = totHoursP;
        if(totStudentsU > tempTotHours)
            tempTotHours = totHoursU;
        if(totStudentsC > tempTotHours)
            tempTotHours = totHoursC;
        if(totStudentsO > tempTotHours)
            tempTotHours = totHoursO;


    ui->bar_graph->yAxis->setRange(0, tempTotHours);
    ui->bar_graph->yAxis->setPadding(5); // a bit more space to the left border
    ui->bar_graph->yAxis->setLabel("Total Hours/Students");
    ui->bar_graph->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 50, 25));
    ui->bar_graph->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->bar_graph->yAxis->grid()->setSubGridPen(gridPen);

   QVector<double> graphData;

   //Right here we loop through our array of selected items and append to graphdate before displaying it.
//   QModelIndex index;

//   foreach(index, selectedItems) {

//          if(index.row() == 2){
//
//          }

//    }

   qDebug()<< totStudentsP << totStudentsU << totStudentsC << totStudentsO;
   graphData << totStudentsP << totStudentsU << totStudentsC << totStudentsO;
   postBar->setData(ticks, graphData);

}

void Dialog::make_graph2(int startDate,int endDate)
{
    //get data for graph
    Summary* grabber = new Summary();

    QVector<Year> underVec= grabber->summaryFill("Undergraduate Medical Education",startDate,endDate);
    QVector<Year> continuingVec= grabber->summaryFill("Continuing Medical Education",startDate,endDate);
    QVector<Year> postVec = grabber->summaryFill("Postgraduate Medical Education",startDate,endDate);
    QVector<Year> otherVec= grabber->summaryFill("Other",startDate,endDate);

    int totHoursP = 0;
    int totStudentsP = 0;
    int totHoursU = 0;
    int totStudentsU = 0;
    int totHoursC = 0;
    int totStudentsC = 0;
    int totHoursO = 0;
    int totStudentsO = 0;

    //calculate Header Totals
    for(int m=0; m < (int)postVec.size(); m++) {
        totHoursP = totHoursP + postVec[m].tothours;
        totStudentsP = totStudentsP + postVec[m].totstudents;
        totHoursU = totHoursU + underVec[m].tothours;
        totStudentsU = totStudentsU + underVec[m].totstudents;
        totHoursC = totHoursC + continuingVec[m].tothours;
        totStudentsC = totStudentsC + continuingVec[m].totstudents;
        totHoursO = totHoursO + otherVec[m].tothours;
        totStudentsO = totStudentsO + otherVec[m].totstudents;
    }





    // create empty bar chart objects:
    QCPBars *postBar = new QCPBars(ui->bar_graph->xAxis, ui->bar_graph->yAxis);

    ui->bar_graph->addPlottable(postBar);

    // set names and colors:
    QPen pen;
    pen.setWidthF(1.2);
    postBar->setName("Postgraduate Medical Education");
    pen.setColor(QColor(255, 131, 0));
    postBar->setPen(pen);
    postBar->setBrush(QColor(255, 131, 0, 50));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4;
    labels << "PME" << "UME" << "CME" << "Other" ;
    ui->bar_graph->xAxis->setAutoTicks(false);
    ui->bar_graph->xAxis->setAutoTickLabels(false);
    ui->bar_graph->xAxis->setTickVector(ticks);
    ui->bar_graph->xAxis->setTickVectorLabels(labels);
    ui->bar_graph->xAxis->grid()->setVisible(true);


    // prepare y axis:
    ui->bar_graph->yAxis->setAutoTicks(true);
    ui->bar_graph->yAxis->setAutoTickLabels(true);

    // Compares totals to determine max range

    int tempTotHours = 0;


        if(totHoursP > tempTotHours)
            tempTotHours = totHoursP;
        if(totHoursU > tempTotHours)
            tempTotHours = totHoursU;
        if(totHoursC > tempTotHours)
            tempTotHours = totHoursC;
        if(totHoursO > tempTotHours)
            tempTotHours = totHoursO;


    ui->bar_graph->yAxis->setRange(0, tempTotHours);
    ui->bar_graph->yAxis->setPadding(5); // a bit more space to the left border
    ui->bar_graph->yAxis->setLabel("Total Hours/Students");
    ui->bar_graph->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->bar_graph->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->bar_graph->yAxis->grid()->setSubGridPen(gridPen);

   QVector<double> graphData;
//   QModelIndex index;

//   foreach(index, selectedItems) {

//          if(index.row() == 3){
//              qDebug()<<("here");
//              graphData << totHoursP << totHoursU << totHoursC << totHoursO;
//              postBar->setData(ticks, graphData);
//          }

//        }
   graphData << totHoursP << totHoursU << totHoursC << totHoursO;
   postBar->setData(ticks, graphData);
}


