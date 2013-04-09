#-------------------------------------------------
#
# Project created by QtCreator 2013-04-09T15:30:56
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_mathutilstest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../
HEADERS += ../mathutils.h
SOURCES += ../mathutils.cpp
SOURCES += tst_mathutilstest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
