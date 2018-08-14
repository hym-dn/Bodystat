#include"cursubjwidget.h"
#include"ui_cursubjwidget.h"
#include"../data/subjpool.h"
#include"../data/subject.h"
#include"../data/subjinfo.h"
#include"testdatalistmodel.h"

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

void CurSubjWidget::onSelectionChangedTestDataListView(
    const QItemSelection &selected,const QItemSelection &/*deselected*/){
    QModelIndexList idxList=selected.indexes();
    if(idxList.isEmpty()){
        SubjPool::instance()->setCurTestData(-1);
        return;
    }
    const QModelIndex &idx=idxList.at(0);
    if(!idx.isValid()){
        SubjPool::instance()->setCurTestData(-1);
        return;
    }
    SubjPool::instance()->setCurTestData(idx.row());
}

void CurSubjWidget::initUi(){
    TestDataListModel *listModel=
        new TestDataListModel(_ui->_testDataListView);
    Q_ASSERT(0!=listModel);
    _ui->_testDataListView->setModel(listModel);
    connect(SubjPool::instance(),
        SIGNAL(curSubjChanged()),this,
        SLOT(onCurSubjChanged()));
    connect(_ui->_testDataListView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&,
        const QItemSelection&)),this,SLOT(
        onSelectionChangedTestDataListView(
        const QItemSelection&,const QItemSelection&)));
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
    dynamic_cast<TestDataListModel*>(_ui->
        _testDataListView->model())->update();
}
