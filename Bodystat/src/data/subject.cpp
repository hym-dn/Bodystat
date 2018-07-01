#include"subject.h"
#include<QObject>

Subject::Subject()
    :_id()
    ,_name()
    ,_age(0)
    ,_sex(SEX_UNKNOWN)
    ,_height(0.0f)
    ,_weight(0.0f)
    ,_entryDateTime()
    ,_modifyDateTime(){
}

Subject::Subject(const Subject &src)
    :_id(src._id)
    ,_name(src._name)
    ,_age(src._age)
    ,_sex(src._sex)
    ,_height(src._height)
    ,_weight(src._weight)
    ,_entryDateTime(src._entryDateTime)
    ,_modifyDateTime(src._modifyDateTime){
}

Subject::~Subject(){
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
    }else{
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
    return(QString("%1").arg(_age));
}

void Subject::setSex(const Sex sex){
    _sex=sex;
}

Subject::Sex Subject::getSex() const{
    return(_sex);
}

void Subject::setHeight(const float height){
    _height=height;
}

float Subject::getHeight() const{
    return(_height);
}

QString Subject::getHeightText() const{
    return(QString("%1").arg(_height,0,'f',3));
}

void Subject::setWeight(const float weight){
    _weight=weight;
}

float Subject::getWeight() const{
    return(_weight);
}

QString Subject::getWeightText() const{
    return(QString("%1").arg(_weight,0,'f',3));
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

Subject &Subject::operator=(const Subject &src){
    _id=src._id;
    _name=src._name;
    _age=src._age;
    _sex=src._sex;
    _height=src._height;
    _weight=src._weight;
    _entryDateTime=src._entryDateTime;
    _modifyDateTime=src._modifyDateTime;
    return(*this);
}
