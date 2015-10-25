#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QVector>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

struct entry{
    string faculty;
    int hours;
    int students;
    entry(string f, int h, int s){
        faculty=f;
        hours=h;
        students=s;
    }

    entry(){}
};

struct year{
    int date;
    int totHours;
    int totStudents;
    QVector <entry> list;
    year (int year, int totalHours, int totalStudents)
    {
        date = year;
        totHours = totalHours;
        totStudents = totalStudents;
    }

    year(){}

};



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

        //testVector
        QVector <year> testVector;

            testVector.append(year(2012,666,555));
            testVector[0].list.append(entry("John",333,777));
            testVector[0].list.append(entry("Matt", 4322,2332));

            testVector.append(year(2015,123,432));
            testVector[1].list.append(entry("SDFA",243,247));
            testVector[1].list.append(entry("asdfasd", 523,645));

    ui->setupUi(this);
    //Set tree widget table headers
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->headerItem()->setText(0,"");
    ui->treeWidget->headerItem()->setText(1,"Academic Year");
    ui->treeWidget->headerItem()->setText(2,"Hour");
    ui->treeWidget->headerItem()->setText(3,"Students");
    //ui->comboBox
//make PME,UME,CME,Other
    //fix this
    QString temphours = "0";
   QString tempStudents = "0";

//loop for  hours/students total

//
 QTreeWidgetItem *pme = root("PME", temphours, tempStudents);
 QTreeWidgetItem *ume = root("UME", temphours, tempStudents);
 QTreeWidgetItem *cme = root("CME", temphours, tempStudents);
 QTreeWidgetItem *other = root("Other", temphours, tempStudents);
 //loop to build rest of tree
 for(int i=0; i < (int)testVector.size(); i++) {
QTreeWidgetItem *year1 = yearChild(pme, QString::number(testVector[i].date),QString::number(testVector[i].totHours),QString::number(testVector[i].totStudents));
for(int j = 0; j < (int)testVector[i].list.size(); j++){
facultyChild(year1, QString::fromStdString(testVector[i].list[j].faculty),QString::number(testVector[i].list[j].hours),QString::number(testVector[i].list[j].students));
}
}
}

//creates headings
QTreeWidgetItem* MainWindow::root(QString title, QString totalHours, QString totalStudents)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);
    item->setText(2,totalHours);
    item->setText(3,totalStudents);
    ui->treeWidget->addTopLevelItem(item);
    return item;
}

//values inside the headings
QTreeWidgetItem* MainWindow::yearChild(QTreeWidgetItem *parent, QString yearRange, QString totalHours, QString totalStudents)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    //QString s = QString::number(yearRange);
    item->setText(1,yearRange);
    item->setText(2,totalHours);
    item->setText(3,totalStudents);
    parent->addChild(item);
    return item;
}

//values inside the headings
void MainWindow::facultyChild(QTreeWidgetItem *parent, QString faculty, QString totalHours, QString totalStudents)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,faculty);
    item->setText(2,totalHours);
    item->setText(3,totalStudents);
    parent->addChild(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialog = new Dialog(this);
    dialog->show();
}
