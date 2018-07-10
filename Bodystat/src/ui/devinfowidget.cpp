#include"devinfowidget.h"
#include"ui_devinfowidget.h"
#include<QMovie>

DevInfoWidget::DevInfoWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::DevInfoWidget){
    _ui->setupUi(this);
    initUi();
}

DevInfoWidget::~DevInfoWidget(){
    delete _ui;
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
    //_ui->_progressLabel->hide();
}
