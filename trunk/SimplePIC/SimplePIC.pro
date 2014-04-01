TEMPLATE = app
CONFIG += console
CONFIG -= qt

unix:INCLUDEPATH += /usr/local/include
unix:INCLUDEPATH += /usr/include/mpich2
unix:LIBS += -L/usr/local/lib -lboost_system -lboost_thread -lboost_chrono -lboost_date_time

win32:INCLUDEPATH += "D:/Distribs/boost/boost_1_55_0"
win32:LIBS += -L"D:/Distribs/boost/boost_1_55_0/stage/lib"

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    pic.cpp

HEADERS += \
    particle.h \
    cell.h \
    vector2d.h \
    rect2d.h \
    cellmesh.h

