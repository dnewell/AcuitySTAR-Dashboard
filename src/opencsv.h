#ifndef OPENCSV_H
#define OPENCSV_H

#include <iostream>
#include <fstream>
#include <list>
#include <QtSql/QtSql>
#include <boost/tokenizer.hpp>
#include <string>
#include <stdio.h>

class OpenCSV
{
public:
    OpenCSV();
    std::string csvIntoDb(std::string);
    std::string getTypeFromHeadingList();
private:
    void removeFromCSV(std::string, std::string);
    bool listContainsString(std::string);
};



#endif // OPENCSV_H
