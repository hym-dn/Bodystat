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
    ui/assigndownloadwidget.ui \
    ui/curtestdatawidget.ui \
    ui/recentsubjwidget.ui \
    ui/selreportwidget.ui \
    ui/printpreviewwidget.ui \
    ui/newsubjdlg.ui \
    ui/sysconfigwidget.ui

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
    src/ui/assigndownloadwidget.cpp \
    src/ui/testdatalistmodel.cpp \
    src/ui/curtestdatawidget.cpp \
    src/ui/recentsubjwidget.cpp \
    src/ui/selreportwidget.cpp \
    src/task/reporttask.cpp \
    src/ui/printpreviewwidget.cpp \
    src/ui/newsubjdlg.cpp \
    src/ui/sysconfigwidget.cpp \
    src/data/hispinfo.cpp \
    src/data/sysinfopool.cpp \
    src/data/fatrange.cpp \
    src/data/fatparam.cpp \
    src/data/tbwparam.cpp \
    src/data/tbwrange.cpp \
    src/data/leanparam.cpp \
    src/data/leanrange.cpp \
    src/data/bmirange.cpp \
    src/data/bmiparam.cpp \
    src/report/graphic/chart.cpp

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
    src/ui/assigndownloadwidget.h \
    src/ui/testdatalistmodel.h \
    src/ui/curtestdatawidget.h \
    src/ui/recentsubjwidget.h \
    src/ui/selreportwidget.h \
    src/task/reporttask.h \
    src/ui/printpreviewwidget.h \
    src/ui/newsubjdlg.h \
    src/ui/sysconfigwidget.h \
    src/data/hispinfo.h \
    src/data/sysinfopool.h \
    src/data/fatrange.h \
    src/data/fatparam.h \
    src/data/tbwparam.h \
    src/data/tbwrange.h \
    src/data/leanparam.h \
    src/data/leanrange.h \
    src/data/bmirange.h \
    src/data/bmiparam.h \
    src/report/graphic/chart.h

DESTDIR += ../bin

PRECOMPILED_HEADER += ./precompile.h

LIBS+= ../lib/BodystatSDK.lib

RESOURCES += \
    res/bodystat.qrc
