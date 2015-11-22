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

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makeTree(0,0);
}

void MainWindow::makeTree(int start_year, int end_year, CSV_type){
    ui->treeWidget->clear();
    
    //get data for vectors
    Summary* summary = new Summary();
    double Tier_1_Tot, Tier_2_Tot, Tier_3_Tot; 
    Vector<QTreeWidgetItem> Tier_1_Data, Tier_2_Data, Tier_3_Data; 
    Vector<QStrings> Tier_1_Fields, Tier_2_Fields, Tier_3_Fields; 
    
    Tier_1_Tot = 0; Tier_2_Tot = 0; Tier_3_Tot = 0;
    
    
    if (CSV_type == "Teaching"){
        Tier_1_Fields = ("PME", "CME", "UME", "Other");
        
        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
        for (y = start_year; y < end_year; y++){
            Tier_2_Fields[y - start_year] = "" + y + " - " + y+1; 
        }
        
    }
    else if (CSV_type == "Grants"){
        Tier_1_Fields = ("Grants", "Clinical Funding");
        Tier_2_Fields = ("Peer Reviewed", "Industry Sponsored");
    }
    else if (CSV_type == "Publications"){
        Tier_1_Fields = ("Publications");
        Tier_2_Fields = ("Published Abstracts", "Journal Articles", "Books", "Book Chapters", "Letters to Editor");
    }
    else {
        Tier_1_Fields = ("Invited Lectures", "Abstracts Presented", "Next Presentation");
        
        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
        for (y = start_year; y < end_year; y++){
            Tier_2_Fields[y - start_year] = "" + y + " - " + y+1; 
        }
        
    }
    
    //iterate once on each Tier_1 element 
    for (x = 0; x < Tier_1_Fields.length(); x++){
        
        Tier_1_Tot = summary(Tier_1_Fields[x] ,start_year ,end_year ,CSV_type);
        
        Tier_1_Data[x] = root(Tier_1_Fields[x], Tier_1_Tot);
        
        //INSERT CODE TO DISPLAY TIER_1_DATA IN GUI
        
        //iterate once on each Tier_2 element
        for (y = 0; y < Tier_2_Fields.length(); y++){
            
            Tier_2_Tot = summary(Tier_1_Fields[x], Tier_2_Fields[y], start_year, end_year, CSV_type);
            
            Tier_2_Data[y] = root(Tier_1_Data[x], Tier_2_Fields[y],Tier_2_Tot);
            
            //INSERT CODE TO DISPLAY TIER_2_DATA IN GUI
            
            //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]
            Tier_3_Fields = summary(Tier_1_Fields[x], Tier_2_Fields[y], start_year, end_year, CSV_ype;
            
            //iterate once for each Tier_3 element 
            for (z = 0; z < Tier_3_Fields.length(); z++){
                
                Tier_3_Tot = summary(Tier_1_Fields[x], Tier_2_Fields[y], Tier_3_Fields[z], start_year, end_year, CSV_type);
                
                Tier_3_Data[z] = root(Tier_2_Data[y], Tier_3_Fields[z], Tier_3_Tot);
                
                //INSERT CODE TO DISPLAY TIER_3_DATA IN GUI
                
            }//for z 
            
        }//for y 
        
    }//for x
    
}

//sets tier_1 header name and totals 
QTreeWidgetItem* MainWindow::root(QString title, Vector<Doubles> totals){
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);
    
    for(int x = 2; x < totals.length(); x++){
        item->setText(x,totals[x-2]);        
    }
    
    ui->treeWidget->addTopLevelItem(item);
    return item;
}

//sets tier_2 and tier_3 header names and totals 
QTreeWidgetItem* MainWindow::root(QTreeWidgetItem *parent, QString Tier_name, Vector<Doubles> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,Tier_name);
    
    for(in x = 2; x < totals.length()+2; x++){
        item->setText(x,totals[x-2]);
    }
    
    parent->addChild(item);
    return item;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    dialog = new Dialog(this,ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt());
    dialog->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("(*.csv)"));
    if (fileName != NULL){
    string filePath = fileName.toStdString();
    DB* db = new DB();
    db->createDatabase();
    db->teachingCsvIntoDb(filePath);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    makeTree(ui->comboBox->currentText().toInt(),ui->comboBox_2->currentText().toInt());
}
