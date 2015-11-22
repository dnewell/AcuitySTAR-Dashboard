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
#include <list>
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
 * TO DO: modularize.
 * @brief DB::createDatabase
 */

void DB::createDatabase(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "db_connection");
    QString name = "database.sqlite";

    db.setDatabaseName(QDir::homePath() + QDir::separator() + name);

    db.open();

}

/**
 * This method reads from the a teaching file, parses each line into tokens, and
 * then inserts those lines into the database.
 *
 * For details on how the tokenizer functor is working,
 * see: http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/escaped_list_separator.htm
 *
 * TO DO: modularize.
 *
 *  @brief DB::parseCSV
 */
string DB::teachingCsvIntoDb(string fullPathToFile){
    string currentLine      = "";
    string headings         = "";
    string builtValueQuery  = "";
    string builtHeaderQuery = "";
    string finalQuery       = "";
    QString qstr            = "";
    list<string> headingList;

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

// Tokenizes the headings of the CSV file
    tokenizer<escaped_list_separator<char> > tok(headings);                     // parse heading line token by token


    for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
    {

        string currentItem = *beg;

        // remove all white space in current heading, effectively converting to camelcase.

        for(int i=0; i< currentItem.length(); i++)
        {
            if(currentItem[i] == ' ') currentItem.erase(i,1);      // Change to ...currentItem.replace(i,1,"_"), to replace all whitespace with underscores
        }

        // remove all non alphanumeric characters - not doing may result in malformed SQL queries

        currentItem.erase( std::remove_if( currentItem.begin(), currentItem.end(), []( char c ) { return !std::isalnum(c) ; } ), currentItem.end() ) ;

        builtHeaderQuery = builtHeaderQuery + currentItem + " TEXT, ";

        headingList.push_back(currentItem);
    }
    builtHeaderQuery = builtHeaderQuery.substr(0, builtHeaderQuery.length()-2);

    // Creates new table with the appropriate name

    string tableName = getTypeFromHeadingList(headingList.size());
    // drop table if it already exists, then insert new table
    finalQuery = "DROP TABLE " + tableName + ";";
    qstr = QString::fromStdString(finalQuery);
    query.exec(qstr);
    // create new table, with name to match type of csv
    finalQuery = "CREATE TABLE " + tableName + "(" + builtHeaderQuery + ");";
    qstr = QString::fromStdString(finalQuery);
    query.exec(qstr);


    while (getline(inputfile, currentLine))                                             // process the remaining rows line by line
    {
        finalQuery = "";
        builtValueQuery = "";

        tokenizer<escaped_list_separator<char> > tok(currentLine);                      // give boost tokenizer the currentline
        for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
           builtValueQuery = builtValueQuery + " '" + (string)*beg + "',";
        }

        builtValueQuery = builtValueQuery.substr(0, builtValueQuery.length()-1) +" ";
        string tableName = getTypeFromHeadingList(headingList.size());                  // decides the type of CSV file from the number of the headings, names table appropriately
        finalQuery = "INSERT INTO " + tableName + " VALUES(" + builtValueQuery + ")";   // builds the query from the 28 values in a single row

        qstr = QString::fromStdString(finalQuery);                                      // cast to QString

        query.exec(qstr);                                                               // executes the database query, inserting one row into the table
    }
    return tableName;
}

/**
 * This helper function decides from an integer representing the number of elements in a std::list containing
 * heading names which type of CSV file the headings correspond to.
 * @brief getTypeFromHeadingList
 * @return string with type of csv file (i.e. the SQL table name)
 */
string DB::getTypeFromHeadingList(int numHeadings){
    if (numHeadings == 28){
        return "Teaching";
    }
    if (numHeadings == 38){
        return "Grants";
    }
    if (numHeadings == 30){
        return "Presentations";
    }
    if (numHeadings == 44){
        return "Publications";
    }
    return "Unexpected CSV type";
}



