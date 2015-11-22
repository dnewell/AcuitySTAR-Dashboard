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
#include <db.h>
#include <filter.h>
#include "about_canteloupe.h"
#include <dialog.h>

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makeTree(0,0);
}

void MainWindow::makeTree(int startDate, int endDate){
    ui->treeWidget->clear();
    //get data for vectors
    Summary* grabber = new Summary();

    QVector<Year> underVec= grabber->summaryFill("Undergraduate Medical Education",startDate,endDate);
    QVector<Year> continuingVec= grabber->summaryFill("Continuing Medical Education",startDate,endDate);
    QVector<Year> postVec = grabber->summaryFill("Postgraduate Medical Education",startDate,endDate);
    QVector<Year> otherVec= grabber->summaryFill("Other",startDate,endDate);

    //Set tree widget table headers
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->headerItem()->setText(0,"");
    ui->treeWidget->headerItem()->setText(1,"Academic Year");
    ui->treeWidget->headerItem()->setText(2,"Hours");
    ui->treeWidget->headerItem()->setText(3,"Students");


    //ui->comboBox
    //make PME,UME,CME,Other
    int totHoursP = 0;
    int totStudentsP = 0;
    int totHoursU = 0;
    int totStudentsU = 0;
    int totHoursC = 0;
    int totStudentsC = 0;
    int totHoursO = 0;
    int totStudentsO = 0;

    //calculate Header Totals
    for(int m=0; m < (int)postVec.size(); m++) {
        totHoursP = totHoursP + postVec[m].tothours;
        totStudentsP = totStudentsP + postVec[m].totstudents;
        totHoursU = totHoursU + underVec[m].tothours;
        totStudentsU = totStudentsU + underVec[m].totstudents;
        totHoursC = totHoursC + continuingVec[m].tothours;
        totStudentsC = totStudentsC + continuingVec[m].totstudents;
        totHoursO = totHoursO + otherVec[m].tothours;
        totStudentsO = totStudentsO + otherVec[m].totstudents;
    }
    //build headers
    QTreeWidgetItem *pme = root("PME", QString::number(totHoursP), QString::number(totStudentsP));
    QTreeWidgetItem *ume = root("UME", QString::number(totHoursU), QString::number(totStudentsU));
    QTreeWidgetItem *cme = root("CME", QString::number(totHoursC), QString::number(totStudentsC));
    QTreeWidgetItem *other = root("Other", QString::number(totHoursO), QString::number(totStudentsO));

    //build:
    //pme tree
    for(int i=0; i < (int)postVec.size(); i++) {
        QTreeWidgetItem *year1 = yearChild(pme, QString::number(postVec[i].date),QString::number(postVec[i].tothours),QString::number(postVec[i].totstudents));
        for(int j = 0; j < (int)postVec[i].list.size(); j++){
            facultyChild(year1, postVec[i].list[j].faculty,QString::number(postVec[i].list[j].hours),QString::number(postVec[i].list[j].students));
        }
    }
    //ume tree
    for(int i=0; i < (int)underVec.size(); i++) {
        QTreeWidgetItem *year2 = yearChild(ume, QString::number(underVec[i].date),QString::number(underVec[i].tothours),QString::number(underVec[i].totstudents));
        for(int j = 0; j < (int)underVec[i].list.size(); j++){
            facultyChild(year2, underVec[i].list[j].faculty,QString::number(underVec[i].list[j].hours),QString::number(underVec[i].list[j].students));
        }
    }
    //cme tree
    for(int i=0; i < (int)continuingVec.size(); i++) {
        QTreeWidgetItem *year3 = yearChild(cme, QString::number(continuingVec[i].date),QString::number(continuingVec[i].tothours),QString::number(continuingVec[i].totstudents));
        for(int j = 0; j < (int)continuingVec[i].list.size(); j++){
            facultyChild(year3, continuingVec[i].list[j].faculty,QString::number(continuingVec[i].list[j].hours),QString::number(continuingVec[i].list[j].students));
        }
    }
    //other tree
    for(int i=0; i < (int)otherVec.size(); i++) {
        QTreeWidgetItem *year4 = yearChild(other, QString::number(otherVec[i].date),QString::number(otherVec[i].tothours),QString::number(otherVec[i].totstudents));
        for(int j = 0; j < (int)otherVec[i].list.size(); j++){
            facultyChild(year4, otherVec[i].list[j].faculty,QString::number(otherVec[i].list[j].hours),QString::number(otherVec[i].list[j].students));
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
   dialogWindow = new Dialog(this);
   dialogWindow->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("(*.csv)"));
    if (fileName != NULL){
    string filePath = fileName.toStdString();
    DB* db = new DB();
    db->createDatabase();
    string tableName = db->teachingCsvIntoDb(filePath);
    cout << tableName << endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    makeTree(ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt());
}

void MainWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_actionAbout_Canteloupe_triggered()
{
    canteHelp = new About_Canteloupe(this);
    canteHelp -> show();

//    about_canteloupe canteHelp;
//    canteHelp.setModal(true);
//    canteHelp.exec();
}
