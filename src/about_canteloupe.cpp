#include "about_canteloupe.h"
#include "ui_about_canteloupe.h"

About_Canteloupe::About_Canteloupe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_Canteloupe)
{
    ui->setupUi(this);
}

About_Canteloupe::~About_Canteloupe()
{
    delete ui;
}
