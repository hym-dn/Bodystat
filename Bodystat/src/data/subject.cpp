#include"subject.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>

Subject::Subject()
    :_id()
    ,_name()
    ,_age(0)
    ,_sex(SEX_UNKNOWN)
    ,_height(0.0f)
    ,_weight(0.0f)
    ,_entryDateTime()
    ,_modifyDateTime()
    ,_accessDateTime(){
}

Subject::Subject(const Subject &src)
    :_id(src._id)
    ,_name(src._name)
    ,_age(src._age)
    ,_sex(src._sex)
    ,_height(src._height)
    ,_weight(src._weight)
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
    // ID
    _id=query.value(0).toString();
    // 姓名
    _name=query.value(1).toString();
    // 年龄
    bool ok=false;
    _age=query.value(2).toUInt(&ok);
    if(!ok){
        return(-2);
    }
    // 性别
    const unsigned int sex=
        query.value(3).toUInt(&ok);
    if(!ok){
        return(-3);
    }
    if(SEX_UNKNOWN!=sex&&SEX_MALE!=sex&&
        SEX_FEMALE!=sex&&SEX_OTHER!=sex){
        return(-4);
    }
    _sex=static_cast<Sex>(sex);
    // 身高
    _height=query.value(4).toFloat(&ok);
    if(!ok){
        return(-5);
    }
    // 体重
    _weight=query.value(5).toFloat(&ok);
    if(!ok){
        return(-6);
    }
    // 录入日期时间
    _entryDateTime=query.value(6).toDateTime();
    // 修改日期时间
    _modifyDateTime=query.value(7).toDateTime();
    // 访问日期时间
    _accessDateTime=query.value(8).toDateTime();
    // 当前主题非法
    if(isValid()<0){
        return(-7);
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
        // 添加
        sql=QString("INSERT INTO Subject (ID,Name,Age,Sex,Height,"
            "Weight,EntryDateTime,ModifyDateTime,AccessDateTime) "
            "VALUES ('%1','%2',%3,%4,%5,%6,'%7','%8','%9')").arg(_id)
            .arg(_name).arg(getAgeText()).arg(_sex).arg(getHeightText())
            .arg(getWeightText()).arg(getEntryDateTimeText()).arg(
            getModifyDateTimeText()).arg(getAccessDateTimeText());
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
        // 更新
        sql=QString("UPDATE Subject SET Name='%1',Age=%2,Sex=%3,"
            "Height=%4,Weight=%5,EntryDateTime='%6',ModifyDateTime='%7',"
            "AccessDateTime='%8' WHERE ID='%8';").arg(_name).arg(
            getAgeText()).arg(_sex).arg(getHeightText()).arg(
            getWeightText()).arg(getEntryDateTimeText()).arg(
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
    if(_id.isEmpty()){
        if(0!=msg){
            *msg=QObject::tr("【ID】不能为空！");
        }
        return(-1);
    }
    else if(_name.isEmpty()){
        if(0!=msg){
            *msg=QObject::tr("【姓名】不能为空！");
        }
        return(-2);
    }
    else if(_age>200){
        if(0!=msg){
            *msg=QObject::tr("【年龄】应是0~200之间的整数！");
        }
        return(-3);
    }
    else if(SEX_UNKNOWN==_sex){
        if(0!=msg){
            *msg=QObject::tr("【性别】不能为空！");
        }
        return(-4);
    }
    else if(_height<0.0||_height>999.999){
        if(0!=msg){
            *msg=QObject::tr("【身高】应是0~999.999之间的数！");
        }
        return(-5);
    }
    else if(_weight<0.0||_weight>999.999){
        if(0!=msg){
            *msg=QObject::tr("【体重】应是0~999.999之间的数！");
        }
        return(-6);
    }
    else if(!_entryDateTime.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【录入时间】应是有效的日期时间！");
        }
        return(-7);
    }
    else if(!_modifyDateTime.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【修改时间】应是有效的日期时间！");
        }
        return(-8);
    }
    else if(!_accessDateTime.isValid()){
        if(0!=msg){
            *msg=QObject::tr("【访问时间】应是有效的日期时间！");
        }
        return(-9);
    }
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

void Subject::setAge(const unsigned int age){
    _age=age;
}

unsigned int Subject::getAge() const{
    return(_age);
}

QString Subject::getAgeText() const{
    if(0==_age){
        return(QString());
    }else{
        return(QString("%1").arg(_age));
    }
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

void Subject::setHeight(const float height){
    _height=height;
}

float Subject::getHeight() const{
    return(_height);
}

QString Subject::getHeightText() const{
    if(_height<=0.0f){
        return(QString());
    }else{
        return(QString("%1").arg(_height,0,'f',3));
    }
}

void Subject::setWeight(const float weight){
    _weight=weight;
}

float Subject::getWeight() const{
    return(_weight);
}

QString Subject::getWeightText() const{
    if(_weight<=0.0f){
        return(QString());
    }else{
        return(QString("%1").arg(_weight,0,'f',3));
    }
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
        return(_accessDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    }else{
        return(QString());
    }
}

Subject &Subject::operator=(const Subject &src){
    _id=src._id;
    _name=src._name;
    _age=src._age;
    _sex=src._sex;
    _height=src._height;
    _weight=src._weight;
    _entryDateTime=src._entryDateTime;
    _modifyDateTime=src._modifyDateTime;
    _accessDateTime=src._accessDateTime;
    return(*this);
}
