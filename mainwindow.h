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

QTreeWidgetItem* root(QString title, Vector<Doubles> totals);
QTreeWidgetItem* root(QTreeWidgetItem *parent, QString Tier_name, Vector<Doubles> totals);

void MainWindow::makeTree(int start_year, int end_year, CSV_type);

private slots:
void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QDialog *dialog;
};

#endif // MAINWINDOW_H
