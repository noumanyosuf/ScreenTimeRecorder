#-------------------------------------------------
#
# Project created by QtCreator 2014-03-02T14:01:31
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = screentimeservice
CONFIG   += console
CONFIG   -= app_bundle
include(QtService/qtservice.pri)
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    screentimeservice.cpp

HEADERS += \
    screentimeservice.h

win32: LIBS += -L$$PWD/../../../screentime_bin/release/ -lscreentimerecorder

INCLUDEPATH += $$PWD/../../../ScreenTimeAnalyser
DEPENDPATH += $$PWD/../../../ScreenTimeAnalyser

