#include "mainwindow.h"
#include "db.h"
#include <QApplication>
#include <db.h>

//launches main window
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DB* db = new DB();
    db->createDatabase();

    w.show();

    return a.exec();
}
