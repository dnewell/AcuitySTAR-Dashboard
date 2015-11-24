#ifndef PUBLICATIONGRAPHDASH_H
#define PUBLICATIONGRAPHDASH_H

#include <QDialog>

namespace Ui {
class publicationGraphDash;
}

class publicationGraphDash : public QDialog
{
    Q_OBJECT

public:
    explicit publicationGraphDash(QWidget *parent = 0);
    ~publicationGraphDash();

private:
    Ui::publicationGraphDash *ui;
};

#endif // PUBLICATIONGRAPHDASH_H
