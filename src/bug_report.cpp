#include "bug_report.h"
#include "ui_bug_report.h"
#include <Qtcore>
#include <QtGui>
#include <QMessageBox>

Bug_Report::Bug_Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bug_Report)
{
    ui->setupUi(this);
}

Bug_Report::~Bug_Report()
{
    delete ui;
}

void Bug_Report::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "Message sent", "Thanks for your valuable comments!");
}
