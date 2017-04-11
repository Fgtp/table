#-------------------------------------------------
#
# Project created by QtCreator 2017-03-09T14:03:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImportantTable
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    significancetable.cpp \
    object.cpp \
    learningmodul.cpp \
    dialogobj.cpp \
    turntable.cpp

HEADERS  += mainwindow.h \
    significancetable.h \
    object.h \
    learningmodul.h \
    dialogobj.h \
    turntable.h

FORMS    += mainwindow.ui \
    dialogobj.ui
