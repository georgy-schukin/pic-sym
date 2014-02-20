#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T17:01:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PIC
TEMPLATE = app

include(Local.pri)

SOURCES += main.cpp\
        picmainwindow.cpp

HEADERS  += picmainwindow.h \
    picsym/picsym.h \
    picsym/cell.h \
    picsym/mesh2d.h

FORMS    += picmainwindow.ui
