#include"maindlg.h"
#include"ui_maindlg.h"
#include"../theme/thememanager.h"
#include"subjwidget.h"
#include"cursubjwidget.h"
#include"waitdialog.h"
#include"../task/pullsubjvtask.h"
#include"../task/taskstream.h"
#include"selsubjwidget.h"
#include"../data/subject.h"
#include"../data/subjpool.h"
#include"devinfowidget.h"
#include<QSharedPointer>
#include<QMessageBox>

MainDlg::MainDlg(QWidget *parent/*=0*/)
    :QDialog(parent)
    ,_ui(new Ui::MainDlg)
    ,_subWidget(0){
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
    WaitDialog::PtrTask task(new PullSubjVTask(
        TaskStream::PROC_ROUTINE,true));
    if(task.isNull()){
        QMessageBox msgBox(QMessageBox::Critical,
            tr("异常"),tr("内存异常，请重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    WaitDialog dlg(task);
    if(0==dlg.exec()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("报警"),tr("主题信息查询失败，请重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    creat(SUB_WIDGET_ID_SEL_SUBJ);
}

void MainDlg::onDelSubjToolButtonClicked(bool){
    if(SubjPool::instance()->getCurSubj().isValid()<0){
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
    if(SubjPool::instance()->getCurSubj().isValid()<0){
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

void MainDlg::onDevInfoToolButtonClicked(bool){
    creat(SUB_WIDGET_ID_DEV_INFO);
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
    _ui->_recSubjToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_downloadDataToolButton->setStyleSheet(
        ThemeManager::instance()->styleSheet(
        ":rc/toolbutton.qss"));
    _ui->_devInfoToolButton->setStyleSheet(
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
    connect(_ui->_devInfoToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onDevInfoToolButtonClicked(bool)));
    _ui->_subjDockWidget->setWidget(
        new CurSubjWidget(_ui->_subjDockWidget));
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
        _subWidget=new SubjWidget(SubjWidget::MODE_DELETE,
            SubjPool::instance()->getCurSubj());
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_EDT_SUBJ==widgetId){
        _subWidget=new SubjWidget(SubjWidget::MODE_EDIT,
            SubjPool::instance()->getCurSubj());
        Q_ASSERT(0!=_subWidget);
    }else if(SUB_WIDGET_ID_DEV_INFO==widgetId){
        _subWidget=new DevInfoWidget;
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
