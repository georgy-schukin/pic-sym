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
    src/picsym/meshpart.cpp \
    src/picsym/mesh2d.cpp \
    src/picsym/parallelmachine.cpp

HEADERS  += include/picmainwindow.h \    
    include/picsym/mesh2d.h \
    include/picsym/node.h \
    include/picviz.h \
    include/picsym/hilbert.h \
    include/picsym/slicer.h \
    include/picsym/meshpart.h \
    include/picsym/base/cell.h \
    include/picsym/base/array.h \
    include/picsym/base/inode.h \
    include/picsym/base/list.h \
    include/picsym/parallelmachine.h \
    include/picsym/nodethread.h

FORMS    += picmainwindow.ui
