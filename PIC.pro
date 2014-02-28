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
    src/picsym/base/hilbert.cpp \
    src/picviz.cpp \
    src/picsym/base/slicer.cpp \
    src/picsym/parallelmachine.cpp \
    src/picsym/cellmesh2d.cpp \
    src/picsym/nodethread.cpp \
    src/picsym/base/cellrange.cpp

HEADERS  += include/picmainwindow.h \    
    include/picsym/base/mesh2d.h \
    include/picsym/node.h \
    include/picviz.h \
    include/picsym/base/hilbert.h \
    include/picsym/base/slicer.h \
    include/picsym/base/cell.h \
    include/picsym/base/array.h \
    include/picsym/base/inode.h \
    include/picsym/base/list.h \
    include/picsym/parallelmachine.h \
    include/picsym/nodethread.h \
    include/picsym/cellmesh2d.h \
    include/picsym/base/cellrange.h

FORMS    += picmainwindow.ui
