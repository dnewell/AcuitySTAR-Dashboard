#ifndef TEACHINGTABLE_H
#define TEACHINGTABLE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;


namespace Ui {
class TeachingTable;
}
/***
class MySubClassedSqlTableModel : public QSqlTableModel
{
public:
    MySubClassedSqlTableModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase());
};***/

class TeachingTable : public QDialog
{
    Q_OBJECT


public:

    //explicit TeachingTable(QWidget *parent = 0);
    explicit TeachingTable(const QString &tableName,const QString &filter,QWidget *parent = 0);
    ~TeachingTable();
    int getRowNumbers();

private slots:
   void submit();
   void remove();

private:
    QPushButton *submitButton;
    QPushButton *revertButton;
    QPushButton *deleteButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;


private:
    Ui::TeachingTable *ui;

};

class MySubClassedSqlTableModel : public QSqlTableModel
    {
        Q_OBJECT
        public:
           MySubClassedSqlTableModel(QObject * parent = 0, QSqlDatabase db = QSqlDatabase::database("db_connection"))
           : QSqlTableModel(parent,db) {;}
           QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const
           {
              if(role==Qt::BackgroundColorRole)
              {
                 const QVariant value(data(index,Qt::DisplayRole));
                 return QVariant(QColor(value.toString()==""?Qt::red:Qt::white));
              }
              return QSqlTableModel::data(index,role);
           }
    };

#endif // TEACHINGTABLE_H
