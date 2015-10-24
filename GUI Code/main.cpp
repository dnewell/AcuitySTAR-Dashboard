#include "mainwindow.h"
#include <QApplication>

//launches main window
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
