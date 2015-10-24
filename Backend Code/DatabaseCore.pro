#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T18:18:19
#
#-------------------------------------------------

QT       += core
QT       += sql
QT       -= gui

QMAKE_CXXFLAGS += -std=gnu++11

TARGET = DatabaseCore
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    db.cpp \
    summary.cpp \
    year.cpp \
    entry.cpp

HEADERS += \
    db.h \
    main.h \
   #tokenizer.hpp \
    boost/tokenizer.hpp \
    summary.h \
    year.h \
    entry.h
