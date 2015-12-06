#include "tech_support.h"

Tech_Support::Tech_Support(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tech_Support)
{
    ui->setupUi(this);
}

Tech_Support::~Tech_Support()
{
    delete ui;
}
