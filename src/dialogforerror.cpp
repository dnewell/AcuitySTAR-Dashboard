#include "dialogforerror.h"
#include "ui_dialogforerror.h"
QString a = "";
QString b = "";
DialogForError::DialogForError(const QString &table,const QString &tableFilter,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogForError)
{
    a = table;
    b = tableFilter;

    ui->setupUi(this);

}

void DialogForError::on_pushButton_2_clicked()
{
    teachingTable = new TeachingTable(a,b);
    teachingTable->showMaximized();
}

void DialogForError::on_pushButton_3_clicked()
{
    fullTeachingTable = new TeachingTable(a,"");
    fullTeachingTable->showMaximized();
}

DialogForError::~DialogForError()
{
    delete ui;
}
