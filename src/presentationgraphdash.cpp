#include "presentationgraphdash.h"
#include "ui_presentationgraphdash.h"
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
#include <QCompleter>
#include <QStringList>

PresentationGraphDash::PresentationGraphDash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PresentationGraphDash)
{
    ui->setupUi(this);
    ui->searchInPres->setPlaceholderText("Last Name, First Name");
    //Fill the items of the ComboBox
     for(int i = 1975; i <= 2015; i++)
     {
         QString year = QString::number(i);
         ui->fromCBPres->addItem(year);
         ui->toCBPres->addItem(year);
     }

     /*Auto Complete LineEdit*/
     QStringList *list = new QStringList();

     QSqlDatabase db = QSqlDatabase::database("db_connection");
     QSqlQuery qry(db);

     qry.prepare("SELECT DISTINCT MemberName FROM Presentations");
     qry.exec();

     while(qry.next()){
     QString name = QString(qry.record().value(0).toString());
     *list  << name;
     }

     QCompleter* completer = new QCompleter(*list);
     ui->searchInPres->setCompleter(completer);

}

PresentationGraphDash::~PresentationGraphDash()
{
    delete ui;
}

//draws graph 1
void PresentationGraphDash::make_graph1(int startDate,int endDate)
{

    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);

    QString professor =ui->searchInPres->text();
    QString presType = ui->presType->currentText();
    QString strtDate=QString::number(startDate);
    QString edDate=QString::number(endDate);


    /*Populate totals for Number of Attendees*/

    qry.prepare("SELECT SUM(NumberofAttendees) FROM Presentations WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+presType+"%' AND Date BETWEEN '"+strtDate+"%' AND '"+edDate+"%' ");
    qry.exec();

    int result;

    qry.next();
    result = qry.record().value(0).toInt();

    totalsPres[0] = result;
    labelsPres[0] = "Number Of Attendees";

    qry.prepare("SELECT SUM(Hours) FROM Presentations WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+presType+"%' AND Date BETWEEN '"+strtDate+"%' AND '"+edDate+"%' ");
    qry.exec();
    qry.next();
    result = qry.record().value(0).toInt();
    totalsPres[1] = qry.record().value(0).toInt();
    labelsPres[1] = "Hours";

    /*GET MAX TOTAL FOR Y AXIS*/

    double max=0;
    for(int i=0;i<2; i++){
        if(totalsPres[i] > max){

            max = totalsPres[i];
        }

    }

     /*Clear Plots*/
    ui->bar_graphPres->clearPlottables();

    // create empty bar chart objects:
    QCPBars *postBar = new QCPBars(ui->bar_graphPres->xAxis, ui->bar_graphPres->yAxis);

    ui->bar_graphPres->addPlottable(postBar);

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
    label << labelsPres[0] << labelsPres[1];
    ui->bar_graphPres->xAxis->setAutoTicks(false);
    ui->bar_graphPres->xAxis->setAutoTickLabels(false);
    ui->bar_graphPres->xAxis->setTickVector(ticks);
    ui->bar_graphPres->xAxis->setTickVectorLabels(label);
    ui->bar_graphPres->xAxis->grid()->setVisible(true);


    // prepare y axis:
    ui->bar_graphPres->yAxis->setAutoTicks(true);
    ui->bar_graphPres->yAxis->setAutoTickLabels(true);
    ui->bar_graphPres->yAxis->setRange(0, max);
    ui->bar_graphPres->yAxis->setPadding(5); // a bit more space to the left border
    ui->bar_graphPres->yAxis->setLabel("Total Hours/Students");
    ui->bar_graphPres->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 50, 25));
    ui->bar_graphPres->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->bar_graphPres->yAxis->grid()->setSubGridPen(gridPen);

   QVector<double> graphData;


   graphData << totalsPres[0] << totalsPres[1];
   postBar->setData(ticks, graphData);

}


