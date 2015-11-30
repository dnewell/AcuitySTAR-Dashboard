#ifndef OPENCSV_H
#define OPENCSV_H

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <QtSql/QtSql>
#include <boost/tokenizer.hpp>

class OpenCSV
{
public:
    OpenCSV();
    std::string csvIntoDb(std::string);
    std::string getTypeFromHeadingList(int);
};



#endif // OPENCSV_H
