#include"downloaddatawidget.h"
#include"ui_downloaddatawidget.h"
#include"testdatatablemodel.h"
#include"../dev/bluetooth.h"
#include"../dev/bodystat.h"
#include"../dev/devpool.h"
#include<QMovie>
#include<QMessageBox>
#include<QCloseEvent>

DownloadDataWidget::DownloadDataWidget(
    QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_task(TASK_NONE)
    ,_ui(new Ui::DownloadDataWidget){
    _ui->setupUi(this);
    initUi();
    _task=TASK_DOWNLOAD;
    DevPool::instance()->getBluetooth()->
        downloadTestData(DevPool::instance()
        ->getBodyStat());
}

DownloadDataWidget::~DownloadDataWidget(){
    delete _ui;
}

void DownloadDataWidget::closeEvent(QCloseEvent *event){
    if(TASK_NONE==_task){
        MdiSubWidget::closeEvent(event);
    }else{
        QMessageBox msgBox(
            QMessageBox::Information,tr("提示"),
            tr("任务正在执行，不能退出，稍后重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        event->ignore();
    }
}

void DownloadDataWidget::onBtTaskDone(
    const unsigned int /*id*/,const unsigned int err){
    // 重置当前任务
    _task=TASK_NONE;
    // 如果出错
    if(Bluetooth::TASK_ERR_NONE!=err){
        QMessageBox msgBox(
            QMessageBox::Warning,tr("警报"),
            Bluetooth::getTaskText(err));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
    }
    // 使能按钮
    _ui->_openTestDialogPushButton->setDisabled(false);
    // 隐藏进度条
    _ui->_progressLabel->hide();
    // 更新测试数据列表
    dynamic_cast<TestDataTableModel*>(_ui->
        _testDataTableView->model())->update();
}

void DownloadDataWidget::onOpenTestDialogPushButton(bool){
    emit showAssignDownloadWidget(true);
}

void DownloadDataWidget::initUi(){
    layout()->setSizeConstraint(
        QLayout::SetFixedSize);
    _ui->_promptLabel->setPixmap(
        QPixmap(":rc/prompt.png"));
    _ui->_devLabel->setPixmap(
        QPixmap(":rc/Quadscan4000.bmp"));
    QMovie *movie=new QMovie(":rc/progress.gif",
        QByteArray(),_ui->_progressLabel);
    _ui->_progressLabel->setMovie(movie);
    movie->start();
    TestDataTableModel *model=new
        TestDataTableModel(_ui->_testDataTableView);
    _ui->_testDataTableView->setModel(model);
    _ui->_testDataTableView->horizontalHeader()->
        setSectionResizeMode(QHeaderView::ResizeToContents);
    _ui->_openTestDialogPushButton->setDisabled(true);
    connect(DevPool::instance()->getBluetooth(),
        SIGNAL(taskDone(const unsigned int,
        const unsigned int)),this,SLOT(
        onBtTaskDone(const unsigned int,
        const unsigned int)));
    connect(_ui->_openTestDialogPushButton,
        SIGNAL(clicked(bool)),this,SLOT(
        onOpenTestDialogPushButton(bool)));
}
