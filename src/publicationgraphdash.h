#ifndef PUBLICATIONGRAPHDASH_H
#define PUBLICATIONGRAPHDASH_H

#include <QDialog>

namespace Ui {
class publicationGraphDash;
}

class publicationGraphDash : public QDialog
{
    Q_OBJECT

public:
    explicit publicationGraphDash(QWidget *parent = 0);
    ~publicationGraphDash();
private slots:
     void make_graph1(int startDate, int endDate);
     void on_barBtn_clicked();

     void on_pieBtn_clicked();
     void printPieButton();
     void printBarButton();

     void on_pushButton_clicked();

     void on_pushButton_2_clicked();

private:
    Ui::publicationGraphDash *ui;
    bool pie = false;
    QDialog *pieWindow;
    double totalsPub[2];
    QString labelsPub[2];
};

#endif // PUBLICATIONGRAPHDASH_H
