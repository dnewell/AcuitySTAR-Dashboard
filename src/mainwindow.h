#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog.h>
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

QTreeWidgetItem* root(QString title, QString totalHours, QString totalStudents);
QTreeWidgetItem* yearChild(QTreeWidgetItem *parent, QString yearRange, QString totalHours, QString totalStudents);
void facultyChild(QTreeWidgetItem *parent, QString faculty, QString totalHours, QString totalStudents);

void makeTree(int startDate, int endDate);

private slots:
void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QDialog *dialog;
};

#endif // MAINWINDOW_H
