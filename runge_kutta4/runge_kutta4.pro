#-------------------------------------------------
#
# Project created by QtCreator 2021-06-02T23:09:12
#
#-------------------------------------------------

QT       -= core gui

TARGET = runge_kutta4
TEMPLATE = lib

DEFINES += RUNGE_KUTTA4_LIBRARY

SOURCES += runge_kutta4.cpp

HEADERS += runge_kutta4.h \
    ../solver/headers/solver_interface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../../target/release
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../target/debug

CONFIG += C++11
