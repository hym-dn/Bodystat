#include"selsubjwidget.h"
#include"ui_selsubjwidget.h"

SelSubjWidget::SelSubjWidget(QWidget *parent/*=0*/)
    :QWidget(parent)
    ,_ui(new Ui::SelSubjWidget){
    _ui->setupUi(this);
}

SelSubjWidget::~SelSubjWidget(){
    delete _ui;
}
