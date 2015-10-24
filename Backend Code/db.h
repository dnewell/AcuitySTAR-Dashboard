#ifndef DB_H
#define DB_H

#include <string>

class DB
{
public:
    DB();
    void createDatabase();
    void parseCSV(std::string);
};

#endif // DB_H
