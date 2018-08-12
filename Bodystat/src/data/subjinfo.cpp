#include"subjinfo.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>

SubjInfo::SubjInfo()
    :_id()
    ,_name()
    ,_birthday()
    ,_sex(SEX_UNKNOWN)
    ,_telNo()
    ,_mobNo()
    ,_email()
    ,_addr()
    ,_entrDt()
    ,_modiDt()
    ,_accsDt(){
}

SubjInfo::SubjInfo(const SubjInfo &src)
    :_id(src._id)
    ,_name(src._name)
    ,_birthday(src._birthday)
    ,_sex(src._sex)
    ,_telNo(src._telNo)
    ,_mobNo(src._mobNo)
    ,_email(src._email)
    ,_addr(src._addr)
    ,_entrDt(src._entrDt)
    ,_modiDt(src._modiDt)
    ,_accsDt(src._accsDt){
}

SubjInfo::~SubjInfo(){
}

int SubjInfo::pull(QSqlQuery &query){
    if(!query.isActive()||!query.isValid()){
        return(-1);
    }
    _id=query.value(0).toString();
    _name=query.value(1).toString();
    if(query.isNull(2)){
        _birthday=QDate();
    }else{
        _birthday=query.value(2).toDate();
    }
    bool ok=false;
    const unsigned int uInt=
        query.value(3).toUInt(&ok);
    if(!ok){
        return(-2);
    }
    if(SEX_UNKNOWN!=uInt&&SEX_MALE!=uInt&&
        SEX_FEMALE!=uInt&&SEX_OTHER!=uInt){
        return(-3);
    }
    _sex=static_cast<Sex>(uInt);
    if(query.isNull(4)){
        _telNo=QString();
    }else{
        _telNo=query.value(4).toString();
    }
    if(query.isNull(5)){
        _mobNo=QString();
    }else{
        _mobNo=query.value(5).toString();
    }
    if(query.isNull(6)){
        _email=QString();
    }else{
        _email=query.value(6).toString();
    }
    if(query.isNull(7)){
        _addr=QString();
    }else{
        _addr=query.value(7).toString();
    }
    _entrDt=query.value(8).toDateTime();
    _modiDt=query.value(9).toDateTime();
    _accsDt=query.value(10).toDateTime();
    if(isValid()<0){
        return(-4);
    }
    return(0);
}

int SubjInfo::push(QSqlQuery &query,const bool isAdd) const{
    Q_ASSERT(isValid()>=0);
    QString birthday="null";
    if(_birthday.isValid()){
        birthday=QString("'%1'").arg(
            getBirthdayText());
    }
    QString telNo="null";
    if(!_telNo.isEmpty()){
        telNo=QString("'%1'").arg(getTelNo());
    }
    QString mobNo="null";
    if(!_mobNo.isEmpty()){
        mobNo=QString("'%1'").arg(getMobNo());
    }
    QString email="null";
    if(!_email.isEmpty()){
        email=QString("'%1'").arg(getEmail());
    }
    QString addr="null";
    if(!_addr.isEmpty()){
        addr=QString("'%1'").arg(getAddr());
    }
    if(isAdd){
        const QString sql(QString("INSERT INTO Subject "
            "(ID,Name,Birthday,Sex,TelNo,MobNo,Email,Addr,"
            "EntryDateTime,ModifyDateTime,AccessDateTime) "
            "VALUES ('%1','%2',%3,%4,%5,%6,%7,%8,'%9','%10',"
            "'%11');").arg(getId()).arg(getName()).arg(birthday)
            .arg(getSex()).arg(telNo).arg(mobNo).arg(email)
            .arg(addr).arg(getEntrDtText()).arg(getModiDtText())
            .arg(getAccsDtText()));
        if(!query.exec(sql)){
            return(-1);
        }
        return(0);
    }else{
        const QString sql(QString("UPDATE Subject SET Name='%1',"
            "Birthday=%2,Sex=%3,TelNo=%4,MobNo=%5,Email=%6,Addr=%7,"
            "EntryDateTime='%8',ModifyDateTime='%9',AccessDateTime='%10' "
            "WHERE ID='%11';").arg(getName()).arg(birthday).arg(getSex())
            .arg(telNo).arg(mobNo).arg(email).arg(addr).arg(getEntrDtText())
            .arg(getModiDtText()).arg(getAccsDtText()).arg(getId()));
        if(!query.exec(sql)){
            return(-2);
        }
        return(0);
    }
}

