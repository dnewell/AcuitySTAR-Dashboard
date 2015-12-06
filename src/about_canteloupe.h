#ifndef ABOUT_CANTELOUPE_H
#define ABOUT_CANTELOUPE_H

#include <QDialog>
#include "ui_about_canteloupe.h"

namespace Ui {
class About_Canteloupe;
}

class About_Canteloupe : public QDialog
{
    Q_OBJECT

public:
    explicit About_Canteloupe(QWidget *parent = 0);
    ~About_Canteloupe();

private:
    Ui::About_Canteloupe *ui;
};

#endif // ABOUT_CANTELOUPE_H
