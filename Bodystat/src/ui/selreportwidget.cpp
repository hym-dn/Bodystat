#include"selreportwidget.h"
#include"ui_selreportwidget.h"
#include"../ui/testdatalistmodel.h"
#include"waitdialog.h"
#include"../task/reporttask.h"
#include<QMessageBox>

SelReportWidget::SelReportWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::SelReportWidget){
    _ui->setupUi(this);
    initUi();
}

SelReportWidget::~SelReportWidget(){
    delete _ui;
}

void SelReportWidget::onOkPushButtonClicked(bool){
    QModelIndexList idxList=_ui->_selTestReportListView->
        selectionModel()->selectedRows();
    if(idxList.isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("您尚未选中测试数据！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_selTestReportListView->setFocus();
        return;
    }
    QVector<int> tdIdxV;
    foreach(QModelIndex idx,idxList){
        if(!tdIdxV.contains(idx.row())){
            tdIdxV.push_back(idx.row());
        }
    }
    if(tdIdxV.count()>4){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("选中的测试数据不能超过4项！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_selTestReportListView->setFocus();
        return;
    }
    WaitDialog::PtrTask task(new ReportTask(tdIdxV));
    Q_ASSERT(!task.isNull());
    WaitDialog dlg(task);
    if(dlg.exec()<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，报告生成失败！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    emit printPreview();
}

void SelReportWidget::initUi(){
    TestDataListModel *listModel=
        new TestDataListModel(_ui->_selTestReportListView);
    Q_ASSERT(0!=listModel);
    _ui->_selTestReportListView->setModel(listModel);
    connect(_ui->_okPushButton,SIGNAL(clicked(bool)),
        this,SLOT(onOkPushButtonClicked(bool)));
}
