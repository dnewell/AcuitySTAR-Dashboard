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
    explicit Dialog(QModelIndexList selectedList, QWidget *parent = 0, int startDate=0, int endDate=0);
    ~Dialog();

private slots:
   void make_graph1(int startDate, int endDate, QModelIndexList selectedList);
    void make_graph2(int startDate, int endDate, QModelIndexList selectedList);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
