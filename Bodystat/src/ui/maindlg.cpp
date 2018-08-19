#include"maindlg.h"
#include"ui_maindlg.h"
#include"../theme/thememanager.h"
#include"subjwidget.h"
#include"cursubjwidget.h"
#include"selsubjwidget.h"
#include"../data/subject.h"
#include"../data/subjpool.h"
#include"devinfowidget.h"
#include"../dev/devpool.h"
#include"../dev/bluetooth.h"
#include"../dev/bodystat.h"
#include"assigndownloadwidget.h"
#include"downloaddatawidget.h"
#include"curtestdatawidget.h"
#include"../data/subjinfo.h"
#include"recentsubjwidget.h"
#include"../db/dbmanager.h"
#include"selreportwidget.h"
#include"printpreviewwidget.h"
#include<QSharedPointer>
#include<QMessageBox>
#include<QMenu>

MainDlg::MainDlg(QWidget *parent/*=0*/)
    :QDialog(parent)
    ,_ui(new Ui::MainDlg)
    ,_subWidget(0)
    ,_delUnasMenu(0)
    ,_recSubjMenu(0){
    _ui->setupUi(this);
    customUi();
    initUi();
}

MainDlg::~MainDlg(){
    delete _ui;
}

void MainDlg::onSubWidgetClose(){
    if(0!=_subWidget){
        _ui->_mainMdiArea->closeAllSubWindows();
        _ui->_mainMdiArea->removeSubWindow(_subWidget);
        //delete _subWidget;
        _subWidget=0;
    }
}

void MainDlg::onNewSubjToolButtonClicked(bool){
    creat(SUB_WIDGET_ID_NEW_SUBJ);
}

void MainDlg::onSelSubjToolButtonClicked(bool){
    creat(SUB_WIDGET_ID_SEL_SUBJ);
}

