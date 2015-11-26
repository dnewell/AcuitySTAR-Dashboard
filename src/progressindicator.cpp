#include "progressindicator.h"
#include "ui_progressindicator.h"
#include <QGraphicsScene>
#include <QMovie>
#include <QDialog>

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
