#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T08:50:15
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
LIBS += -lgdi32
LIBS += -lwinmm
INCLUDEPATH+= -I D:\ruanjian\Python\include
LIBS +=-L D:\ruanjian\Python\libs -lpython27
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player
TEMPLATE = app


SOURCES += main.cpp playmedia.cpp download.cpp \
    searchbutton.cpp \
    nofocusdelegate.cpp
HEADERS  += mainwindow.h play.h   download.h \
    searchbutton.h \
    no_focus_delegate.h

FORMS    += mainwindow.ui

RESOURCES += \
    pic.qrc
