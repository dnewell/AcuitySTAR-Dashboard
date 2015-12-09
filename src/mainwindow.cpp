#include "mainwindow.h"

using namespace std;

extern string tab_focus = "Teaching";
static OpenCSV *db;

QString file_path;

//teaching
static QTreeWidgetItem *pme;
static QTreeWidgetItem *cme;
static QTreeWidgetItem *ume;
static QTreeWidgetItem *teaching_other;

//grants
static QTreeWidgetItem *grants;
static QTreeWidgetItem *funding;

//publications
static QTreeWidgetItem *pub;

//presentatiosns
static QTreeWidgetItem *invite;
static QTreeWidgetItem *abstract;
static QTreeWidgetItem *pres_other;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("Last Name, First Name");
    makeEmptyTree();
}

void MainWindow::makeTree(int start_year, int end_year, QString CSV_type){



    int count=0;

    if(CSV_type=="Teaching"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Academic Year");
        ui->treeWidget->headerItem()->setText(2,"Hours");
        ui->treeWidget->headerItem()->setText(3,"Students");
    }
    else if(CSV_type=="Presentations"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Academic Year");
        ui->treeWidget->headerItem()->setText(2,"# of Presentations");
        ui->treeWidget->headerItem()->setText(3,"");
    }
    else if(CSV_type=="Publications"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Type of Publication  ");
        ui->treeWidget->headerItem()->setText(2,"Total");
        ui->treeWidget->headerItem()->setText(3,"");
    }
    else if (CSV_type == "Grants"){
        ui->treeWidget->headerItem()->setText(0,"");
        ui->treeWidget->headerItem()->setText(1,"Funding or Grant Type");
        ui->treeWidget->headerItem()->setText(2,"Total #");
        ui->treeWidget->headerItem()->setText(3,"Total $");
    }

    //get data for vectors
    Summary* summary = new Summary();
    QVector<double> Tier_1_Tot, Tier_2_Tot, Tier_3_Tot;
    QVector<QString> Tier_1_Fields, Tier_2_Fields, Tier_3_Fields;
    QString faculty=ui->lineEdit->text();


//TEACHING
    if (CSV_type == "Teaching")
    {
        Tier_1_Fields = {"PME", "CME", "UME", "Other"};
        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
        for (int y = start_year; y <= end_year; y++)
        {
            Tier_2_Fields.insert(y-start_year,QString::number(y));
            QCoreApplication::processEvents();
        }

        if(faculty==""){
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
            pme = root(Tier_1_Fields[0], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[1] ,start_year ,end_year ,CSV_type));
            cme = root(Tier_1_Fields[1], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[2] ,start_year ,end_year ,CSV_type));
            ume = root(Tier_1_Fields[2], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[3] ,start_year ,end_year ,CSV_type));
            teaching_other = root(Tier_1_Fields[3], Tier_1_Tot);
        }
        else{
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[0] ,faculty ,start_year ,end_year ,CSV_type));
            pme = root(Tier_1_Fields[0], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[1] ,faculty ,start_year ,end_year ,CSV_type));
            cme = root(Tier_1_Fields[1], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[2] ,faculty ,start_year ,end_year ,CSV_type));
            ume = root(Tier_1_Fields[2], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[3] ,faculty ,start_year ,end_year ,CSV_type));
            teaching_other = root(Tier_1_Fields[3], Tier_1_Tot);
        }

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
            QCoreApplication::processEvents();
            count++;
            QTreeWidgetItem *t2_pme;
            QTreeWidgetItem *t2_cme;
            QTreeWidgetItem *t2_ume;
            QTreeWidgetItem *t2_other;
            if(faculty==""){
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_pme = tier2_root(pme, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_cme = tier2_root(cme, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_ume = tier2_root(ume, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[3], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_other = tier2_root(teaching_other, Tier_2_Fields[i], Tier_2_Tot);
            }
            else{
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_pme = tier2_root(pme, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_cme = tier2_root(cme, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[2], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_ume = tier2_root(ume, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[3], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_other = tier2_root(teaching_other, Tier_2_Fields[i], Tier_2_Tot);
            }

                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

                Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_pme, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                    Tier_3_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                    tier3_root(t2_cme, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));

            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                    Tier_3_Tot=(summary->getTier3(Tier_1_Fields[2], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                    tier3_root(t2_ume, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[3], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                    Tier_3_Tot=(summary->getTier3(Tier_1_Fields[3], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                    tier3_root(t2_other, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
       }
    }

    //GRANTS
    else if (CSV_type == "Grants"){
        Tier_1_Fields = {"Grants", "Clinical Trials"};
        Tier_2_Fields = {"Peer Reviewed", "Industry Sponsored"};

        if(faculty==""){
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
            grants = root(Tier_1_Fields[0], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[1] ,start_year ,end_year ,CSV_type));
            funding = root(Tier_1_Fields[1], Tier_1_Tot);
        }
        else{
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[0] ,faculty, start_year ,end_year ,CSV_type));
            grants = root(Tier_1_Fields[0], Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[1] ,faculty, start_year ,end_year ,CSV_type));
            funding = root(Tier_1_Fields[1], Tier_1_Tot);
        }

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
            QCoreApplication::processEvents();
            count++;
            QTreeWidgetItem *t2_grants;
            QTreeWidgetItem *t2_funding;
            if(faculty==""){
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_grants = tier2_root(grants, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_funding = tier2_root(funding, Tier_2_Fields[i], Tier_2_Tot);
            }
            else{
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_grants = tier2_root(grants, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_funding = tier2_root(funding, Tier_2_Fields[i], Tier_2_Tot);
            }

            //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_grants, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                    Tier_3_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                    tier3_root(t2_funding, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
       }
    }

    //PUBLICATIONS
    else if (CSV_type == "Publications"){
        Tier_1_Fields = {"Publications"};
        Tier_2_Fields = {"Published Abstracts", "Journal Articles", "Books", "Book Chapters", "Letters to Editor"};

        if(faculty==""){
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
            pub = root(Tier_1_Fields[0], Tier_1_Tot);
        }
        else{
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[0] ,faculty ,start_year ,end_year ,CSV_type));
            pub = root(Tier_1_Fields[0], Tier_1_Tot);
        }

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
            QCoreApplication::processEvents();
            count++;
            QTreeWidgetItem *t2_pub;
            if(faculty==""){
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_pub = tier2_root(pub, Tier_2_Fields[i], Tier_2_Tot);
            }
            else{
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_pub = tier2_root(pub, Tier_2_Fields[i], Tier_2_Tot);
            }

                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

                Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_pub, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
        }
    }

    //PRESENTATIONS
    else if (CSV_type == "Presentations")
    {
        Tier_1_Fields = {"Invited Lectures", "Abstracts Presented", "Other"};

        //sets a one year range from start_year to end_year and stores each range in Tier_2_Fields
        for (int y = start_year; y <= end_year; y++){
            QCoreApplication::processEvents();
            count++;
            Tier_2_Fields.insert(y-start_year,QString::number(y));
        }

        if(faculty==""){
            count++;
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[0] ,start_year ,end_year ,CSV_type));
            invite = root("Invited Lectures", Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[1] ,start_year ,end_year ,CSV_type));
            abstract = root("Abstracts Presented", Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1(Tier_1_Fields[2] ,start_year ,end_year ,CSV_type));
            pres_other = root("Other", Tier_1_Tot);
        }
        else{
            count++;
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[0] ,faculty ,start_year ,end_year ,CSV_type));
            invite = root("Invited Lectures", Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[1] ,faculty ,start_year ,end_year ,CSV_type));
            abstract = root("Abstracts Presented", Tier_1_Tot);
            Tier_1_Tot=(summary->getTier1Filter(Tier_1_Fields[2] ,faculty ,start_year ,end_year ,CSV_type));
            pres_other = root("Other", Tier_1_Tot);
        }

            //iterate once on each Tier_2 element
        for (int i = 0; i < Tier_2_Fields.length(); i++)
        {
            QCoreApplication::processEvents();
            count++;
            QTreeWidgetItem *t2_invite;
            QTreeWidgetItem *t2_abstract;
            QTreeWidgetItem *t2_next;

            if(faculty==""){
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_invite = tier2_root(invite, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_abstract = tier2_root(abstract, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier2(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));
                t2_next = tier2_root(pres_other, Tier_2_Fields[i], Tier_2_Tot);
            }
            else{
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_invite = tier2_root(invite, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_abstract = tier2_root(abstract, Tier_2_Fields[i], Tier_2_Tot);
                Tier_2_Tot=(summary->getTier3(Tier_1_Fields[2], Tier_2_Fields[i], faculty, start_year, end_year, CSV_type));
                t2_next = tier2_root(pres_other, Tier_2_Fields[i], Tier_2_Tot);
            }

                //This function from Summary will return the names/faculties involved Tier_1_Fields[x] and Tier_2_Fields[y]

                Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[0], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                 Tier_3_Tot=(summary->getTier3(Tier_1_Fields[0], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                 tier3_root(t2_invite, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[1], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                    Tier_3_Tot=(summary->getTier3(Tier_1_Fields[1], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                    tier3_root(t2_abstract, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
            Tier_3_Fields = (summary->getFaculty(Tier_1_Fields[2], Tier_2_Fields[i], start_year, end_year, CSV_type));
            for (int j = 0; j < Tier_3_Fields.length(); j++)
            {
                QCoreApplication::processEvents();
                count++;
                if(faculty=="" || faculty==Tier_3_Fields[j]){
                    Tier_3_Tot=(summary->getTier3(Tier_1_Fields[2], Tier_2_Fields[i], Tier_3_Fields[j], start_year, end_year, CSV_type));
                    tier3_root(t2_next, Tier_3_Fields[j], Tier_3_Tot);
                }
            }
        }
    }

    //resize columns
    for(int n = 0; n < 4; n++)
    {
        count++;
        ui->treeWidget->resizeColumnToContents(n);
    }

}

//creates headings
//sets tier_1 header name and totals
QTreeWidgetItem* MainWindow::root(QString title, QVector<double> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);

    for(int x = 0; x < totals.length(); x++){
        QCoreApplication::processEvents();
        item->setText(x+2,QString::number(totals[x]));
    }
    ui->treeWidget->addTopLevelItem(item);
    return item;
}

//sets tier_2 and tier_3 header names and totals
QTreeWidgetItem* MainWindow::tier2_root(QTreeWidgetItem *parent, QString Tier_name, QVector<double> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,Tier_name);

    for(int x = 0; x < totals.length(); x++){
        QCoreApplication::processEvents();

        item->setText(x+2,QString::number(totals[x]));
    }

    parent->addChild(item);
    return item;
}
void MainWindow::tier3_root(QTreeWidgetItem *parent, QString Tier_name, QVector<double> totals)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,Tier_name);

    for(int x = 0; x < totals.length(); x++){
        QCoreApplication::processEvents();

        item->setText(x+2,QString::number(totals[x]));
    }

    parent->addChild(item);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_graph_clicked()
{
  if(ui->tabWidget->currentIndex() == 0){
   dialogWindow = new TeachingGraphDash(this);
   dialogWindow->showMaximized();
  }else if(ui->tabWidget->currentIndex() == 1){

      QDialog *pubDash = new publicationGraphDash(this);
      pubDash->showMaximized();
  }else if(ui->tabWidget->currentIndex() == 3){

      QDialog *presDash = new PresentationGraphDash(this);
      presDash->showMaximized();
  }else if(ui->tabWidget->currentIndex() == 2){

      QDialog *grantsDash = new GrantsFundingGraphDash(this);
      grantsDash->showMaximized();
  }
}


void MainWindow::browse()
{
    ProgressIndicator *progressIndicator = new ProgressIndicator();
    progressIndicator->show();

    file_path = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("(*.csv)"));
    if (file_path  != NULL){
    string filePathSt = file_path.toStdString();

    progressIndicator->raise();
    progressIndicator->activateWindow();


    string tableName = db->csvIntoDb(filePathSt);
    if(pme != NULL)
    {
    pme->setHidden(true);
    cme->setHidden(true);
    ume->setHidden(true);
    teaching_other->setHidden(true);
    }

    //Funding
    if(grants != NULL)
    {
    grants->setHidden(true);
    funding->setHidden(true);
    }

    //publications
    if(pub != NULL)
    {
    pub->setHidden(true);
    }

    //presentations
    if(invite != NULL)
    {
    invite->setHidden(true);
    abstract->setHidden(true);
    pres_other->setHidden(true);
    }
    progressIndicator->close();

    if (tableName == "Teaching")
    {
        ui->tabWidget->setCurrentIndex(0);
        tab_focus = "Teaching";
        ui->main_window_label->setText("Teaching");

        makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Teaching");
    }
    else if (tableName == "Publications")
    {
        ui->tabWidget->setCurrentIndex(1);
        tab_focus = "Publications";
        ui->main_window_label->setText("Publications");
        makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Publications");
    }
    else if (tableName == "Grants")
    {
        ui->tabWidget->setCurrentIndex(2);
        tab_focus = "Grants";
        ui->main_window_label->setText("Funding");
        makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Grants");
    }
    else if (tableName == "Presentations")
    {
        ui->tabWidget->setCurrentIndex(3);
        tab_focus = "Presentations";
        ui->main_window_label->setText("Presentations");
        makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Presentations");
    }
    QString table = QString::fromStdString(tableName);


    QString tableFilter = "";
    if (tableName == "Teaching"){
        tableFilter = "(MemberName='' or PrimaryDomain='' or StartDate='' or EndDate='' or Program='' or TypeofCourseActivity='' or CourseActivity='' or GeographicalScope='' or HoursperTeachingSessionorWeek='' or NumberofTeachingSessionsorWeeks='' or TotalHours='')";
    }
    else if (tableName == "Grants"){
        tableFilter = "(MemberName='' or PrimaryDomain='' or StartDate='' or EndDate='' or FundingType='' or Status=''or PeerReviewed='' or IndustryGrant='' or Role='' or Title='' or PrincipalInvestigator='' or CoInvestigators='' or TotalAmount='')";
    }
    else if (tableName == "Presentations"){
        tableFilter = "(MemberName='' or PrimaryDomain='' or Date='' or Type='' or Role='' or Title='')";
    }
    else if (tableName == "Publications"){
        tableFilter = "(MemberName='' or PrimaryDomain='' or PublicationStatus='' or Type='' or StatusDate='' or Role='' or JournalNamePublishedInBookTitleetc='' or Authors='' or Title='')";
    }




    dialogForError = new DialogForError(table,tableFilter);

    dialogForError->show();
    dialogForError->raise();
    dialogForError->activateWindow();

    // default date filter range
    ui->comboBox_start->setCurrentIndex(0);
    ui->comboBox_end->setCurrentIndex(ui->comboBox_end->count()-1);  // sets to last year in box
    }

}



void MainWindow::on_actionAbout_Canteloupe_triggered()
{
    canteHelp = new About_Canteloupe(this);
    canteHelp -> show();
}


//creates headings
QTreeWidgetItem* MainWindow::root2(QString title, QString totalHours, QString totalStudents)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0,title);
    item->setText(2,totalHours);
    item->setText(3,totalStudents);
    ui->treeWidget->addTopLevelItem(item);
    return item;
}



