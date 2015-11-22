#ifndef DB_H
#define DB_H

#include <string>
using namespace std;
class DB
{
public:
    DB();
    void createDatabase();
    string teachingCsvIntoDb(string);
    string getTypeFromHeadingList(int);
};

#endif // DB_H
