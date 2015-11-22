#ifndef ENTRY_H
#define ENTRY_H
#include <QString>


class Entry
{
public:

    QString faculty;
    double hours;
    int students;

    Entry();
    Entry(QString, double, int);
};

#endif // ENTRY_H
