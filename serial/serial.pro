#-------------------------------------------------
#
# Project created by QtCreator 2022-08-05T13:57:31
#
#-------------------------------------------------

QT       += core gui serialport
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

RC_ICONS = theme.ico

