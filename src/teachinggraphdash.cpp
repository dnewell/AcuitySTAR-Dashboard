#include "teachinggraphdash.h"
#include "ui_teachinggraphdash.h"
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

using namespace std;

//This code actually generates the graph, look at this
//qcustomplot.cpp is supplied by qcustomplot, do not touch that
TeachingGraphDash::TeachingGraphDash(QWidget *parent):
    QDialog(parent),
    ui(new Ui::TeachingGraphDash)
{
    ui->setupUi(this);
    ui->searchIn->setPlaceholderText("Last Name, First Name");
//    Dialog::make_graph1(2009,2015);
//     //Dialog::make_graph2(ui->fromCB->currentText().toInt(),ui->toCB->currentText().toInt());
//     this->setWindowTitle("Pretty Graph");

    //Fill the items of the ComboBox
    ui->fromCB->clear();
    ui->toCB->clear();
     for(int i = 1975; i <= 2015; i++)
     {
         QString year = QString::number(i);
         ui->fromCB->addItem(year);
         ui->toCB->addItem(year);
     }


    QStringList *list = new QStringList();

    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);

    qry.prepare("SELECT DISTINCT MemberName FROM Teaching");
    qry.exec();

    while(qry.next()){
    QString name = QString(qry.record().value(0).toString());
    *list  << name;
    }

    QCompleter* completer = new QCompleter(*list);
    ui->searchIn->setCompleter(completer);

}

TeachingGraphDash::~TeachingGraphDash()
{
    delete ui;
}

void TeachingGraphDash::on_graphBtn_clicked()
{
    ui->bar_graph->clearPlottables();
    TeachingGraphDash::make_graph1(ui->fromCB->currentText().toInt(),ui->toCB->currentText().toInt());
    // Dialog::make_graph2(ui->fromCB->currentText().toInt(),ui->toCB->currentText().toInt());
     ui->bar_graph->replot();
     this->setWindowTitle("Pretty Graph");

}

