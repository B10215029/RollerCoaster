#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T22:29:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RollerCoaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rollercoasterview.cpp \
    Track.cpp \
    ControlPoint.cpp \
    model.cpp

HEADERS  += mainwindow.h \
    rollercoasterview.h \
    Track.h \
    ControlPoint.h \
    vec3.h \
    mat4.h \
    model.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
