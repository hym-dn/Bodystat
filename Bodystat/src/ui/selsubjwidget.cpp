#include"selsubjwidget.h"
#include"ui_selsubjwidget.h"
#include"subjlistmodel.h"
#include"subjsortfilterproxymodel.h"
#include"../data/subjpool.h"
#include"../data/subject.h"
#include"../data/subjinfo.h"
#include"../db/dbmanager.h"
#include<QMessageBox>
#include<QDateTime>

SelSubjWidget::SelSubjWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::SelSubjWidget){
    _ui->setupUi(this);
    initUi();
}

SelSubjWidget::~SelSubjWidget(){
    delete _ui;
}

void SelSubjWidget::onFilterLineEditTextChanged(const QString &text){
    dynamic_cast<SubjSortFilterProxyModel*>(
        _ui->_subjListView->model())->setMatchString(text);
    clearSubjInfo();
}

void SelSubjWidget::onSubjListViewSelectionChanged(
    const QItemSelection&,const QItemSelection&){
    QModelIndexList indexList=_ui->_subjListView->
        selectionModel()->selectedIndexes();
    if(indexList.isEmpty()){
        clearSubjInfo();
    }else{
        QModelIndex subjIndex=((SubjSortFilterProxyModel*)((
            _ui->_subjListView)->model()))->mapToSource(
            indexList.at(0));
        showSubjInfo(SubjPool::instance()->
            get(subjIndex.row())->getSubjInfo());
    }
}

void SelSubjWidget::onSubjListViewDoubleClicked(
    const QModelIndex &index){
    QModelIndex subjIndex=((SubjSortFilterProxyModel*)((
        _ui->_subjListView)->model()))->mapToSource(index);
    updateCurSubjInfo(SubjPool::instance()->get(
        subjIndex.row())->getSubjInfo());
    close();
}

void SelSubjWidget::onSelSubjPushButtonClicked(bool){
    QModelIndexList indexList=_ui->_subjListView->
        selectionModel()->selectedIndexes();
    if(indexList.isEmpty()){
        QMessageBox msgBox(QMessageBox::Information,
            tr("提示"),tr("您尚未选中主题！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_subjListView->setFocus();
        return;
    }
    QModelIndex subjIndex=((SubjSortFilterProxyModel*)((
        _ui->_subjListView)->model()))->mapToSource(
        indexList.at(0));
    updateCurSubjInfo(SubjPool::instance()->get(
        subjIndex.row())->getSubjInfo());
    close();
}

void SelSubjWidget::initUi(){
    // 文本编辑框
    connect(_ui->_filterLineEdit,SIGNAL(
        textChanged(const QString&)),this,
        SLOT(onFilterLineEditTextChanged(
        const QString&)));
    // 列表视图
    SubjListModel *listModel=
        new SubjListModel(_ui->_subjListView);
    Q_ASSERT(0!=listModel);
    SubjSortFilterProxyModel *filterModel=
        new SubjSortFilterProxyModel(_ui->_subjListView);
    Q_ASSERT(0!=filterModel);
    filterModel->setSourceModel(listModel);
    _ui->_subjListView->setModel(filterModel);
    connect(_ui->_subjListView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection&,
        const QItemSelection&)),this,SLOT(
        onSubjListViewSelectionChanged(
        const QItemSelection&,const QItemSelection&)));
    connect(_ui->_subjListView,SIGNAL(doubleClicked(
        const QModelIndex&)),this,SLOT(
        onSubjListViewDoubleClicked(const QModelIndex&)));
    // 按钮
    connect(_ui->_selSubjPushButton,SIGNAL(clicked(bool)),
        this,SLOT(onSelSubjPushButtonClicked(bool)));
}

void SelSubjWidget::clearSubjInfo(){
    _ui->_idLineEdit->setText("");
    _ui->_nameLineEdit->setText("");
    _ui->_birthdayLineEdit->setText("");
    _ui->_sexLineEdit->setText("");
    _ui->_telNoLineEdit->setText("");
    _ui->_mobNoLineEdit->setText("");
    _ui->_emailLineEdit->setText("");
    _ui->_addrTextEdit->setText("");
}

void SelSubjWidget::showSubjInfo(const SubjInfo &subjInfo){
    _ui->_idLineEdit->setText(subjInfo.getId());
    _ui->_nameLineEdit->setText(subjInfo.getName());
    _ui->_birthdayLineEdit->setText(subjInfo.getBirthdayText());
    _ui->_sexLineEdit->setText(subjInfo.getSexText());
    _ui->_telNoLineEdit->setText(subjInfo.getTelNo());
    _ui->_mobNoLineEdit->setText(subjInfo.getMobNo());
    _ui->_emailLineEdit->setText(subjInfo.getEmail());
    _ui->_addrTextEdit->setText(subjInfo.getAddr());
}

void SelSubjWidget::updateCurSubjInfo(const SubjInfo &subjInfo){
    SubjPool::instance()->push(
        DBManager::instance()->getDB(),subjInfo,false);
    SubjPool::instance()->setCur(subjInfo.getId());
}
