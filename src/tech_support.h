#ifndef TECH_SUPPORT_H
#define TECH_SUPPORT_H

#include <QDialog>

namespace Ui {
class Tech_Support;
}

class Tech_Support : public QDialog
{
    Q_OBJECT

public:
    explicit Tech_Support(QWidget *parent = 0);
    ~Tech_Support();

private:
    Ui::Tech_Support *ui;
};

#endif // TECH_SUPPORT_H
