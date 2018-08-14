#include"cursubjwidget.h"
#include"ui_cursubjwidget.h"
#include"../data/subjpool.h"
#include"../data/subject.h"
#include"../data/subjinfo.h"

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
    connect(SubjPool::instance(),
        SIGNAL(curSubjChanged()),this,
        SLOT(onCurSubjChanged()));
    updateUi();
}

void CurSubjWidget::updateUi(){
    SubjInfo subjInfo;
    if(SubjPool::instance()->getCurSubjInfo(subjInfo)<0){
        _ui->_idLineEdit->setText("");
        _ui->_nameLineEdit->setText("");
        _ui->_birthdayLineEdit->setText("");
        _ui->_sexLineEdit->setText("");
    }else{
        _ui->_idLineEdit->setText(subjInfo.getId());
        _ui->_nameLineEdit->setText(subjInfo.getName());
        _ui->_birthdayLineEdit->setText(subjInfo.getBirthdayText());
        _ui->_sexLineEdit->setText(subjInfo.getSexText());
    }
}