void MainWindow::makeEmptyTree(){
    ui->treeWidget->clear();
    //Set tree widget table headers
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->headerItem()->setText(0,"");
    ui->treeWidget->headerItem()->setText(1,"Academic Year");
    ui->treeWidget->headerItem()->setText(2,"Hours");
    ui->treeWidget->headerItem()->setText(3,"Students");

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    //build headers
    QTreeWidgetItem *pme = root2("PME", "0", "0");
    pme->addChild(item);
    QTreeWidgetItem *ume = root2("UME", "0","0");
    QTreeWidgetItem *item2 = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    ume->addChild(item2);
    QTreeWidgetItem *cme = root2("CME", "0", "0");
    QTreeWidgetItem *item3 = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    cme->addChild(item3);
    QTreeWidgetItem *other = root2("Other", "0", "0");
    QTreeWidgetItem *item4 = new QTreeWidgetItem();
    item->setText(1,"0");
    item->setText(2,"0");
    item->setText(3,"0");
    other->addChild(item4);

    //hide tree
    pme->setHidden(true);
    cme->setHidden(true);
    ume->setHidden(true);
    other->setHidden(true);

    //generate date ranges
        for (int x = 1975; x <= 2015; x ++)
        {
            ui->comboBox_start->addItem(QString::number(x));
            ui->comboBox_end->addItem(QString::number(x));
        }
    // set default date range
        ui->comboBox_start->setCurrentIndex(0);
        ui->comboBox_end->setCurrentIndex(ui->comboBox_end->count()-1);

}

