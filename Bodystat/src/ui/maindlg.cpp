#include"maindlg.h"
#include"ui_maindlg.h"
#include"../theme/thememanager.h"
#include"subjwidget.h"

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
        _subWidget=0;
    }
}

void MainDlg::onNewSubjToolButtonClicked(bool){
    creat(SUB_WIDGET_ID_SUBJ);
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
}

void MainDlg::initUi(){
    setWindowFlags(Qt::CustomizeWindowHint|
        Qt::WindowMinimizeButtonHint|
        Qt::WindowMaximizeButtonHint|
        Qt::WindowCloseButtonHint);
    setWindowState(Qt::WindowMaximized);
    connect(_ui->_newSubjToolButton,SIGNAL(clicked(bool)),
        this,SLOT(onNewSubjToolButtonClicked(bool)));
}

void MainDlg::creat(const SubWidgetID widgetId){
    destry();
    if(SUB_WIDGET_ID_SUBJ==widgetId){
        _subWidget=new SubjWidget;
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
