#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T20:25:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = 3307_GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    dialog.ui
