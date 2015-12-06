#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QPushButton>
#include "about_canteloupe.h"
#include <string>
#include <QString>
#include <stdio.h>
#include <iostream>
#include <dialogforerror.h>
#include <teachinggraphdash.h>
#include <teachingtable.h>
#include "bug_report.h"
#include "tech_support.h"

using namespace std;
extern QString filePath;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    QTreeWidgetItem* root(QString title, QString totalHours, QString totalStudents);
//    void makePrint(int start_year, int end_year, QString CSV_type);
//    QTreeWidgetItem* yearChild(QTreeWidgetItem *parent, QString yearRange, QString totalHours, QString totalStudents);
//    void facultyChild(QTreeWidgetItem *parent, QString faculty, QString totalHours, QString totalStudents);


    QTreeWidgetItem* root(QString title, QVector<double> totals);
    QTreeWidgetItem* tier2_root(QTreeWidgetItem *parent, QString Tier_name, QVector<double> totals);
    void tier3_root(QTreeWidgetItem *parent, QString Tier_name, QVector<double> totals);


void makeTree2(int startDate, int endDate);
void makeEmptyTree();
QTreeWidgetItem* root2(QString title, QString totalHours, QString totalStudents);
    void makeTree(int startDate, int endDate, QString CSV_type);

private slots:
    void browse();
    void print();
    void on_button_graph_clicked();
    void on_actionAbout_Canteloupe_triggered();
    void on_button_display_clicked();
	void on_tabWidget_tabBarClicked(int index);
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionReport_Bugs_triggered();
    void on_actionTechnical_Support_triggered();
    void on_actionContext_Help_triggered();
    void autoComplete();

    void on_button_refresh_clicked();

    void on_actionPrint_triggered();

    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    QDialog *dialogWindow;
    About_Canteloupe *canteHelp;
    QDialog *dialogForError;
    QDialog *table;
    Bug_Report *bug;
    Tech_Support *tech;
};

#endif // MAINWINDOW_H
