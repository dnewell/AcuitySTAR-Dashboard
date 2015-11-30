/**
 * OpenCSV class handles all function related to the opening of a CSV file and it's insertion
 * into the SQLite3 database instance.
 * Parsing/tokenizing uses the Boost tokenizer library,
 * and the associated escaped_list_separator functor.
 *
 * See:
 * http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/
 * http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/escaped_list_separator.htm
 *
 * Author: David Newell
 **/

#include "opencsv.h"
#include <string>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <QtSql/QtSql>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

OpenCSV::OpenCSV()
{

}

/**
 * This method reads from the a CSV file, parses each line into tokens, and
 * then inserts those lines into the database.
 *
 * For details on how the tokenizer functor is working,
 * see: http://www.boost.org/doc/libs/1_42_0/libs/tokenizer/escaped_list_separator.htm
 */
string OpenCSV::csvIntoDb(string fullPathToFile){
    string currentLine      = "";
    string headings         = "";
    string builtValueQuery  = "";
    string builtHeaderQuery = "";
    string finalQuery       = "";
    QString qstr            = "";
    list<string> headingList;



    QSqlDatabase sqlDatabase = QSqlDatabase::database("db_connection");                 // database driver guts
    QSqlQuery query(sqlDatabase);


    ifstream inputfile(fullPathToFile);                                                 // open input file stream and handle file not found error
    if(!inputfile.is_open()){
        cout << "Error: the CSV file cannot be found. Check the path and filename." << endl;
        system("exit");
    }

    getline(inputfile, headings);                                                        // get first line of csv file, which contains the column headers

    tokenizer<escaped_list_separator<char> > tok(headings);                              // parse heading line token by token

    for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg)
    {
        string currentItem = *beg;

        for(int i=0; i< currentItem.length(); i++)                                      // remove all white space in current heading, effectively converting to camelcase.
        {
            if(currentItem[i] == ' ') currentItem.erase(i,1);                           // Change to ...currentItem.replace(i,1,"_"), to replace all whitespace with underscores
        }

        currentItem.erase( std::remove_if( currentItem.begin(), currentItem.end(),      // remove all non alphanumeric characters - not doing may result in malformed SQL queries
                                           []( char c ) { return !std::isalnum(c) ; } ), currentItem.end() ) ;

        builtHeaderQuery = builtHeaderQuery + currentItem + " TEXT, ";
        headingList.push_back(currentItem);
    }
    builtHeaderQuery = builtHeaderQuery.substr(0, builtHeaderQuery.length()-2);

    string tableName = getTypeFromHeadingList(headingList.size());                      // creates new table with the appropriate name

    finalQuery = "DROP TABLE " + tableName + ";";                                       // drop table if it already exists, then insert new table

    qstr = QString::fromStdString(finalQuery);
    query.exec(qstr);


    finalQuery = "CREATE TABLE " + tableName + "(" + builtHeaderQuery + ");";           // create new table, with name to match type of csv (Teaching, Grants, etc)
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

        builtValueQuery  = builtValueQuery.substr(0, builtValueQuery.length()-1) +" ";
        string tableName = getTypeFromHeadingList(headingList.size());                  // decides the type of CSV file from the number of the headings, names table appropriately
        finalQuery = "INSERT INTO " + tableName + " VALUES(" + builtValueQuery + ")";   // builds the query from the 28 values in a single row

        qstr = QString::fromStdString(finalQuery);                                      // cast to QString

        query.exec(qstr);                                                               // executes the database query, inserting one row into the table
    }
    if (tableName == "Grants"){
        qstr = QString::fromStdString("UPDATE GRANTS SET TotalAmount= Replace(replace(TotalAmount, '$', ''), ',', '');");
        query.exec(qstr);
    }
    return tableName;
}

/**
 * This helper function decides from an integer representing the number of elements in a std::list containing
 * heading names which type of CSV file the headings correspond to.
 *
 * The multiple conditions in the if statements handle the possibility of a column being added or removed,
 * it is a hack, however, and could break if a Presentations CSV has only 29 headings, for example.
 * The alternative is much more complicated, though, and this should work for our purposes.
 *
 * @return string with type of csv file (i.e. the SQL table name)
 */
string OpenCSV::getTypeFromHeadingList(int numHeadings){
    if (numHeadings == 28 || numHeadings == 29){
        return "Teaching";
    }
    if (numHeadings == 37 || numHeadings == 38 || numHeadings == 39){
        return "Grants";
    }
    if (numHeadings == 30 || numHeadings == 31){
        return "Presentations";
    }
    if (numHeadings == 43 || numHeadings == 44 || numHeadings == 45){
        return "Publications";
    }
    return "Unexpected CSV type";
}
