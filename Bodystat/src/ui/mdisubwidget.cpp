#include"mdisubwidget.h"
#include<QCloseEvent>

MdiSubWidget::MdiSubWidget(QWidget *parent/*=0*/)
    :QWidget(parent){
}

MdiSubWidget::~MdiSubWidget(){
}

void MdiSubWidget::closeEvent(QCloseEvent *event){
    event->accept();
    emit s_close();
}
