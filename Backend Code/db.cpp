////*********  This is the code necessary to open and query the database.  Add up top: #include <QtSql/QtSql>
//    QSqlDatabase sqlDatabase = QSqlDatabase::database("db_connection");
//    QSqlQuery query(sqlDatabase);
//
//    query.prepare(sql_query);     // N.B. all queries must be of type QString, use: newQString = goodQString::fromStdString(badStdString);
//    query.exec();                 // actually executes the query.
////*********

/**
 * DB class handles the SQLite database guts: intial creation/naming,
 * parsing a CSV file, and inserting the tokenized data into the database
 *
 * TO DO:
 * Refactor. Perhaps move the CSV parser/tokenizer into another class?
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
 * This method creates a new SQLite 3 database and sets the attributes (column/heading names)
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
    query.exec("CREATE TABLE TEACHING(RECORDINFO TEXT,  LASTMODIFIEDUSER TEXT,  LASTMODIFIEDDATE TEXT,  ID TEXT, "
               "MEMBERNAME TEXT,  PRIMARYDOMAIN TEXT,  STARTDATE TEXT,  ENDDATE TEXT,  PROGRAM TEXT,  ACTIVITYTYPE TEXT,  "
               "ACTIVITY TEXT,  GEOGRAPHICALSCOPE TEXT, INSTITUTION TEXT, FACULTY TEXT,  DEPARTMENT TEXT,  DIVISION TEXT,  "
               "LOCATION TEXT,  HOURSPERTEACHINGSESSIONORWEEKS TEXT,  NUMBEROFTEACHINGSESSIONSORWEEKS TEXT,  "
               "FACULTYMEMBERADDITIONALCOMMENTS TEXT,  NUMBEROFTRAINEES TEXT,  STUDENTNAMEORNAMES TEXT,  INITIALLECTURE TEXT,  "
               "FACULTYDEVELOPMENT TEXT,  STIPENDRECEIVED TEXT,  COMMENT TEXT, OTHERDETAILS TEXT,  TOTALHOURS TEXT)  ");

}

/**
 * This method reads from the a teaching file, parses each line into tokens, and
 * then inserts those lines into the database.
 *
 * For details on how the tokenizer functor is working,
 * see: http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/escaped_list_separator.htm
 *
 * TO DO: modularize.  make somewhat less cryptic.
 *
 *  @brief DB::parseCSV
 */
void DB::teachingCsvIntoDb(string fullPathToFile){
    string currentLine      = "";
    string headings         = "";
    string builtValueQuery  = "";
    string finalQuery       = "";
    QString qstr            = "";

    // database driver guts

    QSqlDatabase sqlDatabase = QSqlDatabase::database("db_connection");
    QSqlQuery query(sqlDatabase);

    // open input file stream
    ifstream inputfile(fullPathToFile);
    if(!inputfile.is_open()){
        cout << "Error: the CSV file cannot be found. Check the path and filename." << endl;
        system("exit");
    }

    // deal with first line of CSV, which contains the headings
    getline(inputfile, headings);                                               // get first line of csv file, which contains the column headers

//// This code tokenizes the headings of the CSV file: it's only needed if we want to autopopulate the headings of the SQL table down the road
//    tokenizer<escaped_list_separator<char> > tok(headings);                     // parse heading line token by token
//    for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
//    {   //cout << "*****HEADINGS*****" << endl;
//        //cout << *beg << "\n";
//    }
//       // cout << "*****LINES*****" << endl;

    while (getline(inputfile, currentLine))                                     // process the remaining rows line by line
    {
        builtValueQuery = "";

        tokenizer<escaped_list_separator<char> > tok(currentLine);              // give boost tokenizer the currentline
        for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
           builtValueQuery = builtValueQuery + " '" + (string)*beg + "',";
        }

        builtValueQuery = builtValueQuery.substr(0, builtValueQuery.length()-1) +" ";
        finalQuery = "INSERT INTO TEACHING VALUES(" + builtValueQuery + ")";    // builds the query from the 28 values in a single row

        qstr = QString::fromStdString(finalQuery);                              // cast to QString

        query.exec(qstr);                                                       // executes the database query, inserting one row into the table
    }
}
