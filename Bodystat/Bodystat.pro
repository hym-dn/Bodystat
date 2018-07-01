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
    ui/maindlg.ui \
    ui/subjwidget.ui

SOURCES += \
    src/main.cpp \
    src/ui/maindlg.cpp \
    src/report/word/wordengine.cpp \
    src/db/dbmanager.cpp \
    src/theme/thememanager.cpp \
    src/ui/subjwidget.cpp \
    src/ui/mdisubwidget.cpp \
    src/data/subject.cpp

HEADERS += \
    src/ui/maindlg.h \
    src/report/word/wordengine.h \
    src/comm/singleton.h \
    src/db/dbmanager.h \
    src/theme/thememanager.h \
    src/ui/subjwidget.h \
    src/ui/mdisubwidget.h \
    src/data/subject.h

DESTDIR += ../bin

PRECOMPILED_HEADER += ./precompile.h

RESOURCES += \
    res/bodystat.qrc
