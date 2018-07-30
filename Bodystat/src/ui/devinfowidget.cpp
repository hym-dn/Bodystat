#include"devinfowidget.h"
#include"ui_devinfowidget.h"
#include"../dev/devpool.h"
#include"../dev/bluetooth.h"
#include"../dev/bodystat.h"
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
    DevPool::instance()->getBluetooth()->connDev(
        DevPool::instance()->getBodyStat());
}

void DevInfoWidget::onDrivInfoChanged(){
    const QString drivInfo=DevPool::instance()->
        getBluetooth()->getDrivInfo();
    if(drivInfo.isEmpty()){
        _ui->_bluetoothLabel->setPixmap(
            QPixmap(":rc/bluetoothdisabled.png"));
    }else{
        _ui->_bluetoothLabel->setPixmap(
            QPixmap(":rc/bluetoothconnected.png"));
    }
    _ui->_btStackInfoLabel->setText(drivInfo);
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
    connect(DevPool::instance()->getBluetooth(),
        SIGNAL(drivInfoChanged()),this,SLOT(
        onDrivInfoChanged()));
}