int SubjInfo::erase(QSqlQuery &query) const{
    Q_ASSERT(isValid()>=0);
    QString sql(QString("DELETE FROM Subject "
        "WHERE ID='%1';").arg(getId()));
    if(!query.exec(sql)){
        return(-1);
    }
    return(0);
}

int SubjInfo::isValid(QString *msg/*=0*/) const{
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
    else if(!_entrDt.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【录入时间】应是有效的日期时间！");
        }
        return(-4);
    }
    // 修改日期
    else if(!_modiDt.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【修改时间】应是有效的日期时间！");
        }
        return(-5);
    }
    // 访问日期
    else if(!_accsDt.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【访问时间】应是有效的日期时间！");
        }
        return(-6);
    }
    // 返回
    return(0);
}

void SubjInfo::setId(const QString &id){
    _id=id;
}

const QString &SubjInfo::getId() const{
    return(_id);
}

void SubjInfo::setName(const QString &name){
    _name=name;
}

const QString &SubjInfo::getName() const{
    return(_name);
}

void SubjInfo::setBirthday(const QDate &birthday){
    _birthday=birthday;
}

const QDate &SubjInfo::getBirthday() const{
    return(_birthday);
}

QString SubjInfo::getBirthdayText() const{
    return(getBirthday().toString("yyyy-MM-dd"));
}

void SubjInfo::setSex(const Sex sex){
    _sex=sex;
}

SubjInfo::Sex SubjInfo::getSex() const{
    return(_sex);
}

QString SubjInfo::getSexText() const{
    if(SEX_UNKNOWN==getSex()){
        return(QString());
    }else if(SEX_MALE==getSex()){
        return(QObject::tr("男"));
    }else if(SEX_FEMALE==getSex()){
        return(QObject::tr("女"));
    }else{
        return(QObject::tr("其他"));
    }
}

void SubjInfo::setTelNo(const QString &telNo){
    _telNo=telNo;
}

const QString &SubjInfo::getTelNo() const{
    return(_telNo);
}

void SubjInfo::setMobNo(const QString &mobNo){
    _mobNo=mobNo;
}

const QString &SubjInfo::getMobNo() const{
    return(_mobNo);
}

void SubjInfo::setEmail(const QString &email){
    _email=email;
}

const QString &SubjInfo::getEmail() const{
    return(_email);
}

void SubjInfo::setAddr(const QString &addr){
    _addr=addr;
}

const QString &SubjInfo::getAddr() const{
    return(_addr);
}

void SubjInfo::setEntrDt(const QDateTime &dt){
    _entrDt=dt;
}

const QDateTime &SubjInfo::getEntrDt() const{
    return(_entrDt);
}

QString SubjInfo::getEntrDtText() const{
    return(getEntrDt().toString("yyyy-MM-dd hh:mm:ss"));
}

void SubjInfo::setModiDt(const QDateTime &dt){
    _modiDt=dt;
}

const QDateTime &SubjInfo::getModiDt() const{
    return(_modiDt);
}

QString SubjInfo::getModiDtText() const{
    return(getModiDt().toString("yyyy-MM-dd hh:mm:ss"));
}

void SubjInfo::setAccsDt(const QDateTime &dt){
    _accsDt=dt;
}

const QDateTime &SubjInfo::getAccsDt() const{
    return(_accsDt);
}

QString SubjInfo::getAccsDtText() const{
    return(getAccsDt().toString("yyyy-MM-dd hh:mm:ss"));
}

QString SubjInfo::getBrief() const{
    return(getId()+";"+getName()+";"+
           getBirthdayText()+";"+getSexText());
}

SubjInfo &SubjInfo::operator=(const SubjInfo &src){
    _id=src._id;
    _name=src._name;
    _birthday=src._birthday;
    _sex=src._sex;
    _telNo=src._telNo;
    _mobNo=src._mobNo;
    _email=src._email;
    _addr=src._addr;
    _entrDt=src._entrDt;
    _modiDt=src._modiDt;
    _accsDt=src._accsDt;
    return(*this);
}
