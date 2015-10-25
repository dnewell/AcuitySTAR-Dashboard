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



// Test using summary.cpp and entry / year classes
void testSummaryClass(){
    Summary* sum = new Summary();
    QVector<Year> vector;
    vector.append(sum->summaryFill("Postgraduate Medical Education", 2012, 2015));
    for(int n=0; n<vector.size(); n++){
    cout<< "A" <<vector[n].date<<endl;
    cout<< "B" <<vector[n].tothours<<endl;
    cout<< "C" <<vector[n].totstudents<<endl;
    for(int i=0; i<vector[n].list.size(); i++){
        cout<< "d" <<vector[n].list[i].faculty.toStdString()<<endl;
        cout<< "e" <<vector[n].list[i].hours<<endl;
        cout<< "f" <<vector[n].list[i].students<<endl;
    }
    }
}

int main()
{
    DB* db = new DB();
    db->createDatabase();
    db->teachingCsvIntoDb("C:/Users/David/OneDrive/Documents/3307_git/Backend Code/Teaching_sample.csv");
//    dbTest();
    testSummaryClass();
}
