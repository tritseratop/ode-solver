TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32-g++ {
    INCLUDEPATH += G:/boost/boost_1_74_0/boost_mingw_492/include/boost-1_74
    LIBS += "-LG:/boost/boost_1_74_0/boost_mingw_492/lib" \
            -llibboost_filesystem-mgw49-mt-d-x32-1_74 \

} else:win32-msvc* {
}

INCLUDEPATH += ../solver/headers/headers

SOURCES += main.cpp \
    print_tools.cpp \
    schema.cpp \
    solver_connector.cpp \
    solver_module.cpp

HEADERS += \
    headers/print_tools.h \
    headers/schema.h \
    headers/solver_connector.h \
    headers/solver_module.h \
    headers/solver_interface.h


win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../../target
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../target
