#-------------------------------------------------
#
# Project created by QtCreator 2016-02-02T13:33:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TCPTuner
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
    tcp_grapher.cpp

HEADERS  += mainwindow.h \
            qcustomplot.h \
    tcp_grapher.h

FORMS    += mainwindow.ui
