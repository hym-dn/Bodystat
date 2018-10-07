#include"teststatwidget.h"
#include"ui_teststatwidget.h"

TestStatWidget::TestStatWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::TestStatWidget){
    _ui->setupUi(this);
}

TestStatWidget::~TestStatWidget(){
    delete _ui;
}
