#include "publicationgraphdash.h"
#include "ui_publicationgraphdash.h"
#include <year.h>
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

publicationGraphDash::publicationGraphDash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::publicationGraphDash)
{


    ui->setupUi(this);

//    ui->fromCBPub->clear();
//    ui->toCBPub->clear();
     //Fill the items of the ComboBox
      for(int i = 1975; i <= 2015; i++)
      {
          QString year = QString::number(i);
          ui->fromCBPub->addItem(year);
          ui->toCBPub->addItem(year);
      }




}

publicationGraphDash::~publicationGraphDash()
{
    delete ui;
}

void publicationGraphDash::on_barBtn_clicked()
{
    ui->bar_graphPub->clearPlottables();
    make_graph1(ui->fromCBPub->currentText().toInt(),ui->toCBPub->currentText().toInt());
    // Dialog::make_graph2(ui->fromCBPub->currentText().toInt(),ui->toCBPub->currentText().toInt());
    ui->bar_graphPub->replot();
    this->setWindowTitle("Pretty Graph");

}

//draws graph 1
void publicationGraphDash::make_graph1(int startDate,int endDate)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");
    db.open();
    QSqlQuery qry(db);

    QString professor =ui->searchInPub->text();
    QString pubType = ui->pubType->currentText();
    QString strtDate=QString::number(startDate);
    QString edDate=QString::number(endDate);


    /*Populate totals for Number of Contributors*/

    qry.prepare("SELECT SUM(NumberOfContributors) FROM Publications WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+pubType+"%' AND StatusDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' ");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();

    int result;

    qry.next();
    result = qry.record().value(0).toInt();

    totalsPub[0] = result;
    labelsPub[0] = "NumberOfContributors";

    qry.prepare("SELECT SUM(NumberofCitations) FROM Publications WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+pubType+"%' AND StatusDate BETWEEN '"+strtDate+"%' AND '"+edDate+"%' ");
    //qry.prepare("SELECT * FROM Teaching");
    qry.exec();
    qry.next();
    result = qry.record().value(0).toInt();
    totalsPub[1] = qry.record().value(0).toInt();
    labelsPub[1] = "NumberofCitations";

    /*GET MAX TOTAL FOR Y AXIS*/

    double max=0;
    for(int i=0;i<2; i++){
        if(totalsPub[i] > max){

            max = totalsPub[i];
        }

    }

     /*Clear Plots*/
    ui->bar_graphPub->clearPlottables();

    // create empty bar chart objects:
    QCPBars *postBar = new QCPBars(ui->bar_graphPub->xAxis, ui->bar_graphPub->yAxis);

    ui->bar_graphPub->addPlottable(postBar);

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
    ticks << 1 << 2;
    label << labelsPub[0] << labelsPub[1];
    ui->bar_graphPub->xAxis->setAutoTicks(false);
    ui->bar_graphPub->xAxis->setAutoTickLabels(false);
    ui->bar_graphPub->xAxis->setTickVector(ticks);
    ui->bar_graphPub->xAxis->setTickVectorLabels(label);
    ui->bar_graphPub->xAxis->grid()->setVisible(true);


    // prepare y axis:
    ui->bar_graphPub->yAxis->setAutoTicks(true);
    ui->bar_graphPub->yAxis->setAutoTickLabels(true);
    ui->bar_graphPub->yAxis->setRange(0, max);
    ui->bar_graphPub->yAxis->setPadding(5); // a bit more space to the left border
    ui->bar_graphPub->yAxis->setLabel("Total Hours/Students");
    ui->bar_graphPub->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 50, 25));
    ui->bar_graphPub->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->bar_graphPub->yAxis->grid()->setSubGridPen(gridPen);

   QVector<double> graphData;


   graphData << totalsPub[0] << totalsPub[1];
   postBar->setData(ticks, graphData);

}

void publicationGraphDash::on_pieBtn_clicked()
{
    pieWindow = new PieChart(labelsPub, totalsPub, 2, 2, this);
    pieWindow->show();
}