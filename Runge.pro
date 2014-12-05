#-------------------------------------------------
#
# Project created by QtCreator 2014-11-28T18:49:28
#
#-------------------------------------------------

QT       += core gui
CONFIG += qwt
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += gui
TARGET = Runge
TARGET = qwt
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
