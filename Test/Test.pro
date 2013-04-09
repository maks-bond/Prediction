#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T15:30:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../
HEADERS += ../mathutils.h \
    ../modelgenerator.h \
    ../basicmodel.h

SOURCES += ../mathutils.cpp \
    ../modelgenerator.cpp \
    test.cpp \
    ../basicmodel.cpp

SOURCES +=
DEFINES += SRCDIR=\\\"$$PWD/\\\"