void PresentationGraphDash::on_barBtn_clicked()
{
    ui->bar_graphPres->clearPlottables();
    make_graph1(ui->fromCBPres->currentText().toInt(),ui->toCBPres->currentText().toInt());
    // Dialog::make_graph2(ui->fromCBPres->currentText().toInt(),ui->toCBPres->currentText().toInt());
    ui->bar_graphPres->replot();
    this->setWindowTitle("Pretty Graph");

}

void PresentationGraphDash::on_pieBtn_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);

    QString professor =ui->searchInPres->text();
    QString strtDate=QString::number(ui->fromCBPres->currentText().toInt());
    QString edDate=QString::number(ui->toCBPres->currentText().toInt());
    QString presType = ui->presType->currentText();


    /*Populate totals for Number of Attendees*/

    qry.prepare("SELECT SUM(NumberofAttendees) FROM Presentations WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+presType+"%' AND Date BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    qry.exec();

    double result;
    if(qry.next()){
    result = qry.record().value(0).toInt();
    }else{
        result = 0;
    }
    totalsPres[0] = result;
    labelsPres[0] = "Number Of Attendees";

    qry.prepare("SELECT SUM(Hours) FROM Presentations WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+presType+"%' AND Date BETWEEN '"+strtDate+"%' AND '"+edDate+"%' ");
    qry.exec();
    if(qry.next()){
    result = qry.record().value(0).toInt();
    }else{
        result = 0;
    }

    totalsPres[1] = qry.record().value(0).toDouble();
    labelsPres[1] = "Hours";

    pieWindow = new PieChart(labelsPres, totalsPres, 2, 2, this);
    pieWindow->showMaximized();




}

void PresentationGraphDash::printBarButton(){
    QPrinter printer;
    QPainter painter;
   //printer.setOutputFileName("/Users/Anoop/Filenamecena");
    QPrintDialog *dialog = new QPrintDialog(&printer);

    dialog->setWindowTitle("Print Bar Chart");
    if (dialog->exec() != QDialog::Accepted)
        return;
    painter.begin(&printer);
    painter.scale(0.5,0.5);
    ui->bar_graphPres->render(&painter);
    painter.end();


}






void PresentationGraphDash::printPieButton(){


    QSqlDatabase db = QSqlDatabase::database("db_connection");
    QSqlQuery qry(db);

    QString professor =ui->searchInPres->text();
    QString strtDate=QString::number(ui->fromCBPres->currentText().toInt());
    QString edDate=QString::number(ui->toCBPres->currentText().toInt());
    QString presType = ui->presType->currentText();


    /*Populate totals for Number of Attendees*/

    qry.prepare("SELECT SUM(NumberofAttendees) FROM Presentations WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+presType+"%' AND Date BETWEEN '"+strtDate+"%' AND '"+edDate+"%'");
    qry.exec();

    double result;
    if(qry.next()){
    result = qry.record().value(0).toInt();
    }else{
        result = 0;
    }
    totalsPres[0] = result;
    labelsPres[0] = "Number Of Attendees";

    qry.prepare("SELECT SUM(Hours) FROM Presentations WHERE MemberName LIKE '"+professor+"%' AND Type LIKE '"+presType+"%' AND Date BETWEEN '"+strtDate+"%' AND '"+edDate+"%' ");
    qry.exec();
    if(qry.next()){
    result = qry.record().value(0).toInt();
    }else{
        result = 0;
    }

    totalsPres[1] = qry.record().value(0).toDouble();
    labelsPres[1] = "Hours";

    pieWindow = new PieChart(labelsPres, totalsPres, 2, 2, this);

    QPrinter printer;
    QPainter painter;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Pie Chart");
    if (dialog->exec() != QDialog::Accepted)
        return;
    painter.begin(&printer);
    painter.scale(0.5,0.5);
    pieWindow->render(&painter);
    painter.end();




}




void PresentationGraphDash::on_pushButton_clicked()
{
    printBarButton();
}

void PresentationGraphDash::on_pushButton_2_clicked()
{
    printPieButton();
}
