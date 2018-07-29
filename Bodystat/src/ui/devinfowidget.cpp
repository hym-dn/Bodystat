#include"devinfowidget.h"
#include"ui_devinfowidget.h"
#include"../commu/commupool.h"
#include"../commu/btcommu.h"
#include<QMovie>
#include<QMessageBox>

DevInfoWidget::DevInfoWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::DevInfoWidget){
    _ui->setupUi(this);
    initUi();
}

DevInfoWidget::~DevInfoWidget(){
    delete _ui;
}

void DevInfoWidget::onScanDevPushButtonClicked(bool){
    // 检测蓝牙驱动
    if(CommuPool::instance()->getBtCom()->isValid()<0){
        // 提示
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("蓝牙驱动异常！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        // 返回
        return;
    }
    // 获取蓝牙信息
    if(CommuPool::instance()->getBtCom()->readStackInfo()<0){
        // 提示
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("获取蓝牙信息失败！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        // 返回
        return;
    }
}

void DevInfoWidget::onBtStackInfoChanged(){
    const QString btStackInfo=CommuPool::
        instance()->getBtCom()->getStackInfo();
    if(btStackInfo.isEmpty()){
        _ui->_bluetoothLabel->setPixmap(
            QPixmap(":rc/bluetoothdisabled.png"));
    }else{
        _ui->_bluetoothLabel->setPixmap(
            QPixmap(":rc/bluetoothconnected.png"));
    }
    _ui->_btStackInfoLabel->setText(btStackInfo);
}

void DevInfoWidget::initUi(){
    _ui->_bluetoothLabel->setPixmap(
        QPixmap(":rc/bluetoothdisabled.png"));
    _ui->_devLabel->setPixmap(
        QPixmap(":rc/Quadscan4000.bmp"));
    QMovie *movie=new QMovie(":rc/progress.gif",
        QByteArray(),_ui->_progressLabel);
    _ui->_progressLabel->setMovie(movie);
    movie->start();
    _ui->_progressLabel->hide();
    connect(_ui->_scanDevPushButton,SIGNAL(
        clicked(bool)),this,SLOT(
        onScanDevPushButtonClicked(bool)));
    connect(CommuPool::instance()->getBtCom(),
        SIGNAL(stackInfoChanged()),this,SLOT(
        onBtStackInfoChanged()));
}
