#ifndef DIALOG_H
#define DIALOG_H

#include <QModelIndexList>
#include <QDialog>
#include <qcustomplot.h>
#include <QModelIndexList>

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

private:
    Ui::Dialog *ui;
    bool pie = false;
    QDialog *pieWindow;
    double totals[16];
    QString labels[16];
};

#endif // DIALOG_H