void MainDlg::onDelSubjToolButtonClicked(bool){
    if(SubjPool::instance()->getCurSubjIdx()<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("报警"),tr("没有主题被选择！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    creat(SUB_WIDGET_ID_DEL_SUBJ);
}

void MainDlg::onEdtSubjToolButtonClicked(bool){
    if(SubjPool::instance()->getCurSubjIdx()<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("报警"),tr("没有主题被选择！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    creat(SUB_WIDGET_ID_EDT_SUBJ);
}

void MainDlg::onDelUnasActionTriggered(bool){
    QAction *action=dynamic_cast<QAction*>(sender());
    if(0==action){
        return;
    }
    SubjInfo subjInfo;
    if(SubjPool::instance()->getCurSubjInfo(subjInfo)<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("报警"),tr("没有主题被选择！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    if(1==action->data().toInt()){
        QMessageBox msgBox(QMessageBox::Question,
            tr("询问"),tr("继续将彻底从数据库删除当前主题，是否继续？"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes,tr("是"));
        msgBox.setButtonText(QMessageBox::No,tr("否"));
        int result=msgBox.exec();
        if(QMessageBox::No==result){ // 否
            return;
        }
        if(SubjPool::instance()->erase(DBManager::instance()->
            getDB(),subjInfo.getId())<0){
            QMessageBox msgBox(QMessageBox::Warning,
                tr("警报"),tr("对不起删除失败，请重试！"));
            msgBox.setFont(font());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();
            return;
        }
        SubjPool::instance()->setCurSubj(-1);
    }else{
        if(SubjPool::instance()->getCurTestDataIdx()<0){
            QMessageBox msgBox(QMessageBox::Warning,
                tr("报警"),tr("没有测试被选择！"));
            msgBox.setFont(font());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();
            return;
        }
        QMessageBox msgBox(QMessageBox::Question,
            tr("询问"),tr("继续将取消当前测试的分配，是否继续？"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setButtonText(QMessageBox::Yes,tr("是"));
        msgBox.setButtonText(QMessageBox::No,tr("否"));
        int result=msgBox.exec();
        if(QMessageBox::No==result){ // 否
            return;
        }
        if(SubjPool::instance()->unassign(
            DBManager::instance()->getDB())<0){
            QMessageBox msgBox(QMessageBox::Warning,
                tr("警报"),tr("取消测试分配失败，请重试！"));
            msgBox.setFont(font());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();
            return;
        }
        SubjPool::instance()->setCurSubj(subjInfo.getId());
    }
}

void MainDlg::onRecSubjMenuAboutToShow(){
    _recSubjMenu->clear();
    int subjCount=SubjPool::instance()->count();
    if(subjCount>20){subjCount=20;}
    for(int i=0;i<subjCount;++i){
        SubjInfo subjInfo;
        SubjPool::instance()->getSubjInfo(i,subjInfo);
        QAction *action=_recSubjMenu->addAction(
            subjInfo.getName());
        action->setData(i);
        connect(action,SIGNAL(triggered(bool)),
            this,SLOT(onRecSubjActionTriggered(bool)));
    }
}

void MainDlg::onRecSubjActionTriggered(bool){
    QAction *action=dynamic_cast<QAction*>(sender());
    if(0==action){
        return;
    }
    SubjPool::instance()->setCurSubj(action->data().toInt());
    creat(SUB_WIDGET_ID_REC_SUBJ);
}

void MainDlg::onAssignDownloadToolButtonClicked(bool){
    creat(SUB_WIDGET_ID_ASN_DWLD);
}

void MainDlg::onDownloadDataToolButtonClicked(bool){
    if(!DevPool::instance()->getBodyStat()->getIsOpen()||
        !DevPool::instance()->getBodyStat()->getIsConnect()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("报警"),tr("设备尚未就绪！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    creat(SUB_WIDGET_ID_DWL_DATA);
}

void MainDlg::onDevInfoToolButtonClicked(bool){
    creat(SUB_WIDGET_ID_DEV_INFO);
}

void MainDlg::onBodyCompToolButtonClicked(bool){
    if(SubjPool::instance()->getCurSubjIdx()<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("报警"),tr("没有主题被选择！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    creat(SUB_WIDGET_ID_SEL_REPT);
}

void MainDlg::onPrintPreview(){
    creat(SUB_WIDGET_ID_PRI_PREV);
}

void MainDlg::onBtTaskStart(const unsigned int /*id*/){
    _ui->_newSubjToolButton->setDisabled(true);
    _ui->_selSubjToolButton->setDisabled(true);
    _ui->_delSubjToolButton->setDisabled(true);
    _ui->_edtSubjToolButton->setDisabled(true);
    _ui->_delUnasToolButton->setDisabled(true);
    _ui->_recSubjToolButton->setDisabled(true);
    _ui->_assignDownloadToolButton->setDisabled(true);
    _ui->_downloadDataToolButton->setDisabled(true);
    _ui->_devInfoToolButton->setDisabled(true);
    _ui->_bodyCompToolButton->setDisabled(true);
}

void MainDlg::onBtTaskDone(
    const unsigned int /*id*/,const unsigned int /*err*/){
    _ui->_newSubjToolButton->setDisabled(false);
    _ui->_selSubjToolButton->setDisabled(false);
    _ui->_delSubjToolButton->setDisabled(false);
    _ui->_edtSubjToolButton->setDisabled(false);
    _ui->_delUnasToolButton->setDisabled(false);
    _ui->_recSubjToolButton->setDisabled(false);
    _ui->_assignDownloadToolButton->setDisabled(false);
    _ui->_downloadDataToolButton->setDisabled(false);
    _ui->_devInfoToolButton->setDisabled(false);
    _ui->_bodyCompToolButton->setDisabled(false);
}

void MainDlg::customUi(){
    _ui->_newSubjToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_selSubjToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_delSubjToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_edtSubjToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_delUnasToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_recSubjToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_assignDownloadToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_downloadDataToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_devInfoToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_bodyCompToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
}

void MainDlg::initUi(){
    setWindowFlags(Qt::CustomizeWindowHint|
        Qt::WindowMinimizeButtonHint|
        Qt::WindowMaximizeButtonHint|
        Qt::WindowCloseButtonHint);
    setWindowState(Qt::WindowMaximized);
    connect(_ui->_newSubjToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onNewSubjToolButtonClicked(bool)));
    connect(_ui->_selSubjToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onSelSubjToolButtonClicked(bool)));
    connect(_ui->_delSubjToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onDelSubjToolButtonClicked(bool)));
    connect(_ui->_edtSubjToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onEdtSubjToolButtonClicked(bool)));
    _delUnasMenu=new QMenu(_ui->_delUnasToolButton);
    QAction *action=_delUnasMenu->addAction(tr("删除"));
    action->setData(1);
    connect(action,SIGNAL(triggered(bool)),this,SLOT(
        onDelUnasActionTriggered(bool)));
    action=_delUnasMenu->addAction(tr("取消分配"));
    action->setData(2);
    connect(action,SIGNAL(triggered(bool)),this,SLOT(
        onDelUnasActionTriggered(bool)));
    _ui->_delUnasToolButton->setMenu(_delUnasMenu);
    _recSubjMenu=new QMenu(_ui->_recSubjToolButton);
    _ui->_recSubjToolButton->setMenu(_recSubjMenu);
    connect(_recSubjMenu,SIGNAL(aboutToShow()),
        this,SLOT(onRecSubjMenuAboutToShow()));
    connect(_ui->_assignDownloadToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onAssignDownloadToolButtonClicked(bool)));
    connect(_ui->_downloadDataToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onDownloadDataToolButtonClicked(bool)));
    connect(_ui->_devInfoToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onDevInfoToolButtonClicked(bool)));
    connect(_ui->_bodyCompToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onBodyCompToolButtonClicked(bool)));
    connect(DevPool::instance()->getBluetooth(),
        SIGNAL(taskStart(const unsigned int)),this,
        SLOT(onBtTaskStart(const unsigned int)));
    connect(DevPool::instance()->getBluetooth(),
        SIGNAL(taskDone(const unsigned int,const unsigned int)),
        this,SLOT(onBtTaskDone(const unsigned int,
        const unsigned int)));
    _ui->_subjDockWidget->setWidget(
        new CurSubjWidget(_ui->_subjDockWidget));
    _ui->_testDockWidget->setWidget(
        new CurTestDataWidget(_ui->_testDockWidget));
}

void MainDlg::creat(const SubWidgetID widgetId){
    destry();
    if(SUB_WIDGET_ID_NEW_SUBJ==widgetId){
        _subWidget=new SubjWidget;
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_SEL_SUBJ==widgetId){
        _subWidget=new SelSubjWidget;
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_DEL_SUBJ==widgetId){
        SubjInfo subjInfo;
        SubjPool::instance()->getCurSubjInfo(subjInfo);
        _subWidget=new SubjWidget(SubjWidget::MODE_DELETE,&subjInfo);
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_EDT_SUBJ==widgetId){
        SubjInfo subjInfo;
        SubjPool::instance()->getCurSubjInfo(subjInfo);
        _subWidget=new SubjWidget(SubjWidget::MODE_EDIT,&subjInfo);
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_REC_SUBJ==widgetId){
        _subWidget=new RecentSubjWidget;
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_ASN_DWLD==widgetId){
        _subWidget=new AssignDownloadWidget;
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_DWL_DATA==widgetId){
        _subWidget=new DownloadDataWidget;
        Q_ASSERT(0!=_subWidget);
        connect(_subWidget,SIGNAL(showAssignDownloadWidget(bool)),
            this,SLOT(onAssignDownloadToolButtonClicked(bool)));
    }else if(SUB_WIDGET_ID_DEV_INFO==widgetId){
        _subWidget=new DevInfoWidget;
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_SEL_REPT==widgetId){
        _subWidget=new SelReportWidget;
        Q_ASSERT(0!=_subWidget);
        connect(_subWidget,SIGNAL(printPreview()),
            this,SLOT(onPrintPreview()));
    }else if(SUB_WIDGET_ID_PRI_PREV==widgetId){
        _subWidget=new PrintPreviewWidget;
        Q_ASSERT(0!=_subWidget);
    }
    _subWidget->setAttribute(Qt::WA_DeleteOnClose); // 关闭即销毁
    connect(_subWidget,SIGNAL(s_close()),this,
        SLOT(onSubWidgetClose()));
    _ui->_mainMdiArea->addSubWindow(_subWidget);
    _subWidget->show();
}

void MainDlg::destry(){
    if(0!=_subWidget){
        _subWidget->close();
    }
}
