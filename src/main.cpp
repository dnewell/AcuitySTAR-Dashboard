#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <QVector>
#include <QtSql/QtSql>
#include <QString>
#include "db.h"
#include "summary.h"

using namespace std;

void dbTest(){
    //open connection to database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");  //without all the QDir stuff, will only look in current working directory
    db.open();
    QSqlQuery query(db);

    //query database
    query.exec("SELECT FACULTY, HOURSPERTEACHINGSESSIONORWEEKS, NUMBEROFTRAINEES FROM TEACHING WHERE STARTDATE = '1999' AND PROGRAM = 'Postgraduate Medical Education'");
    while (query.next()) {
        QString faculty = query.value(0).toString();
        QString hours = query.value(1).toString();
        QString numTrainees = query.value(2).toString();
        qDebug() << faculty << hours << numTrainees;
        }
}


//launches main window
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DB* db = new DB();
    db->createDatabase();
    db->teachingCsvIntoDb("C:/CS3307/3307-TeamCanteloupe/Backend Code/Teaching_sample.csv");
//    dbTest();
    //testSummaryClass();

    return a.exec();
}
