#-------------------------------------------------
#
# Project created by QtCreator 2015-11-21T17:38:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graphs
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    filereader.cpp \
    graph.cpp

HEADERS  += \
    filereader.h \
    mainwindow.h \
    graph.h

INCLUDEPATH += C:\Qt\Qt5.5.1\boost\boost_1_59_0 \
               C:\Qt\5.5\boost\boost_1_59_0

FORMS    += mainwindow.ui
