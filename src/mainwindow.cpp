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
#include <publicationgraphdash.h>
#include <presentationgraphdash.h>
#include <grantsfundinggraphdash.h>

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
  if(filePath.contains("Teaching")){
   dialogWindow = new Dialog(filePath, this);
   dialogWindow->show();
  }else if(filePath.contains("Publications")){

      QDialog *pubDash = new publicationGraphDash(this);
      pubDash->show();
  }else if(filePath.contains("Presentations")){

      QDialog *presDash = new PresentationGraphDash(this);
      presDash->show();
  }else if(filePath.contains("Grants")){

      QDialog *grantsDash = new GrantsFundingGraphDash(this);
      grantsDash->show();
  }
}


void MainWindow::on_pushButton_2_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("(*.csv)"));
    if (filePath != NULL){
    string filePathSt = filePath.toStdString();
    DB* db = new DB();
    db->createDatabase();
    db->teachingCsvIntoDb(filePathSt);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    makeTree(ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt());
//    makePrint(ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt(),"Teaching");
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
//void MainWindow::makePrint(int start_year, int end_year, QString CSV_type){
//    ui->treeWidget->clear();

//    if(CSV_type==""){
//        ui->treeWidget->setColumnCount(4);
//    }

//    if(CSV_type=="Teaching"){
//        ui->treeWidget->headerItem()->setText(0,"");
//        ui->treeWidget->headerItem()->setText(1,"Academic Year");
//        ui->treeWidget->headerItem()->setText(2,"Hours");
//        ui->treeWidget->headerItem()->setText(3,"Students");
//    }
//    else if(CSV_type=="Presentations"){
//        ui->treeWidget->headerItem()->setText(0,"");
//        ui->treeWidget->headerItem()->setText(1,"Academic Year");
//        ui->treeWidget->headerItem()->setText(2,"# of Presentations");
//        ui->treeWidget->headerItem()->setText(3,"");
//    }
//    else if(CSV_type=="Publications"){
//        ui->treeWidget->headerItem()->setText(0,"");
//        ui->treeWidget->headerItem()->setText(1,"Type");
//        ui->treeWidget->headerItem()->setText(2,"Total");
//        ui->treeWidget->headerItem()->setText(3,"");
//    }
//    else if (CSV_type == "Grants"){
//        ui->treeWidget->headerItem()->setText(0,"");
//        ui->treeWidget->headerItem()->setText(1,"Funding Type");
//        ui->treeWidget->headerItem()->setText(2,"Total #");
//        ui->treeWidget->headerItem()->setText(3,"Total $");
//    }

//    //get data for vectors
//    Summary* summary = new Summary();
//    QVector<double> Tier_1_Tot, Tier_2_Tot, Tier_3_Tot;
//    QVector<QString> Tier_1_Fields, Tier_2_Fields, Tier_3_Fields;
//    QString printString;



//    if (CSV_type == "Teaching"){
//        Tier_1_Fields = {"PME", "CME", "UME", "Other"};

//        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
//        for (int y = start_year; y <= end_year; y++){
//            Tier_2_Fields.insert(y-start_year,QString::number(y));
//        }

//    }
//    else if (CSV_type == "Grants"){
//        Tier_1_Fields = {"Grants", "Clinical Funding"};
//        Tier_2_Fields = {"Peer Reviewed", "Industry Sponsored"};
//    }
//    else if (CSV_type == "Publications"){
//        Tier_1_Fields = {"Publications"};
//        Tier_2_Fields = {"Published Abstracts", "Journal Articles", "Books", "Book Chapters", "Letters to Editor"};
//    }
//    else if (CSV_type == "Presentations"){
//        Tier_1_Fields = {"Invited Lectures", "Abstracts Presented", "Next Presentation"};

//        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
//        for (int y = start_year; y <= end_year; y++){
//            Tier_2_Fields.insert(y-start_year,QString::number(y));
//        }

//    }

//    //iterate once on each Tier_1 element
//    for (int x = 0; x < Tier_1_Fields.length(); x++){

//        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[x] ,start_year ,end_year ,CSV_type));

//        printString = printString + "\n " + Tier_1_Fields[x] + " : ";

//        for (int totIndex = 0; totIndex < Tier_1_Tot.length();totIndex++){

//            printString = printString + " " + Tier_1_Tot[totIndex] + " ";

//        }//for totIndex

//        //iterate once on each Tier_2 element
//        for (int y = 0; y < Tier_2_Fields.length(); y++){

//            Tier_2_Tot=(summary->getTier2(Tier_1_Fields[x], Tier_2_Fields[y], start_year, end_year, CSV_type));

//            printString = printString + "\n " + Tier_2_Fields[y] + " : ";

//            for (int totIndex = 0; totIndex < Tier_2_Tot.length();totIndex++){

//                printString = printString + " " + Tier_2_Tot[totIndex] + " ";

//            }//for totIndex

//            //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]
//            Tier_3_Fields=(summary->getFaculty(Tier_1_Fields[x], Tier_2_Fields[y], start_year, end_year, CSV_type));

//            //iterate once for each Tier_3 element
//            for (int z = 0; z < Tier_3_Fields.length(); z++){

//                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[x], Tier_2_Fields[y], Tier_3_Fields[z], start_year, end_year, CSV_type));

//                printString = printString + "\n " + Tier_3_Fields[z] + " : ";

//                for (int totIndex = 0; totIndex < Tier_3_Tot.length();totIndex++){

//                    printString = printString + " " + Tier_3_Tot[totIndex] + " ";

//                }//for totIndex

//            }//for z

//        }//for y

//    }//for x

//    qDebug()<< printString;

//}//makeTree

