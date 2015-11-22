#ifndef FILTER_H
#define FILTER_H

#include <QDialog>

namespace Ui {
class filter;
}

class filter : public QDialog
{
    Q_OBJECT

public:
    explicit filter(QWidget *parent = 0, int startDate=0, int endDate=0);
    ~filter();

private slots:
    void on_pushButton_clicked();

private:
    Ui::filter *ui;
    QDialog *dialog;
    int startDate;
    int endDate;
};

#endif // FILTER_H