//print
void MainWindow::on_button_display_clicked()
{
    QString tableName = QString::fromStdString(tab_focus);
    table = new TeachingTable(tableName,"");
    table->showMaximized();
}

//tabs
void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    switch(index)
    {
    case 0:
        ui->main_window_label->setText("Teaching");

         //teaching
        if(pme != NULL)
        {
        pme->setHidden(false);
        cme->setHidden(false);
        ume->setHidden(false);
        teaching_other->setHidden(false);
        }

        //Funding
        if(grants != NULL)
        {
        grants->setHidden(true);
        funding->setHidden(true);
        }

        //publications
        if(pub != NULL)
        {
        pub->setHidden(true);
        }

        //presentations
        if(invite != NULL)
        {
        invite->setHidden(true);
        abstract->setHidden(true);
        pres_other->setHidden(true);
        }

        break;
    case 1:
        ui->main_window_label->setText("Publications");
        if(pme != NULL)
        {
        pme->setHidden(true);
        cme->setHidden(true);
        ume->setHidden(true);
        teaching_other->setHidden(true);
        }

        //Funding
        if(grants != NULL)
        {
        grants->setHidden(true);
        funding->setHidden(true);
        }

        //publications
        if(pub != NULL)
        {
        pub->setHidden(false);
        }

        //presentations
        if(invite != NULL)
        {
        invite->setHidden(true);
        abstract->setHidden(true);
        pres_other->setHidden(true);
        }

        break;
    case 2:
        ui->main_window_label->setText("Funding");

        if(pme != NULL)
        {
        pme->setHidden(true);
        cme->setHidden(true);
        ume->setHidden(true);
        teaching_other->setHidden(true);
        }

        //Funding
        if(grants != NULL)
        {
        grants->setHidden(false);
        funding->setHidden(false);
        }

        //publications
        if(pub != NULL)
        {
        pub->setHidden(true);
        }

        //presentations
        if(invite != NULL)
        {
        invite->setHidden(true);
        abstract->setHidden(true);
        pres_other->setHidden(true);
        }

        break;
    case 3:
        ui->main_window_label->setText("Presentations");
        if(pme != NULL)
        {
        pme->setHidden(true);
        cme->setHidden(true);
        ume->setHidden(true);
        teaching_other->setHidden(true);
        }

        //Funding
        if(grants != NULL)
        {
        grants->setHidden(true);
        funding->setHidden(true);
        }

        //publications
        if(pub != NULL)
        {
        pub->setHidden(true);
        }

        //presentations
        if(invite != NULL)
        {
        invite->setHidden(false);
        abstract->setHidden(false);
        pres_other->setHidden(false);
        }
        break;
    default:
        break;
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    browse();
}

