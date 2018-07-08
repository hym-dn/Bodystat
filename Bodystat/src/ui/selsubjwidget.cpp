#include"selsubjwidget.h"
#include"ui_selsubjwidget.h"
#include"subjlistmodel.h"
#include"subjsortfilterproxymodel.h"
#include"../data/subjpool.h"
#include"../data/subject.h"
#include<QMessageBox>

SelSubjWidget::SelSubjWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::SelSubjWidget){
    _ui->setupUi(this);
    initUi();
}

SelSubjWidget::~SelSubjWidget(){
    delete _ui;
}

void SelSubjWidget::closeEvent(QCloseEvent *event){
    SubjPool::instance()->clearSubjV();
    MdiSubWidget::closeEvent(event);
}

void SelSubjWidget::onFilterLineEditTextChanged(const QString &text){
    dynamic_cast<SubjSortFilterProxyModel*>(_ui->_subjListView->
        model())->setMatchString(text);
    clearSubj();
}

void SelSubjWidget::onSubjListViewSelectionChanged(
    const QItemSelection&,const QItemSelection&){
    QModelIndexList indexList=_ui->_subjListView->
        selectionModel()->selectedIndexes();
    if(indexList.isEmpty()){
        clearSubj();
    }else{
        QModelIndex subjIndex=((SubjSortFilterProxyModel*)((
            _ui->_subjListView)->model()))->mapToSource(
            indexList.at(0));
        showSubj(SubjPool::instance()->getSubj(subjIndex.row()));
    }
}

void SelSubjWidget::onSubjListViewDoubleClicked(
    const QModelIndex &index){
    QModelIndex subjIndex=((SubjSortFilterProxyModel*)((
        _ui->_subjListView)->model()))->mapToSource(index);
    SubjPool::instance()->setCurSubj(SubjPool::instance()
        ->getSubj(subjIndex.row()));
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
    SubjPool::instance()->setCurSubj(SubjPool::instance()
        ->getSubj(subjIndex.row()));
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

void SelSubjWidget::clearSubj(){
    _ui->_idLineEdit->setText("");
    _ui->_nameLineEdit->setText("");
    _ui->_ageLineEdit->setText("");
    _ui->_sexLineEdit->setText("");
    _ui->_heightLineEdit->setText("");
    _ui->_weightLineEdit->setText("");
}

void SelSubjWidget::showSubj(const Subject &subj){
    _ui->_idLineEdit->setText(subj.getId());
    _ui->_nameLineEdit->setText(subj.getName());
    _ui->_ageLineEdit->setText(subj.getAgeText());
    _ui->_sexLineEdit->setText(subj.getSexText());
    _ui->_heightLineEdit->setText(subj.getHeightText());
    _ui->_weightLineEdit->setText(subj.getWeightText());
}
