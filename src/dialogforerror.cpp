#include "dialogforerror.h"
#include "ui_dialogforerror.h"

DialogForError::DialogForError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogForError)
{
    ui->setupUi(this);
}

//void DialogForError::on_pushButton_clicked()
//{
//    teachingTable = new TeachingTable("Teaching","RemoveError","(MemberName = '') OR (PrimaryDomain = '') OR (StartDate = '') OR (EndDate ='')");
//}

void DialogForError::on_pushButton_2_clicked()
{
    teachingTable = new TeachingTable("Teaching","","(MemberName = '') OR (PrimaryDomain = '') OR (StartDate = '') OR (EndDate ='')");
    teachingTable->showMaximized();
}

void DialogForError::on_pushButton_3_clicked()
{
    teachingTable = new TeachingTable("Teaching","","");
    teachingTable->showMaximized();
}

DialogForError::~DialogForError()
{
    delete ui;
}
