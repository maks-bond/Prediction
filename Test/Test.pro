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
HEADERS += ../modelgenerator.h \
    ../basicmodel.h \
    ../forecastmodel.h \
    ../alglib/stdafx.h \
    ../alglib/specialfunctions.h \
    ../alglib/solvers.h \
    ../alglib/optimization.h \
    ../alglib/linalg.h \
    ../alglib/interpolation.h \
    ../alglib/integration.h \
    ../alglib/ap.h \
    ../alglib/alglibmisc.h \
    ../alglib/alglibinternal.h \
    ../matrix.h \
    modelgeneratortest.h \
    ../datamodel.h \
    datamodeltest.h \
    ../datacompany.h \
    matrixtest.h \
    forecastmodeltest.h \
    multiseriesgmdhtest.h \
    ../multiseriesgmdh.h \
    ../abstractgmdh.h

SOURCES += ../modelgenerator.cpp \
    ../forecastmodel.cpp \
    ../alglib/specialfunctions.cpp \
    ../alglib/solvers.cpp \
    ../alglib/optimization.cpp \
    ../alglib/linalg.cpp \
    ../alglib/interpolation.cpp \
    ../alglib/integration.cpp \
    ../alglib/ap.cpp \
    ../alglib/alglibmisc.cpp \
    ../alglib/alglibinternal.cpp \
    ../matrix.cpp \
    main.cpp \
    modelgeneratortest.cpp \
    ../datamodel.cpp \
    datamodeltest.cpp \
    ../datacompany.cpp \
    matrixtest.cpp \
    forecastmodeltest.cpp \
    multiseriesgmdhtest.cpp \
    ../multiseriesgmdh.cpp \
    ../abstractgmdh.cpp

SOURCES +=
DEFINES += SRCDIR=\\\"$$PWD/\\\"
