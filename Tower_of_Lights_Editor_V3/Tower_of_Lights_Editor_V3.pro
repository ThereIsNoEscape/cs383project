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
    tanfile_new.cpp \
    cell.cpp \
    tanfile.cpp \
    openfile.cpp \
    tanfile_save.cpp \
    lettereffectdialog.cpp \
    symboleffectdialog.cpp \
    shapeeffectdialog.cpp \
    preview.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    cell.h \
    config.h \
    tanfile.h \
    effect.h \
    lettereffectdialog.h \
    symboleffectdialog.h \
    shapeeffectdialog.h \
    preview.h \
    thread.h

FORMS    += mainwindow.ui \
    lettereffectdialog.ui \
    symboleffectdialog.ui \
    shapeeffectdialog.ui \
    preview.ui

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/menus
INSTALLS += target

RESOURCES += \
    resources.qrc
