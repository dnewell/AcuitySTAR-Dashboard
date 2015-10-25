#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QtSql/QtSql>
#include <iostream>
#include "C:\Qt\5.4\msvc2012_opengl\include\QtSql\5.4.2\QtSql\private\qsql_sqlite2_p.h"
using namespace std;

class Entry{
public:
    string faculty;
    int hours;
    int students;
};

class Year{
public:
    QVector<Entry> list;
    int date;
    int tothours;
    int totstudents;
};

QVector<Year> summaryFill(QString program, int start, int end){
    QSqlQuery qry;
    QVector<Year> years;
    QString qstr;
    QSqlRecord rec;
    for(int yearcount=start; yearcount<=end; yearcount++){
        Year curyear;
        curyear.date=yearcount;
        curyear.tothours=0;
        curyear.totstudents=0;
        qstr=QString::number(yearcount);

        if(program.compare("Other")!=0){
            qry.prepare("SELECT FACULTY, HOURSPERTEACHINGSESSIONORWEEKS, NUMBEROFTRAINEES FROM TEACHING WHERE STARTDATE = "+qstr+" AND PROGRAM = "+program+"");
            qry.exec();
        }
        else{
            qry.prepare("SELECT FACULTY, HOURSPERTEACHINGSESSIONORWEEKS, NUMBEROFTRAINEES FROM TEACHING WHERE STARTDATE = "+qstr+" AND PROGRAM NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')");
            qry.exec();
        }
        qry.next();

        curyear.list.append(new Entry(qry.value(0).toString(), qry.value(1).toInt(), qry.value(2).toInt()));
        for(int n=0; qry.next(); n++){
            int exist=0;
            int index;
            for(int i=0; i<curyear.list.size(); i++){
                if(curyear.list[i].faculty.compare(qry.value(0).toString())==0){
                    exist=1;
                    index=i;
                }
            }

            if(exist==1){
                curyear.list[index].hours+=qry.value(1).toInt();
                curyear.list[index].students+=qry.value(2).toInt();
            }
            else{
                curyear.list.append(new Entry(qry.value(0).toString(), qry.value(1).toInt(), qry.value(2).toInt()));
            }
            curyear.tothours+=qry.value(1).toInt();
            curyear.totstudents+=qry.value(2).toInt();
        }
        years.append(curyear);
    }
}

int main(){
    QSqlQuery qry;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(".\testdata");
    db.open();

    qry.prepare("CREATE TABLE data(program varchar(20), faculty varchar(20), year integer, hours integer, students integer)");
    qry.exec();

    qry.prepare("INSERT INTO data(program, faculty, year, hours, students) VALUES ('PME', 'place1', 2012, 10, 100)");
    qry.exec();

    db.close();
}
