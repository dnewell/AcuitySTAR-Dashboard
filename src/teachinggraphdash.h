#ifndef TEACHINGGRAPHDASH_H
#define TEACHINGGRAPHDASH_H

#include <QModelIndexList>
#include <QDialog>
#include <qcustomplot.h>
#include <QModelIndexList>

namespace Ui {
class TeachingGraphDash;
}

class TeachingGraphDash : public QDialog
{
    Q_OBJECT

public:

    explicit TeachingGraphDash(QWidget *parent = 0);

    ~TeachingGraphDash();

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
    Ui::TeachingGraphDash *ui;
    bool pie = false;
    QDialog *pieWindow;
    double totals[16];
    QString labels[16];
};

#endif // TEACHINGGRAPHDASH_H
