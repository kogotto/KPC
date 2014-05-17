#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T16:56:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KPC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    picturesproject.cpp \
    unmarkedmodel.cpp \
    markedmodel.cpp \
    pictureeditor.cpp \
    picturewidget.cpp \
    markedpictureeditor.cpp \
    unmarkedpictureeditor.cpp

HEADERS  += mainwindow.h \
    picturesproject.h \
    unmarkedmodel.h \
    markedmodel.h \
    pictureeditor.h \
    picturewidget.h \
    markedpictureeditor.h \
    picturestructs.h \
    unmarkedpictureeditor.h

FORMS    += mainwindow.ui

OTHER_FILES +=

LIBS += -L/usr/lib/x86_64-linux-gnu/
