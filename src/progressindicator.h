#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QDialog>
#include "ui_progressindicator.h"
#include <QGraphicsScene>
#include <QMovie>

namespace Ui {
class ProgressIndicator;
}

class ProgressIndicator : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressIndicator(QWidget *parent = 0);
    ~ProgressIndicator();

private:
    Ui::ProgressIndicator *ui;
};

#endif // PROGRESSINDICATOR_H
