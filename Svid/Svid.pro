#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T14:23:47
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Svid
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DialGen.cpp \
    ModelUni.cpp \
    StorProject.cpp \
    TTableview.cpp \
    TTextedit.cpp

HEADERS  += mainwindow.h \
    DialGen.h \
    ModelUni.h \
    StorProject.h \
    TTableview.h \
    TTextedit.h

FORMS    += mainwindow.ui
