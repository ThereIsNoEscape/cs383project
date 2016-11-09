#-------------------------------------------------
#
# Project created by QtCreator 2016-11-09T07:26:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower_of_Lights_Editor_V3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openFile.cpp \
    TanFile_Save.cpp \
    tanfile_new.cpp

HEADERS  += mainwindow.h \
    TanFile.h

FORMS    += mainwindow.ui
