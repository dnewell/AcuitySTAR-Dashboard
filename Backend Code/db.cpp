////*********START**********  This is the required code to open and query the database.  Add up top: #include <QtSql/QtSql>
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(QDir::homePath() + QDir::separator() + "database.sqlite");  //without all the QDir stuff, will only look in current working directory
//    db.open();
//    QSqlQuery query(db);
//    query.exec("SELECT* etc etc");        // actually executes the query. N.B. all queries must be of type QString, use: newQString = goodQString::fromStdString(badStdString);
//    db.close();
////*********END************
// Check out the following site for how to format different queries / deal with return values
// http://sysmagazine.com/posts/128836/
/**
 * DB class handles the SQLite database guts: intial creation/naming,
 * parsing a CSV file, and inserting the tokenized data into the database
 *
 * TO DO:
 * Refactor, moving the CSV parser/tokenizer into another class
 *
 * Author: David Newell
 **/

#include "db.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QtSql/QtSql>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

DB::DB()
{

}


/**
 * This method creates a new SQLite 3 database, sets the attributes,
 * and calls the parseCSV method.
 *
 * TO DO: modularize. move the CSV parsing logic into another class
 * @brief DB::createDatabase
 */

void DB::createDatabase(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "db_connection");
    QString name = "database.sqlite";

    db.setDatabaseName(QDir::homePath() + QDir::separator() + name);

    db.open();

    QSqlQuery query(db);
    query.exec("CREATE TABLE TEACHING(RECORDINFO TEXT,  LASTMODIFIEDUSER TEXT,  LASTMODIFIEDDATE TEXT,  ID TEXT PRIMARY KEY, "
               "MEMBERNAME TEXT,  PRIMARYDOMAIN TEXT,  STARTDATE TEXT,  ENDDATE TEXT,  PROGRAM TEXT,  ACTIVITYTYPE TEXT,  "
               "ACTIVITY TEXT,  GEOGRAPHICALSCOPE TEXT, INSTITUTION TEXT, FACULTY TEXT,  DEPARTMENT TEXT,  DIVISION TEXT,  "
               "LOCATION TEXT,  HOURSPERTEACHINGSESSIONORWEEKS TEXT,  NUMBEROFTEACHINGSESSIONSORWEEKS TEXT,  "
               "FACULTYMEMBERADDITIONALCOMMENTS TEXT,  NUMBEROFTRAINEES TEXT,  STUDENTNAMEORNAMES TEXT,  INITIALLECTURE TEXT,  "
               "FACULTYDEVELOPMENT TEXT,  STIPENDRECEIVED TEXT,  COMMENT TEXT, OTHERDETAILS TEXT,  TOTALHOURS TEXT)  ");

    parseCSV("C:/Users/David/Desktop/DatabaseCore/Teaching_sample.csv");

}

/**
 * This method reads from the a teaching file, parses each line into tokens, and
 * then inserts those lines into the database.
 *
 * It's chock full of magic, so be delicate!
 *
 * For details on how the tokenizer functor is working,
 * see: http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/escaped_list_separator.htm
 *
 * TO DO: modularize.  make somewhat less cryptic.
 *
 *  @brief DB::parseCSV
 */
void DB::parseCSV(string fullPathToFile){
    string currentLine      = "";
    string headings         = "";
    string builtValueQuery  = "";
    string finalQuery       = "";
    QString qstr            = "";
    //    QSqlDatabase sqlDatabase;
    //    QSqlQuery query;
    int numberOfRows           = 0;

    // database driver guts

    QSqlDatabase sqlDatabase = QSqlDatabase::database("db_connection");

       QSqlQuery query(sqlDatabase);


    // open input file stream
    ifstream inputfile(fullPathToFile);

    // deal with first line of CSV, which contains the headings
    getline(inputfile, headings);                                               // get first line of csv file, which contains the column headers

    tokenizer<escaped_list_separator<char> > tok(headings);                     // parse heading line token by token
    for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
    {   //cout << "*****HEADINGS*****" << endl;
       // cout << *beg << "\n";
    }
       // cout << "*****LINES*****" << endl;

    while (getline(inputfile, currentLine))                                     // process the remaining rows line by line
    {
        builtValueQuery = "";
        numberOfRows++;

        tokenizer<escaped_list_separator<char> > tok(currentLine);              // give boost tokenizer the currentline
        for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
           builtValueQuery = builtValueQuery + "'" + (string)*beg + "',";
        }

        finalQuery = "INSERT INTO TEACHING VALUES(" + builtValueQuery + ")";    // builds the query from the 28 values in a single row

        builtValueQuery = builtValueQuery.substr(0, builtValueQuery.length()-1);

        cout << " ****begin query:" + finalQuery << endl;


        qstr = QString::fromStdString(finalQuery);                              // cast to QString

        // executes the database query, inserting one row
        query.exec(qstr);
    }
    cout << finalQuery;
}
