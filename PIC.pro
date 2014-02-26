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

INCLUDEPATH += $$PWD/include

SOURCES += src/main.cpp\
        src/picmainwindow.cpp \
    src/picsym/hilbert.cpp \
    src/picviz.cpp \
    src/picsym/slicer.cpp \
    src/picsym/machine.cpp \
    src/picsym/meshpart.cpp \
    src/picsym/mesh2d.cpp \
    src/picsym/cellarray.cpp

HEADERS  += include/picmainwindow.h \
    include/picsym/cell.h \
    include/picsym/mesh2d.h \
    include/picsym/node.h \
    include/picviz.h \
    include/picsym/hilbert.h \
    include/picsym/slicer.h \
    include/picsym/machine.h \
    include/picsym/meshpart.h \
    include/picsym/cellarray.h

FORMS    += picmainwindow.ui
