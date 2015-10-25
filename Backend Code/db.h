#ifndef DB_H
#define DB_H

#include <string>

class DB
{
public:
    DB();
    void createDatabase();
    void teachingCsvIntoDb(std::string);
};

#endif // DB_H
