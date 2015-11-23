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
    explicit Dialog(QString filePath, QWidget *parent = 0);
    QString FILE_PATH;
    ~Dialog();

private slots:
   void make_graph1(int startDate, int endDate);
    void make_graph2(int startDate, int endDate);
    void on_graphBtn_clicked();
    void on_pieChart_clicked();

private:
    Ui::Dialog *ui;
    bool pie = false;
    QDialog *pieWindow;
};

#endif // DIALOG_H
