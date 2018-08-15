#include"recentsubjwidget.h"
#include"ui_recentsubjwidget.h"
#include"../data/subjinfo.h"
#include"../data/subjpool.h"
#include"../data/testdata.h"
#include"../data/testdatapool.h"

RecentSubjWidget::RecentSubjWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::RecentSubjWidget){
    _ui->setupUi(this);
    initUi();
    updateUi();
}

RecentSubjWidget::~RecentSubjWidget(){
    delete _ui;
}

void RecentSubjWidget::onCurSubjTestDataChanged(){
    updateUi();
}

void RecentSubjWidget::initUi(){
    connect(SubjPool::instance(),SIGNAL(curSubjChanged()),
        this,SLOT(onCurSubjTestDataChanged()));
    connect(SubjPool::instance(),SIGNAL(curTestDataChanged()),
        this,SLOT(onCurSubjTestDataChanged()));
}

void RecentSubjWidget::updateUi(){
    SubjInfo subjInfo;
    if(SubjPool::instance()->getCurSubjInfo(subjInfo)<0){
        _ui->_subjIdLineEdit->setText("");
        _ui->_subjNameLineEdit->setText("");
        _ui->_subjBirthdayLineEdit->setText("");
        _ui->_subjSexLineEdit->setText("");
        _ui->_subjTelNoLineEdit->setText("");
        _ui->_subjMobNoLineEdit->setText("");
        _ui->_subjEmailLineEdit->setText("");
        _ui->_subjAddrTextEdit->setText("");
    }else{
        _ui->_subjIdLineEdit->setText(subjInfo.getId());
        _ui->_subjNameLineEdit->setText(subjInfo.getName());
        _ui->_subjBirthdayLineEdit->setText(subjInfo.getBirthdayText());
        _ui->_subjSexLineEdit->setText(subjInfo.getSexText());
        _ui->_subjTelNoLineEdit->setText(subjInfo.getTelNo());
        _ui->_subjMobNoLineEdit->setText(subjInfo.getMobNo());
        _ui->_subjEmailLineEdit->setText(subjInfo.getEmail());
        _ui->_subjAddrTextEdit->setText(subjInfo.getAddr());
    }
    SubjPool::PtrCTestData testData=SubjPool::instance()->getCurTestData();
    if(testData.isNull()){
        _ui->_devModelLineEdit->setText("");
        _ui->_devSeriNumLineEdit->setText("");
        _ui->_sexLineEdit->setText("");
        _ui->_ageLineEdit->setText("");
        _ui->_heightLineEdit->setText("");
        _ui->_weightLineEdit->setText("");
        _ui->_activityLineEdit->setText("");
        _ui->_waistLineEdit->setText("");
        _ui->_hipLineEdit->setText("");
        _ui->_5kHzLineEdit->setText("");
        _ui->_50kHzLineEdit->setText("");
        _ui->_100kHzLineEdit->setText("");
        _ui->_200kHzLineEdit->setText("");
        _ui->_reacLineEdit->setText("");
        _ui->_reactLineEdit->setText("");
        _ui->_phaseAngleLineEdit->setText("");
    }else{
        _ui->_devModelLineEdit->setText(testData->getDevModelText());
        _ui->_devSeriNumLineEdit->setText(testData->getDevSeriNumText());
        _ui->_sexLineEdit->setText(testData->getSexText());
        _ui->_ageLineEdit->setText(testData->getAgeText());
        _ui->_heightLineEdit->setText(testData->getHeightText());
        _ui->_weightLineEdit->setText(testData->getWeightText());
        _ui->_activityLineEdit->setText(testData->getActivityText());
        _ui->_waistLineEdit->setText(testData->getWaistText());
        _ui->_hipLineEdit->setText(testData->getHipText());
        _ui->_5kHzLineEdit->setText(testData->getIz5kHzText());
        _ui->_50kHzLineEdit->setText(testData->getIz50kHzText());
        _ui->_100kHzLineEdit->setText(testData->getIz100kHzText());
        _ui->_200kHzLineEdit->setText(testData->getIz200kHzText());
        _ui->_reacLineEdit->setText(testData->getIr50kHzText());
        _ui->_reactLineEdit->setText(testData->getFx50kHzText());
        _ui->_phaseAngleLineEdit->setText(testData->getFpa50kHzText());
    }
}
