#include"sysconfigwidget.h"
#include"ui_sysconfigwidget.h"
#include"../data/hispinfo.h"
#include"../data/sysinfopool.h"
#include"../db/dbmanager.h"
#include<QSharedPointer>
#include<QMessageBox>

SysConfigWidget::SysConfigWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::SysConfigWidget){
    _ui->setupUi(this);
    initUi();
}

SysConfigWidget::~SysConfigWidget(){
    delete _ui;
}

void SysConfigWidget::onSavePushButtonClicked(bool){
    QSharedPointer<HispInfo> hispInfo(new HispInfo);
    if(hispInfo.isNull()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，内存分配失败，请重试！"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    QString text=_ui->_hospitalNameLineEdit->text();
    hispInfo->setHispName(text);
    text=_ui->_sectionNameLineEdit->text();
    hispInfo->setSectName(text);
    const int res=hispInfo->isValid(&text);
    if(res<0){
        QMessageBox msgBox(
            QMessageBox::Warning,tr("警报"),text);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,
            QApplication::tr("确定"));
        msgBox.exec();
        if(-1==res){
            _ui->_hospitalNameLineEdit->setFocus();
        }else if(-2==res){
            _ui->_sectionNameLineEdit->setFocus();
        }
        return;
    }
    if(SysInfoPool::instance()->push(
        hispInfo,DBManager::instance()->getDB())<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，数据库操作失败，请重试！"));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    QMessageBox msgBox(QMessageBox::Information,
        tr("提示"),tr("医院信息保存完成！"));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
    msgBox.exec();
}

void SysConfigWidget::initUi(){
    _ui->_hospitalNameLineEdit->setMaxLength(46);
    _ui->_hospitalNameLineEdit->setText(SysInfoPool::
        instance()->getHispInfo()->getHispName());
    _ui->_sectionNameLineEdit->setMaxLength(46);
    _ui->_sectionNameLineEdit->setText(SysInfoPool::
        instance()->getHispInfo()->getSectName());
    connect(_ui->_savePushButton,SIGNAL(clicked(bool)),
        this,SLOT(onSavePushButtonClicked(bool)));
}
