unix:INCLUDEPATH += /usr/local/include
unix:LIBS += -L/usr/local/lib -lboost_system -lboost_thread -lboost_chrono -lboost_date_time

win32:INCLUDEPATH += "D:/Distribs/boost/boost_1_55_0"
win32:LIBS += -L"D:/Distribs/boost/boost_1_55_0/stage/lib"
