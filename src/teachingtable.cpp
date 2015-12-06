#include "teachingtable.h"



TeachingTable::TeachingTable(const QString &tableName,const QString &filter, QWidget *parent) :
//TeachingTable::TeachingTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeachingTable)
{
    QSqlDatabase db = QSqlDatabase::database("db_connection");

    if (filter  != ""){
      model = new MySubClassedSqlTableModel(this);
    }
    else{
       model = new QSqlTableModel(this, db);
    }
    //model = new QSqlTableModel(this, db);

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
    setWindowTitle(tr("Table"));

}






void TeachingTable::submit()
{

    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    } else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Table"),
                             tr("The database reported an error: %1")
                             .arg(model->lastError().text()));
    }


}

void TeachingTable::remove()
{

    model->removeRows(0,model->rowCount());
    //model->database().commit();
    QMessageBox msgBox;
    msgBox.setText("All rows which contained errors have been removed.");
    msgBox.setInformativeText("Do you wish to save this change?");
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
          this->close();
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          this->close();
          break;
      default:
          this->close();
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
