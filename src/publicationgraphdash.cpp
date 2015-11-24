#include "publicationgraphdash.h"
#include "ui_publicationgraphdash.h"

publicationGraphDash::publicationGraphDash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::publicationGraphDash)
{
    ui->setupUi(this);
}

publicationGraphDash::~publicationGraphDash()
{
    delete ui;
}
