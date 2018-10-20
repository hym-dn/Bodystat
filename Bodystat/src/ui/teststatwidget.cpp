#include"teststatwidget.h"
#include"ui_teststatwidget.h"
#include"../data/testdata.h"
#include"../data/testdatapool.h"
#include"teststatlistmodel.h"
#include"teststatsortfilterproxymodel.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QFile>
#include<QTextStream>

TestStatWidget::TestStatWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::TestStatWidget){
    _ui->setupUi(this);
    initUi();
}

TestStatWidget::~TestStatWidget(){
    delete _ui;
}

void TestStatWidget::closeEvent(QCloseEvent *event){
    TestDataPool::instance()->clear_t();
    MdiSubWidget::closeEvent(event);
}

void TestStatWidget::onTestFilterLineEditTextChanged(const QString &text){
    dynamic_cast<TestStatSortFilterProxyModel*>(
        _ui->_testStatListView->model())->setMatchString(text);
}

void TestStatWidget::onExportPushButtonClicked(bool){
    QModelIndexList indxList=_ui->_testStatListView->
        selectionModel()->selectedIndexes();
    if(indxList.isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("您尚未选中测试数据！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    const QString fileName=QFileDialog::
        getSaveFileName(this,tr("保存"),"",
        tr("Export Files (*.csv)"));
    if(fileName.isEmpty()){
        return;
    }else{
        QFile file(fileName);
        if(!file.open(QFile::WriteOnly|QIODevice::Text)){
            QMessageBox msgBox(QMessageBox::Warning,
                tr("警报"),tr("对不起，文件创建失败，请重试!"));
            msgBox.setFont(font());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();
            return;
        }
        QTextStream out(&file);
        out<<tr("设备")<<","<<tr("设备号")<<","<<tr("测试日期")
          <<","<<tr("测试号")<<","<<tr("性别")<<","<<tr("年龄")<<","<<tr("身高")
          <<","<<tr("体重")<<","<<tr("活跃度")<<","<<tr("胸围")
          <<","<<tr("臀围")<<","<<"iz5kHz"<<","<<"iz50kHz"
          <<","<<"iz100kHz"<<","<<"iz200kHz"<<","<<"ir50kHz"
          <<","<<"fx50kHz"<<","<<"fpa50kHz"<<","<<"Fat Perc"
          <<","<<"Lean Perc"<<","<<"Lean Kg"<<","<<"Total Weight"
          <<","<<"DLW"<<","<<"DLW Perc"<<","<<"TBW Perc"<<","
          <<"TBW"<<","<<"ECW Perc"<<","<<"Ecw"<<","<<"ICW Perc"
          ","<<"ICW"<<","<<"BCM"<<","<<"Third Space"<<","<<
          "Third Space Perc"<<","<<"Nutrition"<<","<<"Illness"
         <<","<<"BMR"<<","<<"BMR Kg"<<","<<"Est Avg"<<","<<"BMI"
         <<","<<"BFMI"<<","<<"FFMI"<<","<<"Waist Hip"<<","<<"Wellness"
         <<","<<"ECW Legacy"<<","<<"TBW Legacy"<<","<<"OHY"<<","
         <<"Sk Muscle"<<","<<"Cal Sk Muscle"<<","<<"CM"<<","<<"REXT"
         <<","<<"RINT"<<","<<"FC"<<","<<"Alpha"<<"\n";
        for(int i=0;i<indxList.count();++i){
            QModelIndex indx=indxList.at(i);
            indx=dynamic_cast<TestStatSortFilterProxyModel*>(
                _ui->_testStatListView->model())->mapToSource(indx);
            TestDataPool::PtrToCData test=
                TestDataPool::instance()->getData_t(indx.row());
            out<<test->getBrief()<<"\n";
        }
        file.close();
        QMessageBox msgBox(QMessageBox::Information,
            tr("提示"),tr("文件导出成功！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
    }
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
