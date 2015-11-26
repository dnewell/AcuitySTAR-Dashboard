#ifndef GRANTSFUNDINGGRAPHDASH_H
#define GRANTSFUNDINGGRAPHDASH_H

#include <QDialog>

namespace Ui {
class GrantsFundingGraphDash;
}

class GrantsFundingGraphDash : public QDialog
{
    Q_OBJECT

public:
    explicit GrantsFundingGraphDash(QWidget *parent = 0);
    ~GrantsFundingGraphDash();
private slots:
    void make_graph1(int startDate,int endDate);

    void on_graphBtn_clicked();

    void on_pieBtn_clicked();
    void printPieButton();
    void printBarButton();

private:
    Ui::GrantsFundingGraphDash *ui;
    double totalsGrants[2];
    QString labelsGrants[2];
    double totalsGrantsPie[2];
    QString labelsGrantsPie[2];
};

#endif // GRANTSFUNDINGGRAPHDASH_H
