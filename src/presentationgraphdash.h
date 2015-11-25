#ifndef PRESENTATIONGRAPHDASH_H
#define PRESENTATIONGRAPHDASH_H

#include <QDialog>

namespace Ui {
class PresentationGraphDash;
}

class PresentationGraphDash : public QDialog
{
    Q_OBJECT

public:
    explicit PresentationGraphDash(QWidget *parent = 0);
    ~PresentationGraphDash();
private slots:
     void make_graph1(int startDate, int endDate);

     void on_barBtn_clicked();

     void on_pieBtn_clicked();

     void printPieButton();
     void printBarButton();

private:
    Ui::PresentationGraphDash *ui;
    double totalsPres[2];
    QString labelsPres[2];
    QDialog *pieWindow;

};

#endif // PRESENTATIONGRAPHDASH_H
