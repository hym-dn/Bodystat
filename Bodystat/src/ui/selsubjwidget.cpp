#include"selsubjwidget.h"
#include"ui_selsubjwidget.h"
#include"subjlistmodel.h"
#include"subjsortfilterproxymodel.h"
#include"../data/subjpool.h"
#include"../data/subject.h"
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
    updateCurSubj(SubjPool::instance()->getSubj(subjIndex.row()));
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
    updateCurSubj(SubjPool::instance()->getSubj(subjIndex.row()));
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
    _ui->_birthdayLineEdit->setText("");
    _ui->_sexLineEdit->setText("");
}

void SelSubjWidget::showSubj(const Subject &subj){
    // 主题信息
    _ui->_idLineEdit->setText(subj.getId());
    _ui->_nameLineEdit->setText(subj.getName());
    _ui->_birthdayLineEdit->setText(subj.getBirthdayText());
    _ui->_sexLineEdit->setText(subj.getSexText());
    // 联系信息
    _ui->_telNoLineEdit->setText(subj.getTelNo());
    _ui->_mobNoLineEdit->setText(subj.getMobNo());
    _ui->_emailLineEdit->setText(subj.getEmail());
    _ui->_addrTextEdit->setText(subj.getAddr());
}

void SelSubjWidget::updateCurSubj(const Subject &subj){
    QSqlDatabase db=DBManager::instance()->getDB();
    if(db.isValid()&&db.isOpen()){
        QString sql=QString("UPDATE Subject SET AccessDateTime='%1' "
            "WHERE ID='%2';").arg(QDateTime::currentDateTime().toString(
            "yyyy-MM-dd hh:mm:ss")).arg(subj.getId());
        QSqlQuery query(db);
        query.exec(sql);
    }
    SubjPool::instance()->setCurSubj(subj);
}
