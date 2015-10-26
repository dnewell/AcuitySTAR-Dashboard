#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>
#include <QVector>
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <summary.h>

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


    ui->setupUi(this);
    //Set tree widget table headers
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->headerItem()->setText(0,"");
    ui->treeWidget->headerItem()->setText(1,"Postgraduate Education");
    ui->treeWidget->headerItem()->setText(2,"Undergraduate Education");
    ui->treeWidget->headerItem()->setText(3,"Continuing Education");
    ui->treeWidget->headerItem()->setText(4,"Other");

    Summary* grabber = new Summary();

    QVector<Year> underVec= grabber->summaryFill("Undergraduate Medical Education",2010,2015);
    QVector<Year> continuingVec= grabber->summaryFill("Continuing Medical Education",2010,2015);
    QVector<Year> postVec= grabber->summaryFill("Postgraduate Medical Education",2010,2015);
    QVector<Year> otherVec= grabber->summaryFill("Other",2010,2015);

    int postHourTot = 0;
    int underHourTot = 0;
    int continHourTot = 0;
    int otherHourTot = 0;

    for (int curYear = 0; curYear < 4; curYear++){

        postHourTot+= postVec[curYear].tothours;
        underHourTot+= underVec[curYear].tothours;
        continHourTot+= continuingVec[curYear].tothours;
        otherHourTot+= otherVec[curYear].tothours;

    }

    int postStudTot = 0;
    int underStudTot = 0;
    int continStudTot = 0;
    int otherStudTot = 0;

    for (int curYear = 0; curYear < 4; curYear++){

        postStudTot+= postVec[curYear].totstudents;
        underStudTot+= underVec[curYear].totstudents;
        continStudTot+= continuingVec[curYear].totstudents;
        otherStudTot+= otherVec[curYear].totstudents;

    }
    QString qRoot = QString::number(postHourTot);
    QString qPost = QString::number(postStudTot);

    QTreeWidgetItem *pme = root("Postgraduate Education", qRoot, qPost);

    for(int i=0; i < (int)postVec.size(); i++) {

        QTreeWidgetItem *postWidget = yearChild(pme, QString::number(postVec[i].date),QString::number(postVec[i].tothours),QString::number(postVec[i].totstudents));

        for(int j = 0; j < (int)postVec[i].list.size(); j++){

            facultyChild(postWidget, postVec[i].list[j].faculty,QString::number(postVec[i].list[j].hours),QString::number(postVec[i].list[j].students));

        }

    }

    qRoot = QString::number(underHourTot);
    qPost = QString::number(underStudTot);

    QTreeWidgetItem *ume = root("Undergraduate Education", qRoot, qPost);

    for(int i=0; i < (int)underVec.size(); i++) {

           QTreeWidgetItem *postWidget = yearChild(ume, QString::number(postVec[i].date),QString::number(postVec[i].tothours),QString::number(postVec[i].totstudents));

        for(int j = 0; j < (int)underVec[i].list.size(); j++){

            facultyChild(postWidget, underVec[i].list[j].faculty,QString::number(underVec[i].list[j].hours),QString::number(underVec[i].list[j].students));

        }

    }
    qRoot = QString::number(continHourTot);
    qPost = QString::number(continStudTot);
    QTreeWidgetItem *cme = root("Continuing Education", qRoot, qPost);

    for(int i=0; i < (int)continuingVec.size(); i++) {

        QTreeWidgetItem *continWidget = yearChild(cme, QString::number(continuingVec[i].date),QString::number(continuingVec[i].tothours),QString::number(continuingVec[i].totstudents));

        for(int j = 0; j < (int)continuingVec[i].list.size(); j++){

            facultyChild(continWidget, continuingVec[i].list[j].faculty,QString::number(continuingVec[i].list[j].hours),QString::number(continuingVec[i].list[j].students));

        }

    }
    qRoot = QString::number(otherHourTot);
    qPost = QString::number(otherStudTot);
    QTreeWidgetItem *other = root("Other", qRoot, qPost);

    for(int i=0; i < (int)otherVec.size(); i++) {

        QTreeWidgetItem *otherWidget = yearChild(other, QString::number(otherVec[i].date),QString::number(otherVec[i].tothours),QString::number(otherVec[i].totstudents));

        for(int j = 0; j < (int)otherVec[i].list.size(); j++){

            facultyChild(otherWidget, otherVec[i].list[j].faculty,QString::number(otherVec[i].list[j].hours),QString::number(otherVec[i].list[j].students));

        }

    }

}
//creates headings
QTreeWidgetItem* MainWindow::root(QString title, QString totalHours, QString totalStudents){
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);
    item->setText(2,totalHours);
    item->setText(3,totalStudents);
    ui->treeWidget->addTopLevelItem(item);
    return item;
}

//values inside the headings
QTreeWidgetItem* MainWindow::yearChild(QTreeWidgetItem *parent, QString yearRange, QString totalHours, QString totalStudents){
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
