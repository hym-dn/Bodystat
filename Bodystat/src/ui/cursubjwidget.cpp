#include"cursubjwidget.h"
#include"ui_cursubjwidget.h"
#include"../data/subjpool.h"
#include"../data/subject.h"

CurSubjWidget::CurSubjWidget(
    QWidget *parent/*=0*/)
    :QWidget(parent)
    ,_ui(new Ui::CurSubjWidget){
    _ui->setupUi(this);
    initUi();
}

CurSubjWidget::~CurSubjWidget(){
    delete _ui;
}

void CurSubjWidget::onCurSubjChanged(){
    updateUi();
}

void CurSubjWidget::initUi(){
    connect(SubjPool::instance(),SIGNAL(curSubjChanged()),
        this,SLOT(onCurSubjChanged()));
    updateUi();
}

void CurSubjWidget::updateUi(){
    _ui->_idLineEdit->setText(
        SubjPool::instance()->
        getCurSubj().getId());
    _ui->_nameLineEdit->setText(
        SubjPool::instance()->
        getCurSubj().getName());
    _ui->_ageLineEdit->setText(
        SubjPool::instance()->
        getCurSubj().getAgeText());
    _ui->_sexLineEdit->setText(
        SubjPool::instance()->
        getCurSubj().getSexText());
    _ui->_heightLineEdit->setText(
        SubjPool::instance()->
        getCurSubj().getHeightText());
    _ui->_weightLineEdit->setText(
        SubjPool::instance()->
        getCurSubj().getWeightText());
}
