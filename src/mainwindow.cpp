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
#include "bug_report.h"
#include "tech_support.h"
#include <QMessageBox>
#include "progressindicator.h"

using namespace std;
extern string tab_focus;
QString file_path;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makeEmptyTree();
}

void MainWindow::makeTree(int start_year, int end_year, QString CSV_type){
    ui->treeWidget->clear();

    if(CSV_type=="Teaching"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Academic Year");
        ui->treeWidget->headerItem()->setText(2,"Hours");
        ui->treeWidget->headerItem()->setText(3,"Students");
    }
    else if(CSV_type=="Presentations"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Academic Year");
        ui->treeWidget->headerItem()->setText(2,"# of Presentations");
        ui->treeWidget->headerItem()->setText(3,"");
    }
    else if(CSV_type=="Publications"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Type of Publication  ");
        ui->treeWidget->headerItem()->setText(2,"Total");
        ui->treeWidget->headerItem()->setText(3,"");
    }
    else if (CSV_type == "Grants"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Funding or Grant Type");
        ui->treeWidget->headerItem()->setText(2,"Total #");
        ui->treeWidget->headerItem()->setText(3,"Total $");
    }

    //get data for vectors
    Summary* summary = new Summary();
    QVector<double> Tier_1_Tot, Tier_2_Tot, Tier_3_Tot;

    QVector<QString> Tier_1_Fields, Tier_2_Fields, Tier_3_Fields;


//TEACHING
    if (CSV_type == "Teaching")
    {
        Tier_1_Fields = {"PME", "CME", "UME", "Other"};
        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
        for (int y = start_year; y <= end_year; y++)
        {
            Tier_2_Fields.insert(y-start_year,QString::number(y));
        }

        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *pme = root(Tier_1_Fields[0], Tier_1_Tot);
        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[1] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *cme = root(Tier_1_Fields[1], Tier_1_Tot);
        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[2] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *ume = root(Tier_1_Fields[2], Tier_1_Tot);
        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[3] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *other = root(Tier_1_Fields[3], Tier_1_Tot);

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_pme = tier2_root(pme, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_cme = tier2_root(cme, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_ume = tier2_root(ume, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[3], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_other = tier2_root(other, Tier_2_Fields[i], Tier_2_Tot);
                //INSERT CODE TO DISPLAY TIER_2_DATA IN GUI

                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

                Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_pme, Tier_3_Fields[j], Tier_3_Tot);
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                tier3_root(t2_cme, Tier_3_Fields[j], Tier_3_Tot);
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));

            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[2], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                tier3_root(t2_ume, Tier_3_Fields[j], Tier_3_Tot);
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[3], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[3], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                tier3_root(t2_other, Tier_3_Fields[j], Tier_3_Tot);
            }
       }
    }

    //GRANTS
    else if (CSV_type == "Grants"){
        Tier_1_Fields = {"Grants", "Clinical Trials"};
        Tier_2_Fields = {"Peer Reviewed", "Industry Sponsored"};

        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *grants = root(Tier_1_Fields[0], Tier_1_Tot);
        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[1] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *funding = root(Tier_1_Fields[1], Tier_1_Tot);

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_grants = tier2_root(grants, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_funding = tier2_root(funding, Tier_2_Fields[i], Tier_2_Tot);
                //INSERT CODE TO DISPLAY TIER_2_DATA IN GUI

                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_grants, Tier_3_Fields[j], Tier_3_Tot);
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                tier3_root(t2_funding, Tier_3_Fields[j], Tier_3_Tot);
            }
       }
    }

    //PUBLICATIONS
    else if (CSV_type == "Publications"){
        Tier_1_Fields = {"Publications"};
        Tier_2_Fields = {"Published Abstracts", "Journal Articles", "Books", "Book Chapters", "Letters to Editor"};

        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *pub = root(Tier_1_Fields[0], Tier_1_Tot);

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_pub = tier2_root(pub, Tier_2_Fields[i], Tier_2_Tot);
                //INSERT CODE TO DISPLAY TIER_2_DATA IN GUI

                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

                Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_pub, Tier_3_Fields[j], Tier_3_Tot);
            }
        }
    }

    //PRESENTATIONS
    else if (CSV_type == "Presentations")
    {
        Tier_1_Fields = {"Invited Lectures", "Abstracts Presented", "Other"};

        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
        for (int y = start_year; y <= end_year; y++){
            Tier_2_Fields.insert(y-start_year,QString::number(y));
        }

        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *invite = root("Invited Lectures", Tier_1_Tot);
        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[1] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *abstract = root("Abstracts Presented", Tier_1_Tot);
        Tier_1_Tot=(summary->getTier1(Tier_1_Fields[2] ,start_year ,end_year ,CSV_type));
        QTreeWidgetItem *next = root("Other", Tier_1_Tot);

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_invite = tier2_root(invite, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_abstract = tier2_root(abstract, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));
                QTreeWidgetItem *t2_next = tier2_root(next, Tier_2_Fields[i], Tier_2_Tot);


                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

                Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_invite, Tier_3_Fields[j], Tier_3_Tot);
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                tier3_root(t2_abstract, Tier_3_Fields[j], Tier_3_Tot);
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));

            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                Tier_3_Tot=(summary->getTier3(Tier_1_Fields[2], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                tier3_root(t2_next, Tier_3_Fields[j], Tier_3_Tot);
            }
        }
    }

    //resize columns
    for(int n = 0; n < 4; n++)
    {
        ui->treeWidget->resizeColumnToContents(n);
    }
}

