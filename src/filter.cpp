#include "filter.h"
#include "ui_filter.h"
#include <dialog.h>
#include <QItemSelectionModel>
#include <QModelIndexList>

using namespace std;

filter::filter(QWidget *parent, int strtDate, int endDte) :
    QDialog(parent),
    ui(new Ui::filter)
{
    ui->setupUi(this);
    //Build list items
    ui->listWidget->addItem("Total Hours");
    ui->listWidget->addItem("Number of Teaching Sessions or Week");
    ui->listWidget->addItem("Number of trainees");
    ui->listWidget->addItem("Hours per Teaching Sessions or Week");
    //save our startDate and endDate to global
    startDate = strtDate;
    endDate = endDte;
}

filter::~filter()
{
    delete ui;
}

void filter::on_pushButton_clicked()
{
    //Get selected filters
    QItemSelectionModel * selections = ui->listWidget->selectionModel();
    QModelIndexList indexes = selections->selectedIndexes();


    dialog = new Dialog(indexes, this, startDate, endDate);
    dialog->show();
}
