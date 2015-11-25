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
//    QGraphicsScene scene;
//    QLabel *gif_anim = new QLabel();
//    QMovie *movie = new QMovie("progress.gif");
//    gif_anim->setMovie(movie);
//    movie->start();
//    QGraphicsProxyWidget *proxy = scene.addWidget(gif_anim);
}

ProgressIndicator::~ProgressIndicator()
{
    delete ui;
}
