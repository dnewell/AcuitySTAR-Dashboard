/**
 * DB class handles the creation of a new SQLite3 database instance,
 * opens a connection to it, and closes that instance upon a call
 * to it's overrided destructor
 *
 * Author: David Newell
 **/

#include "db.h"


using namespace std;
using namespace boost;

DB::DB()
{
}

/**
 * Destructor closes the connection used by the rest of the program
 */
DB::~DB()
{
    QSqlDatabase db = QSqlDatabase::database("db_connection");
    db.close();
}

/**
 * This method creates a new SQLite 3 database and sets the attributes (column/heading names)
 *
 * @brief DB::createDatabase
 */

void DB::createDatabase()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "db_connection");
    QString name = "database.sqlite";

    // database is created in the user's home directory
    db.setDatabaseName(QDir::homePath() + QDir::separator() + name);

    // this is the single database connection open() for the whole program
    db.open();
}





