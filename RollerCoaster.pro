#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T22:29:41
#                                     by b10215029
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RollerCoaster
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
	rollercoasterview.cpp \
	mesh.cpp \
    gameobject.cpp \
    camera.cpp \
    texturedb.cpp \
    mat.cpp \
    vec.cpp \
    light.cpp \
    track.cpp \
    transform.cpp

HEADERS  += mainwindow.h \
	rollercoasterview.h \
	mesh.h \
    gameobject.h \
    camera.h \
    texturedb.h \
    mat.h \
    vec.h \
    light.h \
    track.h \
    transform.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
