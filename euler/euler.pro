#-------------------------------------------------
#
# Project created by QtCreator 2021-06-02T23:11:57
#
#-------------------------------------------------

QT       -= core gui

TARGET = euler
TEMPLATE = lib

DEFINES += EULER_LIBRARY

SOURCES += euler.cpp

HEADERS += euler.h \
    ../solver/headers/solver_interface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../../target
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../target

CONFIG += C++11
