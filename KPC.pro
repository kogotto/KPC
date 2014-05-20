
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
    markedpictureeditor.cpp \
    unmarkedpictureeditor.cpp \
    picturewidget.cpp

HEADERS  += mainwindow.h \
    picturesproject.h \
    unmarkedmodel.h \
    markedmodel.h \
    pictureeditor.h \
    markedpictureeditor.h \
    picturestructs.h \
    unmarkedpictureeditor.h \
    picturewidget.h

FORMS    += mainwindow.ui

OTHER_FILES +=

