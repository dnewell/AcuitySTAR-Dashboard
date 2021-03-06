#ifndef BUG_REPORT_H
#define BUG_REPORT_H

#include <QDialog>
#include "ui_bug_report.h"
#include <Qtcore>
#include <QtGui>
#include <QMessageBox>
#include "message.h"
#include <window.h>

namespace Ui {
class Bug_Report;
}

class Bug_Report : public QDialog
{
    Q_OBJECT

public:
    explicit Bug_Report(QWidget *parent = 0);
    ~Bug_Report();

private slots:
//    void on_pushButton_2_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_2_clicked();

private:
    Ui::Bug_Report *ui;
};

#endif // BUG_REPORT_H
