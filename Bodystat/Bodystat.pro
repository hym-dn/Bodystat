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
    ui/subjwidget.ui \
    ui/cursubjwidget.ui \
    ui/selsubjwidget.ui \
    ui/waitdialog.ui

SOURCES += \
    src/main.cpp \
    src/ui/maindlg.cpp \
    src/report/word/wordengine.cpp \
    src/db/dbmanager.cpp \
    src/theme/thememanager.cpp \
    src/ui/subjwidget.cpp \
    src/ui/mdisubwidget.cpp \
    src/data/subject.cpp \
    src/ui/selsubjwidget.cpp \
    src/data/subjpool.cpp \
    src/ui/cursubjwidget.cpp \
    src/task/taskproc.cpp \
    src/task/task.cpp \
    src/task/taskstream.cpp \
    src/task/pullsubjvtask.cpp \
    src/ui/waitdialog.cpp \
    src/ui/subjlistmodel.cpp \
    src/ui/subjsortfilterproxymodel.cpp

HEADERS += \
    src/ui/maindlg.h \
    src/report/word/wordengine.h \
    src/comm/singleton.h \
    src/db/dbmanager.h \
    src/theme/thememanager.h \
    src/ui/subjwidget.h \
    src/ui/mdisubwidget.h \
    src/data/subject.h \
    src/ui/cursubjwidget.h \
    src/ui/selsubjwidget.h \
    src/data/subjpool.h \
    src/task/taskproc.h \
    src/task/task.h \
    src/task/taskstream.h \
    src/task/pullsubjvtask.h \
    src/ui/waitdialog.h \
    src/ui/subjlistmodel.h \
    src/ui/subjsortfilterproxymodel.h

DESTDIR += ../bin

PRECOMPILED_HEADER += ./precompile.h

RESOURCES += \
    res/bodystat.qrc
