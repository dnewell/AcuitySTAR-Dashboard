#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QtSql/QtSql>
#include <QDebug>
#include <iostream>
#include "summary.h"
using namespace std;




//Summary(){

//}

QVector<Year> Summary::summaryFill(QString program, int start, int end){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");  //without all the QDir stuff, will only look in current working directory
    db.open();
    QSqlQuery qry(db);


    QVector<Year> years;
    QString qstr;
    for(int yearcount=start; yearcount<=end; yearcount++){
        Year curyear (yearcount,0,0);
        qstr=QString::number(yearcount);

        if(program.compare("Other")!=0){
            qry.prepare("SELECT FACULTY, HOURSPERTEACHINGSESSIONORWEEKS, NUMBEROFTRAINEES FROM TEACHING WHERE STARTDATE = '"+qstr+"' AND PROGRAM = '"+program+"'");
            qry.exec();
        }
        else{
            qry.prepare("SELECT FACULTY, HOURSPERTEACHINGSESSIONORWEEKS, NUMBEROFTRAINEES FROM TEACHING WHERE STARTDATE = '"+qstr+"' AND PROGRAM NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')");
            qry.exec();
        }
        if(qry.next()){

            curyear.list.append(Entry(qry.value(0).toString(), qry.value(1).toDouble(), qry.value(2).toInt()));
            curyear.tothours+=qry.value(1).toDouble();
            curyear.totstudents+=qry.value(2).toInt();
            for(int n=0; qry.next(); n++){
                int exist=0;
                int index;
                for(int i=0; i<curyear.list.size(); i++){
                    if(curyear.list[i].faculty.QString::compare(qry.value(0).toString())==0){
                        exist=1;
                        index=i;
                    }
                }

                if(exist==1){
                    curyear.list[index].hours+=qry.value(1).toDouble();
                    //cout<<qry.value(1).toInt()<<endl;
                    //cout<<curyear.list[index].hours<<endl;
                    curyear.list[index].students+=qry.value(2).toInt();
                }
                else{
                    curyear.list.append(Entry(qry.value(0).toString(), qry.value(1).toDouble(), qry.value(2).toInt()));
                }
                curyear.tothours+=qry.value(1).toDouble();
                curyear.totstudents+=qry.value(2).toInt();
            }
        }
        years.append(curyear);
    }
    db.close();
    return years;
}

//int main(){
//    QSqlQuery qry;
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(".\testdata");
//    db.open();

//    qry.prepare("CREATE TABLE data(program varchar(20), faculty varchar(20), year integer, hours integer, students integer)");
//    qry.exec();

//    qry.prepare("INSERT INTO data(program, faculty, year, hours, students) VALUES ('PME', 'place1', 2012, 10, 100)");
//    qry.exec();

//    db.close();
//}
