#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T17:00:13
#
#-------------------------------------------------

QT       += core gui xlsx

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnixViz
TEMPLATE = app


SOURCES += main.cpp\
        unixvizmainwindow.cpp \
    hmc.cpp \
    server.cpp \
    lpar.cpp \
    infopane.cpp \
    hmcbutton.cpp \
    serverbutton.cpp \
    hmcdisplay.cpp \
    rackdisplay.cpp \
    hmclabel.cpp \
    focusdisplay.cpp \
    serverlabel.cpp \
    lparlabel.cpp \
    subnetdisplay.cpp \
    lparbutton.cpp

HEADERS  += unixvizmainwindow.h \
    hmc.h \
    server.h \
    lpar.h \
    infopane.h \
    hmcbutton.h \
    serverbutton.h \
    hmcdisplay.h \
    rackdisplay.h \
    hmclabel.h \
    focusdisplay.h \
    serverlabel.h \
    lparlabel.h \
    subnetdisplay.h \
    lparbutton.h

FORMS    += unixvizmainwindow.ui

RESOURCES += \
    UnixViz.qrc
