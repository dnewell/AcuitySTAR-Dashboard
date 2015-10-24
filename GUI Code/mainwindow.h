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

void root(QString title, QString total);
void child(QTreeWidgetItem *parent, QString name, QString total);

private slots:
void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QDialog *dialog;
};

#endif // MAINWINDOW_H
