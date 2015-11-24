#include "bug_report.h"
#include "ui_bug_report.h"
#include <Qtcore>
#include <QtGui>
#include <QMessageBox>
#include <message.h>
#include <window.h>

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

//    Window window1;
//    QStringList headers;
//    headers << "Subject: Message sent"
//            << "From: julianztz@gmail.com";
//    QString body = "Thank you! /r/n";
//    Message message(body, headers);

//    window1.setMessage(message);

//    Window window2;
//    QObject::connect(&window1, SIGNAL(messageSent(Message)),
//                     &window2, SLOT(setMessage(Message)));
//    QObject::connect(&window2, SIGNAL(messageSent(Message)),
//                     &window1, SLOT(setMessage(Message)));
//    window1.show();
//    window2.show();
}
