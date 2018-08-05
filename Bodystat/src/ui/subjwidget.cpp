#include"subjwidget.h"
#include"ui_subjwidget.h"
#include"../data/subject.h"
#include"../db/dbmanager.h"
#include"../data/subjpool.h"
#include<QMessageBox>

SubjWidget::SubjWidget(
    const Mode mode/*=MODE_NEW*/,
    QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_mode(mode)
    ,_subject(new Subject)
    ,_ui(new Ui::SubjWidget){
    _ui->setupUi(this);
    initUi();
    toUi();
}

SubjWidget::SubjWidget(const Mode mode,
    const Subject &subj,QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_mode(mode)
    ,_subject(new Subject(subj))
    ,_ui(new Ui::SubjWidget){
    _ui->setupUi(this);
    initUi();
    toUi();
}

SubjWidget::~SubjWidget(){
    delete _subject;
    delete _ui;
}

void SubjWidget::onSavePushButtonClicked(bool){
    // 询问
    QMessageBox msgBox(QMessageBox::Question,
        tr("询问"),tr("继续将保存当前主题，是否继续？"));
    msgBox.setFont(font());
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes,tr("是"));
    msgBox.setButtonText(QMessageBox::No,tr("否"));
    int result=msgBox.exec();
    if(QMessageBox::No==result){ // 否
        return;
    }
    // 将界面输入存储到主题中
    if(toSubject(*_subject)<0){
        return;
    }
    // 将主题推送到数据库中
    result=_subject->push(
        DBManager::instance()->getDB(),
        MODE_NEW==_mode);
    if(result<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("对不起，保存失败，请重试！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }else if(result>0){
        if(1==result){
            QMessageBox msgBox(QMessageBox::Warning,
                tr("警报"),tr("对不起，【ID】已存在，保存失败！"));
            msgBox.setFont(font());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();
            return;
        }else{
            QMessageBox msgBox(QMessageBox::Warning,
                tr("警报"),tr("对不起，检测到【ID】异常，保存失败！"));
            msgBox.setFont(font());
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
            msgBox.exec();
            return;
        }
    }else{
        SubjPool::instance()->setCurSubj(*_subject);
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
    // 从数据库删除主题
    QSqlDatabase db=DBManager::instance()->getDB();
    if(!db.isValid()||!db.isOpen()){
        QMessageBox msgBox(QMessageBox::Critical,
            tr("异常"),tr("数据库连接异常！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    QString sql=QString("DELETE FROM Subject WHERE ID='%1';")
        .arg(SubjPool::instance()->getCurSubj().getId());
    QSqlQuery query(db);
    if(!query.exec(sql)){
        QMessageBox msgBox(QMessageBox::Critical,
            tr("异常"),tr("数据库状态异常！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        return;
    }
    // 清除当前主题
    SubjPool::instance()->clearCurSubj();
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
    // 主题信息
    // ID
    _ui->_idLineEdit->setMaxLength(46);
    _ui->_idLineEdit->setValidator(
        new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$"),this));
    _ui->_idLineEdit->setDisabled(
        MODE_EDIT==_mode||MODE_DELETE==_mode);
    // Name
    _ui->_nameLineEdit->setMaxLength(46);
    _ui->_nameLineEdit->setDisabled(MODE_DELETE==_mode);
    // Birthday
    _ui->_birthdayDateEdit->setDisabled(MODE_DELETE==_mode);
    // Sex
    _ui->_sexComboBox->addItem(tr("男"),Subject::SEX_MALE);
    _ui->_sexComboBox->addItem(tr("女"),Subject::SEX_FEMALE);
    _ui->_sexComboBox->addItem(tr("其他"),Subject::SEX_OTHER);
    _ui->_sexComboBox->setDisabled(MODE_DELETE==_mode);
    // 联系信息
    // Tel No
    _ui->_telNoLineEdit->setMaxLength(46);
    _ui->_telNoLineEdit->setDisabled(MODE_DELETE==_mode);
    // Mob No
    _ui->_mobNoLineEdit->setMaxLength(46);
    _ui->_mobNoLineEdit->setDisabled(MODE_DELETE==_mode);
    // Email
    _ui->_emailLineEdit->setMaxLength(46);
    _ui->_emailLineEdit->setDisabled(MODE_DELETE==_mode);
    // Addr
    //_ui->_addrTextEdit->setMaxLength(255);
    _ui->_addrTextEdit->setDisabled(MODE_DELETE==_mode);
    // 按钮
    // Save
    _ui->_savePushButton->setDisabled(MODE_DELETE==_mode);
    if(MODE_DELETE==_mode){
        _ui->_savePushButton->hide();
    }else{
        _ui->_savePushButton->show();
    }
    connect(_ui->_savePushButton,SIGNAL(clicked(bool)),
        this,SLOT(onSavePushButtonClicked(bool)));
    // Delete
    _ui->_deletePushButton->setDisabled(MODE_DELETE!=_mode);
    if(MODE_DELETE==_mode){
        _ui->_deletePushButton->show();
    }else{
        _ui->_deletePushButton->hide();
    }
    connect(_ui->_deletePushButton,SIGNAL(clicked(bool)),
        this,SLOT(onDeletePushButtonClicked(bool)));
    // Cancel
    connect(_ui->_cancelPushButton,SIGNAL(clicked(bool)),
        this,SLOT(onCancelPushButtonClicked(bool)));
}

void SubjWidget::toUi(){
    // 主题信息
    // ID
    _ui->_idLineEdit->setText(_subject->getId());
    // Name
    _ui->_nameLineEdit->setText(_subject->getName());
    // birthday
    _ui->_birthdayDateEdit->setDate(_subject->getBirthday());
    // Sex
    if(Subject::SEX_MALE==_subject->getSex()){
        _ui->_sexComboBox->setCurrentIndex(0);
    }else if(Subject::SEX_FEMALE==_subject->getSex()){
        _ui->_sexComboBox->setCurrentIndex(1);
    }else if(Subject::SEX_OTHER==_subject->getSex()){
        _ui->_sexComboBox->setCurrentIndex(2);
    }else{
        _ui->_sexComboBox->setCurrentIndex(-1);
    }
    // 联系信息
    // Tel No
    _ui->_telNoLineEdit->setText(_subject->getTelNo());
    // Mob No
    _ui->_mobNoLineEdit->setText(_subject->getMobNo());
    // Email
    _ui->_emailLineEdit->setText(_subject->getEmail());
    // addr
    _ui->_addrTextEdit->setText(_subject->getAddr());
}

int SubjWidget::toSubject(Subject &subj) const{
    // 主题信息
    // ID
    if(_ui->_idLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【ID】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_idLineEdit->setFocus();
        return(-1);
    }else{
        subj.setId(_ui->_idLineEdit->text());
    }
    // Name
    if(_ui->_nameLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【姓名】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_nameLineEdit->setFocus();
        return(-2);
    }else{
        subj.setName(_ui->_nameLineEdit->text());
    }
    // Birthday
    if(!_ui->_birthdayDateEdit->date().isValid()){
        subj.setBirthday(QDate());
    }else{
        subj.setBirthday(_ui->_birthdayDateEdit->date());
    }
    // Sex
    if(_ui->_sexComboBox->currentIndex()<0){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请选择【性别】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_sexComboBox->setFocus();
        return(-3);
    }else{
        subj.setSex(static_cast<Subject::Sex>(
            _ui->_sexComboBox->itemData(_ui->_sexComboBox->
            currentIndex()).toUInt()));
    }
    // 联系信息
    // Tel No
    subj.setTelNo(_ui->_telNoLineEdit->text());
    // Mob No
    subj.setMobNo(_ui->_mobNoLineEdit->text());
    // Email
    subj.setEmail(_ui->_emailLineEdit->text());
    // Addr
    subj.setAddr(_ui->_addrTextEdit->toPlainText());
    // 访问信息
    // Entry Date Time & Modify Date Time
    if(MODE_NEW==_mode){
        const QDateTime curDateTime=QDateTime::currentDateTime();
        subj.setEntryDateTime(curDateTime);
        subj.setModifyDateTime(curDateTime);
        subj.setAccessDateTime(curDateTime);
    }else{
        const QDateTime curDateTime=QDateTime::currentDateTime();
        subj.setModifyDateTime(curDateTime);
        subj.setAccessDateTime(curDateTime);
    }
    // Subject
    QString errMsg;
    const int result=subj.isValid(&errMsg);
    if(result<0){
        // 提示
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),errMsg);
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        // 焦点
        switch(result){
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
        // 返回
        return(-4);
    }
    // 返回
    return(0);
}
