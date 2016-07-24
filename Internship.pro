#-------------------------------------------------
#
# Project created by QtCreator 2016-07-12T14:08:26
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Internship
TEMPLATE = app

#CONFIG += console


SOURCES += main.cpp\
        mainwindow.cpp \
    logintask.cpp \
    loginmgrthd.cpp \
    connectmgrthd.cpp \
    mgrthd.cpp

HEADERS  += mainwindow.h \
    TGClientSDK.h \
    logintask.h \
    loginmgrthd.h \
    connectmgrthd.h \
    mgrthd.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -L$$PWD/./ -lNetClientSDK

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
