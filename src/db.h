#ifndef DB_H
#define DB_H

#include <string>
using namespace std;
class DB
{
public:
    DB();
    void createDatabase();
    void teachingCsvIntoDb(string);
};

#endif // DB_H