//creates headings
//sets tier_1 header name and totals
QTreeWidgetItem* MainWindow::root(QString title, QVector<double> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);

    for(int x = 0; x < totals.length(); x++){
        cout<<"Totals:"<<totals[x]<<endl;
        item->setText(x+2,QString::number(totals[x]));
    }
    ui->treeWidget->addTopLevelItem(item);
    return item;
}

//sets tier_2 and tier_3 header names and totals
QTreeWidgetItem* MainWindow::tier2_root(QTreeWidgetItem *parent, QString Tier_name, QVector<double> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,Tier_name);

    for(int x = 0; x < totals.length(); x++){
        item->setText(x+2,QString::number(totals[x]));
    }

    parent->addChild(item);
    return item;
}
void MainWindow::tier3_root(QTreeWidgetItem *parent, QString Tier_name, QVector<double> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,Tier_name);

    for(int x = 0; x < totals.length(); x++){
        item->setText(x+2,QString::number(totals[x]));
    }

    parent->addChild(item);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
  if(file_path.contains("Teaching"))
  {
   dialogWindow = new Dialog(file_path, this);
   dialogWindow->setWindowTitle("Teaching Graphs");
   dialogWindow->show();
  }else if(file_path.contains("Publications"))
  {
      QDialog *pubDash = new publicationGraphDash(this);
      pubDash->setWindowTitle("Publications Graphs");
      pubDash->show();
  }else if(file_path.contains("Presentations"))
  {
      QDialog *presDash = new PresentationGraphDash(this);
      presDash->setWindowTitle("Presentations Graphs");
      presDash->show();
  }else if(file_path.contains("Grants"))
  {
      QDialog *grantsDash = new GrantsFundingGraphDash(this);
      grantsDash->setWindowTitle("Grants Graphs");
      grantsDash->show();
  }
}

////////////////////////////////////////////////////////////////
void MainWindow::on_pushButton_2_clicked()
{
    file_path = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("(*.csv)"));
    if (file_path  != NULL){
    string filePathSt = file_path.toStdString();
    DB* db = new DB();
    ProgressIndicator *progressIndicator = new ProgressIndicator();
    progressIndicator->show();

    db->createDatabase();
    string tableName = db->teachingCsvIntoDb(filePathSt);
    QString table = QString::fromStdString(tableName);

    QString tableFilter = "";
    if (tableName == "Teaching"){
        tableFilter = "(MemberName = '') OR (PrimaryDomain = '') OR (StartDate = '') OR (EndDate ='')";
    }

    dialogForError = new DialogForError(table,tableFilter);
    progressIndicator->close();
    dialogForError->show();
    }
}

//void MainWindow::on_pushButton_3_clicked()
//{
//    makeTree(ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt());
//    makePrint(ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt(),"Teaching");
//}

//void MainWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
//{
//
//}

void MainWindow::on_actionAbout_Canteloupe_triggered()
{
    canteHelp = new About_Canteloupe(this);
    canteHelp -> show();
}


//creates headings
QTreeWidgetItem* MainWindow::root2(QString title, QString totalHours, QString totalStudents)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);
    item->setText(2,totalHours);
    item->setText(3,totalStudents);
    ui->treeWidget->addTopLevelItem(item);
    return item;
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

void MainWindow::makeEmptyTree(){
    ui->treeWidget->clear();
    //Set tree widget table headers
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->headerItem()->setText(0,"");
    ui->treeWidget->headerItem()->setText(1,"Academic Year");
    ui->treeWidget->headerItem()->setText(2,"Hours");
    ui->treeWidget->headerItem()->setText(3,"Students");

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    //build headers
    QTreeWidgetItem *pme = root2("PME", "0", "0");
    pme->addChild(item);
    QTreeWidgetItem *ume = root2("UME", "0","0");
    QTreeWidgetItem *item2 = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    ume->addChild(item2);
    QTreeWidgetItem *cme = root2("CME", "0", "0");
    QTreeWidgetItem *item3 = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    cme->addChild(item3);
    QTreeWidgetItem *other = root2("Other", "0", "0");
    QTreeWidgetItem *item4 = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    other->addChild(item4);

    //hide tree
    pme->setHidden(true);
    cme->setHidden(true);
    ume->setHidden(true);
    other->setHidden(true);
}

//print
void MainWindow::on_pushButton_4_clicked()
{
    table = new TeachingTable("Teaching","");
    table->showMaximized();
}


//tabs
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch(index)
    {
    case 0:
       // tab_focus = "Teaching";
        ui->main_window_label->setText("Teaching");
        makeTree(1975,2015, "Teaching");
        break;
    case 1:
        //tab_focus = "Publications";
        ui->main_window_label->setText("Publications");
        makeTree(1975,2015, "Publications");
        break;
    case 2:
       // tab_focus = "Funding";
        ui->main_window_label->setText("Funding");
        makeTree(1975,2015, "Grants");
        break;
    case 3:
       // tab_focus = "Presentations";
        ui->main_window_label->setText("Presentations");
        makeTree(1975,2015, "Presentations");
        break;
    default:
        break;
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    on_pushButton_2_clicked();
}

void MainWindow::on_actionReport_Bugs_triggered()
{
    bug = new Bug_Report(this);
    bug -> show();
}

void MainWindow::on_actionTechnical_Support_triggered()
{
    tech = new Tech_Support(this);
    tech -> show();
}

void MainWindow::on_actionContext_Help_triggered()
{
    QDesktopServices::openUrl(QUrl("http://canteloupe.s3-website-us-east-1.amazonaws.com/help.html", QUrl::TolerantMode));
}
