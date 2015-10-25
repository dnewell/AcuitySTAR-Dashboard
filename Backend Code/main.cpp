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
    vector.append(sum->summaryFill("Postgraduate Medical Education", 1999, 1999));
    cout<< "A" <<vector[0].date<<endl;
    cout<< "B" <<vector[0].tothours<<endl;
    cout<< "C" <<vector[0].totstudents<<endl;
    for(int i=0; i<vector[0].list.size(); i++){
        cout<< "d" <<vector[0].list[i].faculty.toStdString()<<endl;
        cout<< "e" <<vector[0].list[i].hours<<endl;
        cout<< "f" <<vector[0].list[i].students<<endl;
    }
}

int main()
{
    DB* db = new DB();
    db->createDatabase();
    db->teachingCsvIntoDb("C:/Users/David/Documents/DatabaseCore/Teaching_sample.csv");
    dbTest();

}
