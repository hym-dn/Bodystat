#include"subject.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>

Subject::Subject()
    :_id()
    ,_name()
    ,_birthday()
    ,_sex(SEX_UNKNOWN)
    ,_telNo()
    ,_mobNo()
    ,_email()
    ,_addr()
    ,_entryDateTime()
    ,_modifyDateTime()
    ,_accessDateTime(){
}

Subject::Subject(const Subject &src)
    :_id(src._id)
    ,_name(src._name)
    ,_birthday(src._birthday)
    ,_sex(src._sex)
    ,_telNo(src._telNo)
    ,_mobNo(src._mobNo)
    ,_email(src._email)
    ,_addr(src._addr)
    ,_entryDateTime(src._entryDateTime)
    ,_modifyDateTime(src._modifyDateTime)
    ,_accessDateTime(src._accessDateTime){
}

Subject::~Subject(){
}

int Subject::pull(QSqlQuery &query){
    // 当前查询非法
    if(!query.isActive()||!query.isValid()){
        return(-1);
    }
    // 主题信息
    // ID
    _id=query.value(0).toString();
    // 姓名
    _name=query.value(1).toString();
    // 生日
    if(query.isNull(2)){
        _birthday=QDate();
    }else{
        _birthday=query.value(2).toDate();
    }
    // 性别
    bool ok=false;
    const unsigned int sex=
        query.value(3).toUInt(&ok);
    if(!ok){
        return(-2);
    }
    if(SEX_UNKNOWN!=sex&&SEX_MALE!=sex&&
        SEX_FEMALE!=sex&&SEX_OTHER!=sex){
        return(-3);
    }
    _sex=static_cast<Sex>(sex);
    // 联系方式
    // 电话
    if(query.isNull(4)){
        _telNo=QString();
    }else{
        _telNo=query.value(4).toString();
    }
    // 手机
    if(query.isNull(5)){
        _mobNo=QString();
    }else{
        _mobNo=query.value(5).toString();
    }
    // 邮件
    if(query.isNull(6)){
        _email=QString();
    }else{
        _email=query.value(6).toString();
    }
    // 地址
    if(query.isNull(7)){
        _addr=QString();
    }else{
        _addr=query.value(7).toString();
    }
    // 访问信息
    // 录入日期时间
    _entryDateTime=query.value(8).toDateTime();
    // 修改日期时间
    _modifyDateTime=query.value(9).toDateTime();
    // 访问日期时间
    _accessDateTime=query.value(10).toDateTime();
    // 当前主题非法
    if(isValid()<0){
        return(-4);
    }
    // 返回
    return(0);
}

int Subject::push(QSqlDatabase &db,const bool isAdd){
    // 数据库无效
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    // 当前项目有效
    Q_ASSERT(0==isValid());
    // 添加
    if(isAdd){
        // 检测ID是否冲突
        QString sql=QString(
            "SELECT COUNT(*) FROM Subject WHERE ID='%1';")
            .arg(_id);
        QSqlQuery query(db);
        if(!query.exec(sql)){
            return(-2);
        }
        // ID冲突
        if(query.next()&&query.value(0).toInt()>0){
            return(1);
        }
        // 空处理
        QString birthday="null";
        if(_birthday.isValid()){
            birthday=QString("'%1'").arg(
                getBirthdayText());
        }
        QString telNo="null";
        if(!_telNo.isEmpty()){
            telNo=QString("'%1'").arg(_telNo);
        }
        QString mobNo="null";
        if(!_mobNo.isEmpty()){
            mobNo=QString("'%1'").arg(_mobNo);
        }
        QString email="null";
        if(!_email.isEmpty()){
            email=QString("'%1'").arg(_email);
        }
        QString addr="null";
        if(!_addr.isEmpty()){
            addr=QString("'%1'").arg(_addr);
        }
        // 添加
        sql=QString("INSERT INTO Subject (ID,Name,Birthday,Sex,TelNo,"
            "MobNo,Email,Addr,EntryDateTime,ModifyDateTime,AccessDateTime) "
            "VALUES ('%1','%2',%3,%4,%5,%6,%7,%8,'%9','%10','%11')")
            .arg(_id).arg(_name).arg(birthday).arg(_sex).arg(telNo)
            .arg(mobNo).arg(email).arg(addr).arg(getEntryDateTimeText())
            .arg(getModifyDateTimeText()).arg(getAccessDateTimeText());
        if(!query.exec(sql)){
            return(-3);
        }
        // 返回
        return(0);
    }
    // 更新
    else{
        // 检测ID是否存在
        QString sql=QString(
            "SELECT COUNT(*) FROM Subject WHERE ID='%1';")
            .arg(_id);
        QSqlQuery query(db);
        if(!query.exec(sql)){
            return(-4);
        }
        // ID异常
        if(!query.next()||1!=query.value(0).toInt()){
            return(2);
        }
        // 空处理
        QString birthday="null";
        if(_birthday.isValid()){
            birthday=QString("'%1'").arg(
                getBirthdayText());
        }
        QString telNo="null";
        if(!_telNo.isEmpty()){
            telNo=QString("'%1'").arg(_telNo);
        }
        QString mobNo="null";
        if(!_mobNo.isEmpty()){
            mobNo=QString("'%1'").arg(_mobNo);
        }
        QString email="null";
        if(!_email.isEmpty()){
            email=QString("'%1'").arg(_email);
        }
        QString addr="null";
        if(!_addr.isEmpty()){
            addr=QString("'%1'").arg(_addr);
        }
        // 更新
        sql=QString("UPDATE Subject SET Name='%1',Birthday=%2,Sex=%3,"
            "TelNo=%4,MobNo=%5,Email=%6,Addr=%7,EntryDateTime='%8',"
            "ModifyDateTime='%9',AccessDateTime='%10' WHERE ID='%11';")
            .arg(_name).arg(birthday).arg(_sex).arg(telNo).arg(mobNo)
            .arg(email).arg(addr).arg(getEntryDateTimeText()).arg(
             getModifyDateTimeText()).arg(getAccessDateTimeText())
            .arg(_id);
        if(!query.exec(sql)){
            return(-5);
        }
        // 返回
        return(0);
    }
}