void MainWindow::on_actionReport_Bugs_triggered()
{
    bug = new Bug_Report(this);
    bug -> show();
}

void MainWindow::on_actionTechnical_Support_triggered()
{
    tech = new Tech_Support(this);
    tech -> show();
}

void MainWindow::on_actionContext_Help_triggered()
{
    QDesktopServices::openUrl(QUrl("http://canteloupe.s3-website-us-east-1.amazonaws.com/help.html", QUrl::TolerantMode));
}

void MainWindow::print()
{

    QPrinter printer;
    QPainter painter;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print  Document");
    if (dialog->exec() != QDialog::Accepted)
        return;
    painter.begin(&printer);
    ui->treeWidget->expandAll();
    ui->treeWidget->render(&painter);
    ui->treeWidget->collapseAll();
    painter.end();
}


void MainWindow::on_button_refresh_clicked()
{
    if(pme != NULL)
    {
    pme->setHidden(true);
    cme->setHidden(true);
    ume->setHidden(true);
    teaching_other->setHidden(true);
    }

    //Funding
    if(grants != NULL)
    {
    grants->setHidden(true);
    funding->setHidden(true);
    }

    //publications
    if(pub != NULL)
    {
    pub->setHidden(true);
    }

    //presentations
    if(invite != NULL)
    {
    invite->setHidden(true);
    abstract->setHidden(true);
    pres_other->setHidden(true);
    }
   switch(ui->tabWidget->currentIndex())
   {
   case 0:
      makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Teaching");
       break;
   case 1:
      makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Publications");
       break;
   case 2:
      makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Grants");
       break;
   case 3:
      makeTree(ui->comboBox_start->currentText().toInt(),ui->comboBox_end->currentText().toInt(), "Presentations");
       break;
   default:
       break;
   }
}