//draws bar graph
void TeachingGraphDash::make_graph1(int startDate,int endDate)
{

    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);

    QString professor =ui->searchIn->text();
    QString progLevel = ui->progLevel->currentText();
    QString strtDate=QString::number(ui->fromCB->currentText().toInt());
    QString edDate=QString::number(ui->toCB->currentText().toInt());


    /*Populate UME Totals and Labels for HoursperTeachingSessionorWeek*/

    qry.prepare("SELECT SUM(HoursperTeachingSessionorWeek) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[0] = qry.record().value(0).toInt();
    labels[0] = "Hours Per Teaching Session Or Weeks";


    /*Populate UME Totals and Labels for NumberofTeachingSessionsorWeeks*/

    qry.prepare("SELECT SUM(NumberofTeachingSessionsorWeeks) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[1] = qry.record().value(0).toInt();
    labels[1] = "Number Of Teaching Sessions Or Weeks";


    /*Populate UME Totals and Labels for NumberOfTrainees*/

    qry.prepare("SELECT SUM(NumberOfTrainees) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[2] = qry.record().value(0).toInt();
    labels[2] = "Number Of Trainees";


    /*Populate UME Totals and Labels for TotalHours*/

    qry.prepare("SELECT SUM(TotalHours) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[3] = qry.record().value(0).toInt();
    labels[3] = "Total Hours";


    /*GET MAX TOTAL FOR Y AXIS*/

    int max=0;
    for(int i=0;i<4; i++){
        if(totals[i] > max){

            max = totals[i];
        }

    }

     /*Clear Plots*/
    ui->bar_graph->clearPlottables();

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
    QVector<QString> label;
    ticks << 1 << 2 << 3 << 4;
    label << labels[0] << labels[1] << labels[2] << labels[3] ;
    ui->bar_graph->xAxis->setAutoTicks(false);
    ui->bar_graph->xAxis->setAutoTickLabels(false);
    ui->bar_graph->xAxis->setTickVector(ticks);
    ui->bar_graph->xAxis->setTickVectorLabels(label);
    ui->bar_graph->xAxis->grid()->setVisible(true);


    // prepare y axis:
    ui->bar_graph->yAxis->setAutoTicks(true);
    ui->bar_graph->yAxis->setAutoTickLabels(true);
    ui->bar_graph->yAxis->setRange(0, max);
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

   graphData << totals[0] << totals[1] << totals[2] << totals[3];
   postBar->setData(ticks, graphData);

}

void TeachingGraphDash::make_graph2(int startDate,int endDate)
{
    //get data for graph
    Summary* grabber = new Summary();


    int totHoursP = 0;
    int totStudentsP = 0;
    int totHoursU = 0;
    int totStudentsU = 0;
    int totHoursC = 0;
    int totStudentsC = 0;
    int totHoursO = 0;
    int totStudentsO = 0;






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

   graphData << totHoursP << totHoursU << totHoursC << totHoursO;
   postBar->setData(ticks, graphData);
}

void TeachingGraphDash::on_pieChart_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);
    QString professor =ui->searchIn->text();
    QString progLevel = ui->progLevel->currentText();
    QString strtDate=QString::number(ui->fromCB->currentText().toInt());
    QString edDate=QString::number(ui->toCB->currentText().toInt());


    /*Populate UME Totals and Labels for HoursperTeachingSessionorWeek*/

    qry.prepare("SELECT SUM(HoursperTeachingSessionorWeek) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[0] = qry.record().value(0).toInt();
    labels[0] = "Hours Per Teaching Session Or Weeks";


    /*Populate UME Totals and Labels for NumberofTeachingSessionsorWeeks*/

    qry.prepare("SELECT SUM(NumberofTeachingSessionsorWeeks) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[1] = qry.record().value(0).toInt();
    labels[1] = "Number Of Teaching Sessions Or Weeks";


    /*Populate UME Totals and Labels for NumberOfTrainees*/

    qry.prepare("SELECT SUM(NumberOfTrainees) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[2] = qry.record().value(0).toInt();
    labels[2] = "Number Of Trainees";


    /*Populate UME Totals and Labels for TotalHours*/

    qry.prepare("SELECT SUM(TotalHours) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[3] = qry.record().value(0).toInt();
    labels[3] = "Total Hours";


    QDialog *pieWindow = new PieChart(labels, totals, 4, 4, this);
    pieWindow->showMaximized();

}

void TeachingGraphDash::printPieButton(){
    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);
    QString professor =ui->searchIn->text();
    QString progLevel = ui->progLevel->currentText();
    QString strtDate=QString::number(ui->fromCB->currentText().toInt());
    QString edDate=QString::number(ui->toCB->currentText().toInt());


    /*Populate UME Totals and Labels for HoursperTeachingSessionorWeek*/

    qry.prepare("SELECT SUM(HoursperTeachingSessionorWeek) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[0] = qry.record().value(0).toInt();
    labels[0] = "Hours Per Teaching Session Or Weeks";


    /*Populate UME Totals and Labels for NumberofTeachingSessionsorWeeks*/

    qry.prepare("SELECT SUM(NumberofTeachingSessionsorWeeks) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[1] = qry.record().value(0).toInt();
    labels[1] = "Number Of Teaching Sessions Or Weeks";


    /*Populate UME Totals and Labels for NumberOfTrainees*/

    qry.prepare("SELECT SUM(NumberOfTrainees) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[2] = qry.record().value(0).toInt();
    labels[2] = "Number Of Trainees";


    /*Populate UME Totals and Labels for TotalHours*/

    qry.prepare("SELECT SUM(TotalHours) FROM Teaching WHERE MemberName LIKE '"+professor+"%' AND Program LIKE '"+progLevel+"%' AND StartDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' AND EndDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    //qDebug()<< qry.lastQuery();
    totals[3] = qry.record().value(0).toInt();
    labels[3] = "Total Hours";


    QDialog *pieWindow = new PieChart(labels, totals, 4, 4, this);

    QPrinter printer;
    QPainter painter;
    //printer.setOutputFileName("/Users/Anoop/Filenamecena");
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Pie Chart");
    if (dialog->exec() != QDialog::Accepted)
        return;
    painter.begin(&printer);
    painter.scale(0.5,0.5);
    pieWindow->render(&painter);
    painter.end();




}
void TeachingGraphDash::printBarButton(){
    QPrinter printer;
    QPainter painter;
    //printer.setOutputFileName("/Users/Anoop/Filenamecena");
    QPrintDialog *dialog = new QPrintDialog(&printer);

    dialog->setWindowTitle("Print Bar Chart");
    if (dialog->exec() != QDialog::Accepted)
        return;
    painter.begin(&printer);
    painter.scale(0.5,0.5);
    ui->bar_graph->render(&painter);
    painter.end();
}





void TeachingGraphDash::on_print_pie_Button_clicked()
{
    printPieButton();
}

void TeachingGraphDash::on_print_bar_Button_clicked()
{
   printBarButton();
}
