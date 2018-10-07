#include"teststatwidget.h"
#include"ui_teststatwidget.h"
#include"../data/testdatapool.h"
#include"teststatlistmodel.h"
#include"teststatsortfilterproxymodel.h"

TestStatWidget::TestStatWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::TestStatWidget){
    _ui->setupUi(this);
}

TestStatWidget::~TestStatWidget(){
    delete _ui;
}

void TestStatWidget::closeEvent(QCloseEvent *event){
    TestDataPool::instance()->clear_t();
    MdiSubWidget::closeEvent(event);
}

void TestStatWidget::onTestFilterLineEditTextChanged(const QString &){
    dynamic_cast<TestStatSortFilterProxyModel*>(
        _ui->_testStatListView->model())->setMatchString(text);
}

void TestStatWidget::onExportPushButtonClicked(bool){
}

void TestStatWidget::initUi(){
    // 文本编辑框
    connect(_ui->_testFilterLineEdit,SIGNAL(
        textChanged(const QString&)),this,
        SLOT(onTestFilterLineEditTextChanged(
        const QString&)));
    // 列表视图
    TestStatListModel *listModel=
        new TestStatListModel(_ui->_testStatListView);
    Q_ASSERT(0!=listModel);
    TestStatSortFilterProxyModel *filterModel=
        new TestStatSortFilterProxyModel(_ui->_testStatListView);
    Q_ASSERT(0!=filterModel);
    filterModel->setSourceModel(listModel);
    _ui->_testStatListView->setModel(filterModel);
    // 按钮
    connect(_ui->_exportPushButton,SIGNAL(clicked(bool)),
        this,SLOT(onExportPushButtonClicked(bool)));
}
