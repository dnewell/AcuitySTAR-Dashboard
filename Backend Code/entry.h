#ifndef ENTRY_H
#define ENTRY_H
#include <QString>


class Entry
{
public:

    QString faculty;
    int hours;
    int students;

    Entry();
    Entry(QString, int, int);
};

#endif // ENTRY_H
