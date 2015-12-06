#ifndef DIALOG_H
#define DIALOG_H

#include <QModelIndexList>
#include <QDialog>
#include "ui_dialog.h"
#include <summary.h>
#include <qcustomplot.h>
#include <db.h>
#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QtSql/QtSql>
#include <QDebug>
#include <iostream>
#include <algorithm>
#include <piechart.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Dialog(QWidget *parent = 0);

    ~Dialog();

private slots:
   void make_graph1(int startDate, int endDate);
    void make_graph2(int startDate, int endDate);
    void on_graphBtn_clicked();
    void on_pieChart_clicked();
    void printPieButton();
    void printBarButton();

    void on_print_pie_Button_clicked();

    void on_print_bar_Button_clicked();

private:
    Ui::Dialog *ui;
    bool pie = false;
    QDialog *pieWindow;
    double totals[16];
    QString labels[16];
};

#endif // DIALOG_H
