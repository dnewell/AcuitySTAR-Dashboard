#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(4);
}

//creates headings
void MainWindow::root(QString title, QString total)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);
    item->setText(1,total);

    ui->treeWidget->addTopLevelItem(item);
    ui->comboBox->addItem("2009");

    ui->comboBox_2->addItem("2009");


    child(item, "value1", "11");
    child(item,"value2", "45");

}

//values inside the headings
void MainWindow::child(QTreeWidgetItem *parent, QString title, QString total)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, title);
    item->setText(1,total);
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
