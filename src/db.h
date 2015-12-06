#ifndef DB_H
#define DB_H

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <QtSql/QtSql>
#include <boost/tokenizer.hpp>
using namespace std;
class DB
{
public:
    DB();
    ~DB();
    void createDatabase();
};

#endif // DB_H
