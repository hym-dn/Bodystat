#include"devinfowidget.h"
#include"ui_devinfowidget.h"

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
}