void MainWindow::on_actionPrint_triggered()
{

    QPrinter printer;
    //QDir::homePath() + QDir::separator() + name
    //printer.setOutputFileName(QDir::homePath() + QDir::separator() + testprint");
    QPainter painter;
    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print  Document");
    if (dialog->exec() != QDialog::Accepted)
        return;
    painter.begin(&printer);
    ui->treeWidget->expandAll();
    //ui->treeWidget->size(100, 100);
    //ui->treeWidget->adjustSize();
    ui->treeWidget->render(&painter);
    ui->treeWidget->collapseAll();
    painter.end();
}

void MainWindow::autoComplete()
{

    //Autocomplete based on what tab is open

    QStringList *list = new QStringList();
    QString table;

    if(ui->tabWidget->currentIndex() == 0){
     table = "Teaching";
    }else if(ui->tabWidget->currentIndex() == 1){

       table = "Publications";
    }else if(ui->tabWidget->currentIndex() == 3){

       table = "Presentations";
    }else if(ui->tabWidget->currentIndex() == 2){

        table = "Grants";
    }


    QSqlDatabase sqlDatabase = QSqlDatabase::database("db_connection");                 // new database connection created
    sqlDatabase.open();
    QSqlQuery qry(sqlDatabase);



    qry.prepare("SELECT DISTINCT MemberName FROM " + table);
    qry.exec();

    while(qry.next()){
    QString name = QString(qry.record().value(0).toString());
    *list  << name;
    }

    QCompleter* completer = new QCompleter(*list);
    ui->lineEdit->setCompleter(completer);
}

void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    autoComplete();
}
