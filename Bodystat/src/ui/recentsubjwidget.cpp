#include"recentsubjwidget.h"
#include"ui_recentsubjwidget.h"

RecentSubjWidget::RecentSubjWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::RecentSubjWidget){
    _ui->setupUi(this);
}

RecentSubjWidget::~RecentSubjWidget(){
    delete _ui;
}
