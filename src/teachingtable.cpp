#include "teachingtable.h"
#include "ui_teachingtable.h"

#include <QtWidgets>
#include <QtSql>


TeachingTable::TeachingTable(const QString &tableName,const QString &filter, QWidget *parent) :
//TeachingTable::TeachingTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeachingTable)
{
    //ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");  //without all the QDir stuff, will only look in current working directory
    db.open();

    //QSqlQueryModel *model = new QSqlQueryModel;
    model = new QSqlTableModel(this);
    //model->setQuery("SELECT * from teaching");
    //model->setTable("teaching");
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    if (filter  != ""){
           model->setFilter(filter);
    }

    model->select();

   // model->setFilter("(MemberName = '') OR (PrimaryDomain = '') OR (StartDate = '') OR (EndDate ='')");
    QTableView *view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
    //view->show();
    //db.close();

    submitButton = new QPushButton(tr("Save Change"));
    submitButton->setDefault(true);
    revertButton = new QPushButton(tr("&Revert"));
    if (filter  != ""){
      deleteButton = new QPushButton(tr("&Ignore All Errors"));
    }
    //deleteButton = new QPushButton(tr("&Delete"));
    quitButton = new QPushButton(tr("Close"));
    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    if (filter  != ""){
      buttonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);
    }
    //buttonBox->addButton(deleteButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(revertButton, SIGNAL(clicked()), model, SLOT(revertAll()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    if (filter  != ""){
      connect(deleteButton, SIGNAL(clicked()), this, SLOT(remove()));
    }

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("Teaching Table"));

}


void TeachingTable::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Teaching Table"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }
}

void TeachingTable::remove()
{

    model->removeRows(0,model->rowCount());
    //model->database().commit();
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to delete all the error rows?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Save:
        model->database().transaction();
        if (model->submitAll()) {
            model->database().commit();
        } else {
            model->database().rollback();
            QMessageBox::warning(this, tr("Teaching Table"),
                                 tr("The database reported an error: %1")
                                 .arg(model->lastError().text()));
        }
       this->close();
          break;
      case QMessageBox::Discard:
          model->revertAll();
          // Don't Save was clicked
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
}

int TeachingTable::getRowNumbers()
{
    return model->rowCount();
}


TeachingTable::~TeachingTable()
{
    delete ui;
}
