#include"downloaddatawidget.h"
#include"ui_downloaddatawidget.h"
#include<QMovie>

DownloadDataWidget::DownloadDataWidget(
    QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::DownloadDataWidget){
    _ui->setupUi(this);
    initUi();
}

DownloadDataWidget::~DownloadDataWidget(){
    delete _ui;
}

void DownloadDataWidget::initUi(){
    layout()->setSizeConstraint(
        QLayout::SetFixedSize);
    _ui->_promptLabel->setPixmap(
        QPixmap(":rc/prompt.png"));
    _ui->_devLabel->setPixmap(
        QPixmap(":rc/Quadscan4000.bmp"));
    QMovie *movie=new QMovie(":rc/progress.gif",
        QByteArray(),_ui->_progressLabel);
    _ui->_progressLabel->setMovie(movie);
    movie->start();
}
