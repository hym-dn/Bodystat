#include"cursubjwidget.h"
#include"ui_cursubjwidget.h"

CurSubjWidget::CurSubjWidget(QWidget *parent/*=0*/)
    :QWidget(parent)
    ,_ui(new Ui::CurSubjWidget){
    _ui->setupUi(this);
}

CurSubjWidget::~CurSubjWidget(){
    delete _ui;
}
