#include"subjwidget.h"
#include"ui_subjwidget.h"
#include"../data/subjinfo.h"
#include"../db/dbmanager.h"
#include"../data/subjpool.h"
#include<QMessageBox>

SubjWidget::SubjWidget(const Mode mode/*=MODE_NEW*/,
    const SubjInfo *subjInfo/*=0*/,QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_mode(mode)
    ,_subjInfo()
    ,_ui(new Ui::SubjWidget){
    if(0==subjInfo){
        _subjInfo.reset(new SubjInfo);
    }else{
        _subjInfo.reset(new SubjInfo(*subjInfo));
    }
    Q_ASSERT(!_subjInfo.isNull());
    _ui->setupUi(this);
    initUi();
    toUi();
}

SubjWidget::~SubjWidget(){
    delete _ui;
}

void SubjWidget::onSavePushButtonClicked(bool){
    if(MODE_DELETE==_mode){
        return;
    }
    QMessageBox msgBox(QMessageBox::Question,
        tr("询问"),tr("继续将保存当前主题，是否继续？"));
    msgBox.setFont(font());
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,tr("是"));
    msgBox.setButtonText(QMessageBox::No,tr("否"));
    int result=msgBox.exec();
    if(QMessageBox::No==result){
        return;
    }
    if(toSubjInfo(*_subjInfo)<0){
        return;
    }
    const int res=SubjPool::instance()->push(
        DBManager::instance()->getDB(),
        *_subjInfo,MODE_NEW==_mode);
    if(res<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，保存失败，请重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }else if(res>0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，【ID】已存在，保存失败！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }else{
        SubjPool::instance()->setCurSubj(_subjInfo->getId());
        QMessageBox msgBox(QMessageBox::Information,
            tr("提示"),tr("保存完成！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        close();
        return;
    }
}

void SubjWidget::onDeletePushButtonClicked(bool){
    // 询问
    QMessageBox msgBox(QMessageBox::Question,
        tr("询问"),tr("继续将彻底从数据库删除当前主题，是否继续？"));
    msgBox.setFont(font());
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,tr("是"));
    msgBox.setButtonText(QMessageBox::No,tr("否"));
    int result=msgBox.exec();
    if(QMessageBox::No==result){ // 否
        return;
    }
    // 擦除主题
    if(SubjPool::instance()->erase(
        DBManager::instance()->getDB(),
        _subjInfo->getId())<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起删除失败，请重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    SubjPool::instance()->setCurSubj(-1);
    // 关闭
    close();
}

void SubjWidget::onCancelPushButtonClicked(bool){
    /*
    // 询问
    QMessageBox msgBox(QMessageBox::Question,
        tr("询问"),tr("继续将退出当前对话框，是否继续？"));
    msgBox.setFont(font());
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,tr("是"));
    msgBox.setButtonText(QMessageBox::No,tr("否"));
    int result=msgBox.exec();
    if(QMessageBox::No==result){ // 否
        return;
    }
    */
    // 关闭
    close();
}

void SubjWidget::initUi(){
    _ui->_idLineEdit->setMaxLength(46);
    _ui->_idLineEdit->setValidator(
        new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$"),this));
    _ui->_idLineEdit->setDisabled(MODE_EDIT==_mode||MODE_DELETE==_mode);
    _ui->_nameLineEdit->setMaxLength(46);
    _ui->_nameLineEdit->setDisabled(MODE_DELETE==_mode);
    _ui->_birthdayDateEdit->setDisabled(MODE_DELETE==_mode);
    _ui->_sexComboBox->addItem(tr("男"),SubjInfo::SEX_MALE);
    _ui->_sexComboBox->addItem(tr("女"),SubjInfo::SEX_FEMALE);
    _ui->_sexComboBox->addItem(tr("其他"),SubjInfo::SEX_OTHER);
    _ui->_sexComboBox->setDisabled(MODE_DELETE==_mode);
    _ui->_telNoLineEdit->setMaxLength(46);
    _ui->_telNoLineEdit->setDisabled(MODE_DELETE==_mode);
    _ui->_mobNoLineEdit->setMaxLength(46);
    _ui->_mobNoLineEdit->setDisabled(MODE_DELETE==_mode);
    _ui->_emailLineEdit->setMaxLength(46);
    _ui->_emailLineEdit->setDisabled(MODE_DELETE==_mode);
    //_ui->_addrTextEdit->setMaxLength(255);
    _ui->_addrTextEdit->setDisabled(MODE_DELETE==_mode);
    _ui->_savePushButton->setDisabled(MODE_DELETE==_mode);
    if(MODE_DELETE==_mode){
        _ui->_savePushButton->hide();
    }else{
        _ui->_savePushButton->show();
    }
    connect(_ui->_savePushButton,SIGNAL(clicked(bool)),
        this,SLOT(onSavePushButtonClicked(bool)));
    _ui->_deletePushButton->setDisabled(MODE_DELETE!=_mode);
    if(MODE_DELETE==_mode){
        _ui->_deletePushButton->show();
    }else{
        _ui->_deletePushButton->hide();
    }
    connect(_ui->_deletePushButton,SIGNAL(clicked(bool)),
        this,SLOT(onDeletePushButtonClicked(bool)));
    connect(_ui->_cancelPushButton,SIGNAL(clicked(bool)),
        this,SLOT(onCancelPushButtonClicked(bool)));
}

void SubjWidget::toUi(){
    _ui->_idLineEdit->setText(_subjInfo->getId());
    _ui->_nameLineEdit->setText(_subjInfo->getName());
    _ui->_birthdayDateEdit->setDate(_subjInfo->getBirthday());
    if(SubjInfo::SEX_MALE==_subjInfo->getSex()){
        _ui->_sexComboBox->setCurrentIndex(0);
    }else if(SubjInfo::SEX_FEMALE==_subjInfo->getSex()){
        _ui->_sexComboBox->setCurrentIndex(1);
    }else if(SubjInfo::SEX_OTHER==_subjInfo->getSex()){
        _ui->_sexComboBox->setCurrentIndex(2);
    }else{
        _ui->_sexComboBox->setCurrentIndex(-1);
    }
    _ui->_telNoLineEdit->setText(_subjInfo->getTelNo());
    _ui->_mobNoLineEdit->setText(_subjInfo->getMobNo());
    _ui->_emailLineEdit->setText(_subjInfo->getEmail());
    _ui->_addrTextEdit->setText(_subjInfo->getAddr());
}

int SubjWidget::toSubjInfo(SubjInfo &subjInfo) const{
    if(MODE_DELETE==_mode){
        return(-1);
    }
    if(_ui->_idLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【ID】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_idLineEdit->setFocus();
        return(-2);
    }else{
        subjInfo.setId(_ui->_idLineEdit->text());
    }
    if(_ui->_nameLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【姓名】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_nameLineEdit->setFocus();
        return(-3);
    }else{
        subjInfo.setName(_ui->_nameLineEdit->text());
    }
    if(!_ui->_birthdayDateEdit->date().isValid()){
        subjInfo.setBirthday(QDate());
    }else{
        subjInfo.setBirthday(_ui->_birthdayDateEdit->date());
    }
    if(_ui->_sexComboBox->currentIndex()<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请选择【性别】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_sexComboBox->setFocus();
        return(-4);
    }else{
        subjInfo.setSex(static_cast<SubjInfo::Sex>(
            _ui->_sexComboBox->itemData(_ui->
            _sexComboBox->currentIndex()).toUInt()));
    }
    subjInfo.setTelNo(_ui->_telNoLineEdit->text());
    subjInfo.setMobNo(_ui->_mobNoLineEdit->text());
    subjInfo.setEmail(_ui->_emailLineEdit->text());
    subjInfo.setAddr(_ui->_addrTextEdit->toPlainText());
    if(MODE_NEW==_mode){
        const QDateTime curDt=QDateTime::currentDateTime();
        subjInfo.setEntrDt(curDt);
        subjInfo.setModiDt(curDt);
        subjInfo.setAccsDt(curDt);
    }else{
        const QDateTime curDt=QDateTime::currentDateTime();
        subjInfo.setModiDt(curDt); // 更新修改时间
        //subjInfo.setAccsDt(curDt);
    }
    QString errMsg;
    const int res=subjInfo.isValid(&errMsg);
    if(res<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),errMsg);
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        switch(res){
        case -1:
            _ui->_idLineEdit->setFocus();
            break;
        case -2:
            _ui->_nameLineEdit->setFocus();
            break;
        case -3:
            _ui->_sexComboBox->setFocus();
            break;
        default:
            break;
        }
        return(-5);
    }
    return(0);
}
