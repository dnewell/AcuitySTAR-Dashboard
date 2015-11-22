#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QtSql/QtSql>
#include <QDebug>
#include <iostream>
#include "summary.h"
#include "QDebug"
using namespace std;




QVector<Year> Summary::summaryFill(QString program, int start, int end){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");  //without all the QDir stuff, will only look in current working directory
    qDebug()<<(QDir::homePath() + QDir::separator() + "database.sqlite");
    db.open();
    QSqlQuery qry(db);


    QVector<Year> years;
    QString qstr;
    for(int yearcount=start; yearcount<=end; yearcount++){
        Year curyear (yearcount,0,0);
        qstr=QString::number(yearcount);

        if(program.compare("Other")!=0){
                    qry.prepare("SELECT Faculty, HoursperTeachingSessionorWeek, NumberOfTrainees FROM Teaching WHERE StartDate LIKE '"+qstr+"%' AND Program = '"+program+"'");
                    qry.exec();
                    qDebug()<<(qry.lastQuery());
                }
                else{
                    qry.prepare("SELECT Faculty, HoursperTeachingSessionorWeek, NumberOfTrainees FROM Teaching WHERE StartDate LIKE '"+qstr+"%' AND Program NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')");
                    qry.exec();
                }
        if(qry.next()){

            curyear.list.append(Entry(qry.value(0).toString(), qry.value(1).toDouble(), qry.value(2).toInt()));
            curyear.tothours+=qry.value(1).toDouble();
            curyear.totstudents+=qry.value(2).toInt();
            for(int n=0; qry.next(); n++){
                int exist=0;
                int index;
                for(int i=0; i<curyear.list.size(); i++){
                    if(curyear.list[i].faculty.QString::compare(qry.value(0).toString())==0){
                        exist=1;
                        index=i;
                    }
                }

                if(exist==1){
                    curyear.list[index].hours+=qry.value(1).toDouble();
                    //cout<<qry.value(1).toInt()<<endl;
                    //cout<<curyear.list[index].hours<<endl;
                    curyear.list[index].students+=qry.value(2).toInt();
                }
                else{
                    curyear.list.append(Entry(qry.value(0).toString(), qry.value(1).toDouble(), qry.value(2).toInt()));
                }
                curyear.tothours+=qry.value(1).toDouble();
                curyear.totstudents+=qry.value(2).toInt();
            }
        }
        years.append(curyear);
    }
    db.close();
    return years;
}


QVector<QString> Summary::getFaculty(QString tier1, QString tier2, int startDate, int endDate, QString csvtype){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");
    db.open();
    QSqlQuery qry(db);
    QVector<QString> facultys;
    QString field, source;

    if(csvtype=="Teaching"){
        field="Program";
        startDate=tier2.toInt();
        endDate=tier2.toInt();
        if(tier1=="PME") tier1="Postgraduate Medical Education";
        else if(tier1=="CME") tier1="Continuing Medical Education";
        else if(tier1=="UME") tier1="Undergraduate Medical Education";
    }
    else if(csvtype=="Presentations"){
        field="Type";
        startDate=tier2.toInt();
        endDate=tier2.toInt();
    }
    else if(csvtype=="Publications"){
        field="Type";
        tier1=tier2;
    }
    else if(csvtype=="Grants"){
        field="FundingType";
        if(tier2=="Peer Reviewed")
            source="PeerReviewed?";
        else if(tier2=="Industry Sponsored")
            source="IndustryGrant?";
    }

    if (tier1 == "Other" && csvtype == "Teaching"){
        tier1 = "NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')";
    }
    else if (tier1 == "Other" && csvtype == "Presentations"){
        tier1 = "NOT IN ('Invited Lectures', 'Abstracts Presented')";
    }
    else{
        tier1  = "= '" + tier1 + "'";
    }
    QString q = "SELECT DISTINCT MemberName FROM " + csvtype + " WHERE (";
    for( int a = startDate; a < endDate; a = a + 1 )
    {
        QString qstr=QString::number(a);
        q = q + " StartDate LIKE '" + qstr + "%' OR ";
    }
    QString qstr1=QString::number(endDate);
    if(csvtype=="Grants"){
        q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1 + " AND " + source + " = 'TRUE'";
    }
    else{
        q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1;
    }
    cout<<q.toStdString()<<endl;
    qry.prepare(q);
    qry.exec();
    if(qry.next()){
        facultys.append(qry.value(0).toString());
    }
    db.close();
    return facultys;
}


QVector<double> Summary::getTier3(QString tier1, QString tier2, QString tier3, int startDate, int endDate, QString csvtype){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");
    db.open();
    QSqlQuery qry(db);
    QVector<double> facultys;
    QString field, source, data;

    if(csvtype=="Teaching"){
        field="Program";
        startDate=tier2.toInt();
        endDate=tier2.toInt();
        data="SUM(TotalHours), SUM(NumberOfTrainees)";
        if(tier1=="PME") tier1="Postgraduate Medical Education";
        else if(tier1=="CME") tier1="Continuing Medical Education";
        else if(tier1=="UME") tier1="Undergraduate Medical Education";
    }
    else if(csvtype=="Presentations"){
        field="Type";
        startDate=tier2.toInt();
        endDate=tier2.toInt();
        data="COUNT(*)";
    }
    else if(csvtype=="Publications"){
        field="Type";
        if(tier2 == "Published Abstracts") tier2="Published Abstract";
        else if(tier2 == "Journal Articles") tier2="Journal Article";
        tier1=tier2;
        data="COUNT(*)";
    }
    else if(csvtype=="Grants"){
        field="FundingType";
        if(tier2=="Peer Reviewed")
            source="PeerReviewed?";
        else if(tier2=="Industry Sponsored")
            source="IndustryGrant?";
        data="COUNT(*), SUM(TotalAmount)";
    }

    if (tier1 == "Other" && csvtype == "Teaching"){
        tier1 = "NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')";
    }
    else if (tier1 == "Other" && csvtype == "Presentations"){
        tier1 = "NOT IN ('Invited Lectures', 'Abstracts Presented')";
    }
    else{
        tier1  = "= '" + tier1 + "'";
    }
    QString q = "SELECT "+data+" FROM "+csvtype+" WHERE (";
    for( int a = startDate; a < endDate; a = a + 1 )
    {
        QString qstr=QString::number(a);
        q = q + " StartDate LIKE '" + qstr + "%' OR ";
    }
    QString qstr1=QString::number(endDate);
    if(csvtype=="Grants"){
        q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1 + " AND " + source + " = 'TRUE' AND MemberName = " + tier3;
    }
    else{
        q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1 + " AND MemberName = " + tier3;
    }
    cout<<q.toStdString()<<endl;
    qry.prepare(q);
    qry.exec();
    if(qry.next()){
        facultys.append(qry.value(0).toDouble());
    }
    db.close();
    return facultys;
}


