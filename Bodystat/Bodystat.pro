#-------------------------------------------------
#
# Project created by QtCreator 2018-06-24T16:43:26
#
#-------------------------------------------------

QT       += core gui axcontainer sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bodystat
TEMPLATE = app

FORMS    += \
    ui/maindlg.ui

SOURCES += \
    src/main.cpp \
    src/ui/maindlg.cpp \
    src/report/word/wordengine.cpp \
    src/db/dbmanager.cpp

HEADERS += \
    src/ui/maindlg.h \
    src/report/word/wordengine.h \
    src/comm/singleton.h \
    src/db/dbmanager.h

DESTDIR += ../bin

PRECOMPILED_HEADER += ./precompile.h