int Subject::isValid(QString *msg/*=0*/) const{
    // 主题信息
    // ID
    if(_id.isEmpty()){
        if(0!=msg){
            *msg=QObject::tr("【ID】不能为空！");
        }
        return(-1);
    }
    // 姓名
    else if(_name.isEmpty()){
        if(0!=msg){
            *msg=QObject::tr("【姓名】不能为空！");
        }
        return(-2);
    }
    // 生日
    // 性别
    else if(SEX_UNKNOWN==_sex){
        if(0!=msg){
            *msg=QObject::tr("【性别】不能为空！");
        }
        return(-3);
    }
    // 联系方式
    // 电话
    // 手机
    // 邮件
    // 地址
    // 访问信息
    // 录入日期
    else if(!_entryDateTime.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【录入时间】应是有效的日期时间！");
        }
        return(-4);
    }
    // 修改日期
    else if(!_modifyDateTime.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【修改时间】应是有效的日期时间！");
        }
        return(-5);
    }
    // 访问日期
    else if(!_accessDateTime.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【访问时间】应是有效的日期时间！");
        }
        return(-6);
    }
    // 返回
    else{
        return(0);
    }
}

void Subject::setId(const QString &id){
    _id=id;
}

const QString &Subject::getId() const{
    return(_id);
}

void Subject::setName(const QString &name){
    _name=name;
}

const QString &Subject::getName() const{
    return(_name);
}

void Subject::setBirthday(const QDate &birthday){
    _birthday=birthday;
}

const QDate &Subject::getBirthday() const{
    return(_birthday);
}

QString Subject::getBirthdayText() const{
    return(_birthday.toString("yyyy-MM-dd"));
}

void Subject::setSex(const Sex sex){
    _sex=sex;
}

Subject::Sex Subject::getSex() const{
    return(_sex);
}

QString Subject::getSexText() const{
    if(SEX_UNKNOWN==_sex){
        return(QString());
    }else if(SEX_MALE==_sex){
        return(QObject::tr("男"));
    }else if(SEX_FEMALE==_sex){
        return(QObject::tr("女"));
    }else{
        return(QObject::tr("其他"));
    }
}

void Subject::setTelNo(const QString &telNo){
    _telNo=telNo;
}

const QString &Subject::getTelNo() const{
    return(_telNo);
}

void Subject::setMobNo(const QString &mobNo){
    _mobNo=mobNo;
}

const QString &Subject::getMobNo() const{
    return(_mobNo);
}

void Subject::setEmail(const QString &email){
    _email=email;
}

const QString &Subject::getEmail() const{
    return(_email);
}

void Subject::setAddr(const QString &addr){
    _addr=addr;
}

const QString &Subject::getAddr() const{
    return(_addr);
}

void Subject::setEntryDateTime(const QDateTime &time){
    _entryDateTime=time;
}

const QDateTime &Subject::getEntryDateTime() const{
    return(_entryDateTime);
}

QString Subject::getEntryDateTimeText() const{
    if(_entryDateTime.isValid()){
        return(_entryDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    }else{
        return(QString());
    }
}

void Subject::setModifyDateTime(const QDateTime &time){
    _modifyDateTime=time;
}

const QDateTime &Subject::getModifyDateTime() const{
    return(_modifyDateTime);
}

QString Subject::getModifyDateTimeText() const{
    if(_modifyDateTime.isValid()){
        return(_modifyDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    }else{
        return(QString());
    }
}

void Subject::setAccessDateTime(const QDateTime &time){
    _accessDateTime=time;
}

const QDateTime &Subject::getAccessDateTime() const{
    return(_accessDateTime);
}

QString Subject::getAccessDateTimeText() const{
    if(_accessDateTime.isValid()){
        return(_accessDateTime.toString(
            "yyyy-MM-dd hh:mm:ss"));
    }else{
        return(QString());
    }
}

QString Subject::getBrief() const{
    if(isValid()<0){
        return("Not Valid Subject!");
    }else{
        return(getId()+";"+getName()+";"+
            getBirthdayText()+";"+getSexText());
    }
}

Subject &Subject::operator=(const Subject &src){
    _id=src._id;
    _name=src._name;
    _birthday=src._birthday;
    _sex=src._sex;
    _telNo=src._telNo;
    _mobNo=src._mobNo;
    _email=src._email;
    _addr=src._addr;
    _entryDateTime=src._entryDateTime;
    _modifyDateTime=src._modifyDateTime;
    _accessDateTime=src._accessDateTime;
    return(*this);
}
