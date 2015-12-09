#include "bug_report.h"


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
    QMessageBox::information(this, "Message sent", "Thank you for your feedback!");
}
