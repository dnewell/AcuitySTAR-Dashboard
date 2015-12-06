#include "progressindicator.h"

ProgressIndicator::ProgressIndicator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressIndicator)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
}

ProgressIndicator::~ProgressIndicator()
{
    delete ui;
}
