#-------------------------------------------------
#
# Project created by QtCreator 2013-03-25T14:51:24
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = diploma_desktop
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    modelitem.cpp \
    modelcompany.cpp \
    model.cpp \
    csv.cpp


HEADERS  += mainwindow.h \
    modelitem.h \
    modelcompany.h \
    model.h \
    csv.h

OTHER_FILES += \
    main.qml \
    Button.qml

RESOURCES += \
    res.qrc
