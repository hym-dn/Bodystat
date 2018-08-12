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
    ui/waitdialog.ui \
    ui/devinfowidget.ui \
    ui/downloaddatawidget.ui \
    ui/startdialog.ui \
    ui/assigndownloadwidget.ui

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
    src/task/pullsubjvtask.cpp \
    src/ui/waitdialog.cpp \
    src/ui/subjlistmodel.cpp \
    src/ui/subjsortfilterproxymodel.cpp \
    src/ui/devinfowidget.cpp \
    src/dev/dev.cpp \
    src/commu/commu.cpp \
    src/commu/btcommu.cpp \
    src/commu/commupool.cpp \
    src/dev/bluetooth.cpp \
    src/dev/bodystat.cpp \
    src/dev/devpool.cpp \
    src/data/testdata.cpp \
    src/data/testdatapool.cpp \
    src/ui/downloaddatawidget.cpp \
    src/ui/testdatatablemodel.cpp \
    src/ui/startdialog.cpp \
    src/task/taskpool.cpp \
    src/task/starttask.cpp \
    src/data/subjinfo.cpp \
    src/ui/assigndownloadwidget.cpp

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
    src/task/pullsubjvtask.h \
    src/ui/waitdialog.h \
    src/ui/subjlistmodel.h \
    src/ui/subjsortfilterproxymodel.h \
    src/ui/devinfowidget.h \
    src/dev/dev.h \
    src/commu/commu.h \
    src/commu/btcommu.h \
    src/commu/commupool.h \
    src/dev/bluetooth.h \
    src/dev/bodystat.h \
    src/dev/devpool.h \
    src/data/testdata.h \
    src/data/testdatapool.h \
    src/ui/downloaddatawidget.h \
    src/ui/testdatatablemodel.h \
    src/ui/startdialog.h \
    src/task/taskpool.h \
    src/task/starttask.h \
    src/data/subjinfo.h \
    src/ui/assigndownloadwidget.h

DESTDIR += ../bin

PRECOMPILED_HEADER += ./precompile.h

LIBS+= ../lib/BodystatSDK.lib

RESOURCES += \
    res/bodystat.qrc
