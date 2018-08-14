#include"curtestdatawidget.h"
#include"ui_curtestdatawidget.h"
#include"../data/testdata.h"
#include"../data/subjpool.h"

CurTestDataWidget::CurTestDataWidget(
    QWidget *parent/*=0*/)
    :QWidget(parent)
    ,_ui(new Ui::CurTestDataWidget){
    _ui->setupUi(this);
    initUi();
}

CurTestDataWidget::~CurTestDataWidget(){
    delete _ui;
}

void CurTestDataWidget::onCurTestDataChanged(){
    updateUi();
}

void CurTestDataWidget::initUi(){
    connect(SubjPool::instance(),SIGNAL(
        curTestDataChanged()),this,SLOT(onCurTestDataChanged()));
}

void CurTestDataWidget::updateUi(){
    SubjPool::PtrCTestData testData=
        SubjPool::instance()->getCurTestData();
    if(testData.isNull()){
        _ui->_testDateTimeLineEdit->setText("");
        _ui->_devLineEdit->setText("");
        _ui->_heightLineEdit->setText("");
        _ui->_weightLineEdit->setText("");
        _ui->_testNoteTextEdit->setText("");
    }else{
        _ui->_testDateTimeLineEdit->setText(testData->getTestDateTimeText());
        _ui->_devLineEdit->setText(testData->getDevModelText());
        _ui->_heightLineEdit->setText(testData->getHeightText());
        _ui->_weightLineEdit->setText(testData->getWeightText());
        _ui->_testNoteTextEdit->setText("");
    }
}
