#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QPushButton>
#include "about_canteloupe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString filePath;
    ~MainWindow();

    QTreeWidgetItem* root(QString title, QString totalHours, QString totalStudents);
//    void makePrint(int start_year, int end_year, QString CSV_type);
    QTreeWidgetItem* yearChild(QTreeWidgetItem *parent, QString yearRange, QString totalHours, QString totalStudents);
    void facultyChild(QTreeWidgetItem *parent, QString faculty, QString totalHours, QString totalStudents);

    void makeTree(int startDate, int endDate);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);
    void on_actionAbout_Canteloupe_triggered();

    void on_pushButton_4_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    QDialog *dialogWindow;
    About_Canteloupe *canteHelp;
};

#endif // MAINWINDOW_H
