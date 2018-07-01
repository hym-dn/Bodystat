#include"subjwidget.h"
#include"ui_subjwidget.h"
#include"../data/subject.h"
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
}

SubjWidget::~SubjWidget(){
    delete _subject;
    delete _ui;
}

void SubjWidget::onSavePushButtonClicked(bool){
}

void SubjWidget::initUi(){
    // ID
    _ui->_idLineEdit->setMaxLength(46);
    _ui->_idLineEdit->setValidator(
        new QRegExpValidator(QRegExp(
        "[a-zA-Z0-9]+$")));
    _ui->_idLineEdit->setDisabled(MODE_EDIT==_mode);
    // Name
    _ui->_nameLineEdit->setMaxLength(46);
    // Age
    _ui->_ageLineEdit->setMaxLength(3);
    _ui->_ageLineEdit->setValidator(
        new QRegExpValidator(QRegExp(
        "[0-9]+$")));
    // Sex
    _ui->_sexComboBox->addItem(tr("男"),Subject::SEX_MALE);
    _ui->_sexComboBox->addItem(tr("女"),Subject::SEX_FEMALE);
    _ui->_sexComboBox->addItem(tr("其他"),Subject::SEX_OTHER);
    // Height
    _ui->_heightLineEdit->setMaxLength(7);
    _ui->_heightLineEdit->setValidator(
        new QRegExpValidator(QRegExp(
        "^\\d{1,3}(?:\\.\\d{1,3})?$")));
    // Weight
    _ui->_weightLineEdit->setMaxLength(7);
    _ui->_weightLineEdit->setValidator(
        new QRegExpValidator(QRegExp(
        "^\\d{1,3}(?:\\.\\d{1,3})?$")));
    // Save
    connect(_ui->_savePushButton,SIGNAL(clicked(bool)),
        this,SLOT(onSavePushButtonClicked(bool)));
}

void SubjWidget::toUi(){
    // ID
    _ui->_idLineEdit->setText(_subject->getId());
    // Name
    _ui->_nameLineEdit->setText(_subject->getName());
    // Age
    _ui->_ageLineEdit->setText(_subject->getAgeText());
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
    // Height
    _ui->_heightLineEdit->setText(_subject->getHeightText());
    // Weight
    _ui->_weightLineEdit->setText(_subject->getWeightText());
}

int SubjWidget::toSubject(Subject &subj) const{
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
    // Age
    if(_ui->_ageLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【年龄】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_ageLineEdit->setFocus();
        return(-3);
    }else{
        subj.setAge(_ui->_ageLineEdit->text().toUInt());
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
        return(-4);
    }else{
        subj.setSex(static_cast<Subject::Sex>(
            _ui->_sexComboBox->itemData(_ui->_sexComboBox->
            currentIndex()).toUInt()));
    }
    // Height
    if(_ui->_heightLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【身高】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_heightLineEdit->setFocus();
        return(-5);
    }else{
        subj.setHeight(_ui->_heightLineEdit->text().toFloat());
    }
    // Weight
    if(_ui->_weightLineEdit->text().isEmpty()){
        QMessageBox msgBox(QMessageBox::Warning,
            tr("警报"),tr("请输入【体重】！"));
        msgBox.setFont(font());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setButtonText(QMessageBox::Ok,tr("确定"));
        msgBox.exec();
        _ui->_weightLineEdit->setFocus();
        return(-6);
    }else{
        subj.setWeight(_ui->_weightLineEdit->text().toFloat());
    }
    // Entry Date Time & Modify Date Time
    if(MODE_NEW==_mode){
        const QDateTime curDateTime=QDateTime::currentDateTime();
        subj.setEntryDateTime(curDateTime);
        subj.setModifyDateTime(curDateTime);
    }else{
        const QDateTime curDateTime=QDateTime::currentDateTime();
        subj.setModifyDateTime(curDateTime);
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
            _ui->_ageLineEdit->setFocus();
            break;
        case -4:
            _ui->_sexComboBox->setFocus();
            break;
        case -5:
            _ui->_heightLineEdit->setFocus();
            break;
        case -6:
            _ui->_weightLineEdit->setFocus();
            break;
        default:
            break;
        }
        // 返回
        return(-7);
    }
    // 返回
    return(0);
}
