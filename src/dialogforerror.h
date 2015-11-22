#ifndef DIALOGFORERROR_H
#define DIALOGFORERROR_H

#include <QDialog>
#include <teachingtable.h>

namespace Ui {
class DialogForError;
}

class DialogForError : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForError(const QString &table,const QString &tableFilter,QWidget *parent = 0);
    ~DialogForError();

private slots:
    //void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DialogForError *ui;
    QDialog *teachingTable;
    QDialog *fullTeachingTable;
};

#endif // DIALOGFORERROR_H
