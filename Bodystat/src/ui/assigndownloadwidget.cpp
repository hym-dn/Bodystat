#include"assigndownloadwidget.h"
#include"ui_assigndownloadwidget.h"
#include"testdatatablemodel.h"
#include"subjlistmodel.h"
#include"subjsortfilterproxymodel.h"
#include"../data/testdatapool.h"
#include"../db/dbmanager.h"
#include"../data/subjpool.h"
#include<QMessageBox>
#include<QSet>

AssignDownloadWidget::AssignDownloadWidget(
    QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::AssignDownloadWidget){
    _ui->setupUi(this);
    initUi();
}

AssignDownloadWidget::~AssignDownloadWidget(){
    delete _ui;
}

void AssignDownloadWidget::
    onFilterLineEditTextChanged(const QString &text){
    dynamic_cast<SubjSortFilterProxyModel*>(
        _ui->_subjListView->model())->setMatchString(text);
}

void AssignDownloadWidget::onAssignTestPushButtonClicked(bool){
    QModelIndexList idxList=_ui->_testDataTableView->
        selectionModel()->selectedRows();
    if(idxList.isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("您尚未选中测试数据！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_testDataTableView->setFocus();
        return;
    }
    QSet<int> tdIdxS;
    foreach(QModelIndex idx,idxList){
        if(!tdIdxS.contains(idx.row())){
            tdIdxS.insert(idx.row());
        }
    }
    idxList=_ui->_subjListView->selectionModel()->selectedRows();
    if(idxList.isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("您尚未选中主题！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_subjListView->setFocus();
        return;
    }
    const int subjIdx=idxList.at(0).row();
    QMessageBox msgBox(QMessageBox::Question,
        tr("询问"),tr("继续当前操作，将分配选中的测试数，是否继续？"));
    msgBox.setFont(font());
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,tr("是"));
    msgBox.setButtonText(QMessageBox::No,tr("否"));
    int res=msgBox.exec();
    if(QMessageBox::No==res){
        return;
    }
    if(TestDataPool::instance()->assign(
        DBManager::instance()->getDB(),subjIdx,tdIdxS)<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，分配测试数据失败，请重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_testDataTableView->setFocus();
        return;
    }
    dynamic_cast<TestDataTableModel*>(_ui->
        _testDataTableView->model())->update();
    SubjPool::instance()->setCurSubj(
        SubjPool::instance()->getCurSubjIdx());
}

void AssignDownloadWidget::initUi(){
    TestDataTableModel *model=new
        TestDataTableModel(_ui->_testDataTableView);
    _ui->_testDataTableView->setModel(model);
    _ui->_testDataTableView->horizontalHeader()->
        setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(_ui->_filterLineEdit,SIGNAL(
        textChanged(const QString&)),this,
        SLOT(onFilterLineEditTextChanged(
        const QString&)));
    SubjListModel *listModel=
        new SubjListModel(_ui->_subjListView);
    Q_ASSERT(0!=listModel);
    SubjSortFilterProxyModel *filterModel=
        new SubjSortFilterProxyModel(_ui->_subjListView);
    Q_ASSERT(0!=filterModel);
    filterModel->setSourceModel(listModel);
    _ui->_subjListView->setModel(filterModel);
    connect(_ui->_assignTestPushButton,SIGNAL(clicked(bool)),
        this,SLOT(onAssignTestPushButtonClicked(bool)));
}