QVector<double> Summary::getTier2(QString tier1, QString tier2, int startDate, int endDate, QString csvtype){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");
    db.open();
    QSqlQuery qry(db);
    QVector<double> facultys;
    QString field, source, data;

    if(csvtype=="Teaching"){
        field="Program";
        startDate=tier2.toInt();
        endDate=tier2.toInt();
        data="SUM(TotalHours), SUM(NumberOfTrainees)";
        if(tier1=="PME") tier1="Postgraduate Medical Education";
        else if(tier1=="CME") tier1="Continuing Medical Education";
        else if(tier1=="UME") tier1="Undergraduate Medical Education";
    }
    else if(csvtype=="Presentations"){
        field="Type";
        startDate=tier2.toInt();
        endDate=tier2.toInt();
        data="COUNT(*)";
    }
    else if(csvtype=="Publications"){
        field="Type";
        if(tier2 == "Published Abstracts") tier2="Published Abstract";
        else if(tier2 == "Journal Articles") tier2="Journal Article";
        tier1=tier2;
        data="COUNT(*)";
    }
    else if(csvtype=="Grants"){
        field="FundingType";
        if(tier2=="Peer Reviewed")
            source="PeerReviewed?";
        else if(tier2=="Industry Sponsored")
            source="IndustryGrant?";
        data="COUNT(*), SUM(TotalAmount)";
    }

    if (tier1 == "Other" && csvtype == "Teaching"){
        tier1 = "NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')";
    }
    else if (tier1 == "Other" && csvtype == "Presentations"){
        tier1 = "NOT IN ('Invited Lectures', 'Abstracts Presented')";
    }
    else{
        tier1  = "= '" + tier1 + "'";
    }
    QString q = "SELECT "+data+" FROM "+csvtype+" WHERE (";
    for( int a = startDate; a < endDate; a = a + 1 )
    {
        QString qstr=QString::number(a);
        q = q + " StartDate LIKE '" + qstr + "%' OR ";
    }
    QString qstr1=QString::number(endDate);
    if(csvtype=="Grants"){
        q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1 + " AND " + source + " = 'TRUE'";
    }
    else{
        q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1;
    }
    cout<<q.toStdString()<<endl;
    qry.prepare(q);
    qry.exec();
    if(qry.next()){
        facultys.append(qry.value(0).toDouble());
    }
    db.close();
    return facultys;
}


QVector<double> Summary::getTier1(QString tier1, int startDate, int endDate, QString csvtype){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");
    db.open();
    QSqlQuery qry(db);
    QVector<double> facultys;
    QString field, data;

    if(csvtype=="Teaching"){
        field="Program";
        data="SUM(TotalHours), SUM(NumberOfTrainees)";
        if(tier1=="PME") tier1="Postgraduate Medical Education";
        else if(tier1=="CME") tier1="Continuing Medical Education";
        else if(tier1=="UME") tier1="Undergraduate Medical Education";
    }
    else if(csvtype=="Presentations"){
        field="Type";
        data="COUNT(*)";
    }
    else if(csvtype=="Publications"){
        field="Type";
        data="COUNT(*)";
    }
    else if(csvtype=="Grants"){
        field="FundingType";
        data="COUNT(*), SUM(TotalAmount)";
    }

    if (tier1 == "Other" && csvtype == "Teaching"){
        tier1 = "NOT IN ('Postgraduate Medical Education', 'Continuing Medical Education', 'Undergraduate Medical Education')";
    }
    else if (tier1 == "Other" && csvtype == "Presentations"){
        tier1 = "NOT IN ('Invited Lectures', 'Abstracts Presented')";
    }
    else if (csvtype == "Publications"){
        tier1 = "IN ('Journal Article', 'Published Abstract', 'Books', 'Book Chapters', 'Letters to Editor')";
    }
    else{
        tier1  = "= '" + tier1 + "'";
    }
    QString q = "SELECT "+data+" FROM "+csvtype+" WHERE (";
    for( int a = startDate; a < endDate; a = a + 1 )
    {
        QString qstr=QString::number(a);
        q = q + " StartDate LIKE '" + qstr + "%' OR ";
    }
    QString qstr1=QString::number(endDate);
    q = q + " StartDate LIKE '" + qstr1 + "%' ) AND " + field + " " + tier1;
    cout<<q.toStdString()<<endl;
    qry.prepare(q);
    qry.exec();
    if(qry.next()){
        facultys.append(qry.value(0).toDouble());
    }
    db.close();
    return facultys;
}
