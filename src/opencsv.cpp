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
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <list>
#include <QtSql/QtSql>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

static list<string> headingList;

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

    headingList.clear();

    QSqlDatabase sqlDatabase = QSqlDatabase::database("db_connection");                 // new database connection created
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

    string tableName = getTypeFromHeadingList();                      // creates new table with the appropriate name
    cout<<tableName<<endl;
    finalQuery = "DROP TABLE " + tableName + ";";                                       // drop table if it already exists, then insert new table

    qstr = QString::fromStdString(finalQuery);
    query.exec(qstr);


    finalQuery = "CREATE TABLE " + tableName + "(" + builtHeaderQuery + ");";           // create new table, with name to match type of csv (Teaching, Grants, etc)
    qstr = QString::fromStdString(finalQuery);
    query.exec(qstr);

    int counter = 0;
    while (getline(inputfile, currentLine))                                             // process the remaining rows line by line
    {
        sqlDatabase.transaction();
        finalQuery = "";
        builtValueQuery = "";

        std::string sToRemove = "\\";

        std::string::size_type i = currentLine.find(sToRemove);

        if (i != std::string::npos)
           currentLine.erase(i, sToRemove.length());

        tokenizer<escaped_list_separator<char> > tok(currentLine);                      // give boost tokenizer the currentline
        for(tokenizer<escaped_list_separator<char> >::iterator beg=tok.begin(); beg!=tok.end();++beg){
           builtValueQuery = builtValueQuery + " '" + (string)*beg + "',";
        }

        builtValueQuery  = builtValueQuery.substr(0, builtValueQuery.length()-1) +" ";
        string tableName = getTypeFromHeadingList();                                    // decides the type of CSV file from the number of the headings, names table appropriately
        finalQuery = "INSERT INTO " + tableName + " VALUES(" + builtValueQuery + ")";   // builds the query from the 28 values in a single row

        qstr = QString::fromStdString(finalQuery);                                      // cast to QString
        query.exec(qstr);                                                               // executes the database query, inserting one row into the table
        if (counter % 200 == 0){
            sqlDatabase.commit();
        }

        counter++;
    }

    if (tableName == "Grants"){
        qstr = QString::fromStdString("UPDATE Grants SET TotalAmount= Replace(replace(TotalAmount, '$', ''), ',', '');");
        query.exec(qstr);
    }
    if ((counter-1) % 200 != 0){
            sqlDatabase.commit();
    }
    cout << "done loading data. returning to MainWindow" << endl;
    return tableName;
}

/**
 * This helper function decides from a std::list containing
 * heading names which type of CSV file the headings correspond to.
 *
 * @return string with type of csv file (i.e. the desired SQL table name)
 */
string OpenCSV::getTypeFromHeadingList(){
    if (listContainsString("NumberofTeachingSessionsorWeeks")){
        return "Teaching";
    }
    if (listContainsString("FundingType")){
        return "Grants";
    }
    if (listContainsString("Host")){
        return "Presentations";
    }
    if (listContainsString("Publisher")){
        return "Publications";
    }

//    if (headings.size() == 27 || headings.size() == 28 || headings.size() == 29){
//        return "Teaching";
//    }
//    if (headings.size() == 37 || headings.size() == 38 || headings.size() == 39){
//        return "Grants";
//    }
//    if (headings.size() == 30 || headings.size() == 31){
//        return "Presentations";
//    }
//    if (headings.size() == 43 || headings.size() == 44 || headings.size() == 45){
//        return "Publications";
//    }


    return "Unexpected CSV type";
}

/**
 * This function removes specific characters from a CSV file,
 * which might be required: Boost Tokenizer breaks under
 * certain combinations of escape sequence characters, (backslashes are not good)
 * so the CSV can be pre-cleaned before tokenizing.
 *
 * @brief sanitizeCSV
 * @param string to remove
 * @param pathToFile
 * @return path to the sanitized file
 */
OpenCSV::removeFromCSV(string pathToFile, string stringToReplace){


      ifstream in(pathToFile);
      string str, line;
      while(getline(in, line))
        str += line + "\n";
      cout << str;

      in.close();

      std::string::iterator end_pos0 = std::remove(str.begin(), str.end(), '*');
      std::string::iterator end_pos1 = std::remove(str.begin(), str.end(), '(');
      std::string::iterator end_pos2 = std::remove(str.begin(), str.end(), ')');

      ofstream out(pathToFile); // Open for writing
      out << str;
      out.close();
     ///:~


}

/**
 * Helper function returns true if its input string exists
 * as a substring in a list
 *
 * @brief OpenCSV::listContainsString
 * @param stringToFind
 * @return
 */
bool OpenCSV::listContainsString(string stringToFind){

       std::list<string>::iterator iter = std::find (headingList.begin(), headingList.end(), stringToFind);

       if ( headingList.end() == iter)
       {
           return false;
       }
       else
       {
           return true;
       }

}
