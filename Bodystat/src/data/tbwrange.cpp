#include"tbwrange.h"
#include<QObject>
#include<QVariant>
#include<QSqlQuery>

TbwRange::TbwRange()
    :TbwRange(0,0,0,0,0){
}

TbwRange::TbwRange(const TbwRange &range)
    :TbwRange(range._ageLower,range._ageUpper,
        range._sex,range._referLower,
        range._referUpper){
}

TbwRange::~TbwRange(){
}

int TbwRange::pull(QSqlQuery &query){
    if(!query.isActive()||!query.isValid()){
        return(-1);
    }
    _ageLower=query.value(0).toUInt();
    _ageUpper=query.value(1).toUInt();
    _sex=query.value(2).toUInt();
    _referLower=query.value(3).toUInt();
    _referUpper=query.value(4).toUInt();
    if(isValid()<0){
        return(-2);
    }
    return(0);
}

int TbwRange::isValid(QString *errMsg/*=0*/) const{
    if(_ageLower>=_ageUpper){
        if(0!=errMsg){
            (*errMsg)=QObject::tr("年龄下限应该小于年龄上限！");
        }
        return(-1);
    }
    if(SEX_MALE!=_sex&&SEX_FEMAL!=_sex){
        if(0!=errMsg){
            (*errMsg)=QObject::tr("性别信息非法！");
        }
        return(-2);
    }
    if(_referLower>=_referUpper){
        if(0!=errMsg){
            (*errMsg)=QObject::tr("范围下限应该小于范围上限！");
        }
        return(-3);
    }
    return(0);
}

int TbwRange::isContain(
    const unsigned int age,const unsigned int sex) const{
    if(isValid()<0){
        return(-1);
    }
    if(sex!=_sex){
        return(-2);
    }
    if(age<_ageLower||age>_ageUpper){
        return(-3);
    }
    return(0);
}

void TbwRange::setAgeLower(const unsigned int lower){
    _ageLower=lower;
}

unsigned int TbwRange::getAgeLower() const{
    return(_ageLower);
}

QString TbwRange::getAgeLowerText() const{
    return(QString("%1").arg(getAgeLower()));
}

void TbwRange::setAgeUpper(const unsigned int upper){
    _ageUpper=upper;
}

unsigned int TbwRange::getAgeUpper() const{
    return(_ageUpper);
}

QString TbwRange::getAgeUpperText() const{
    return(QString("%1").arg(getAgeUpper()));
}

void TbwRange::setSex(const unsigned int sex){
    _sex=sex;
}

unsigned int TbwRange::getSex() const{
    return(_sex);
}

QString TbwRange::getSexText() const{
    switch(_sex){
    case SEX_MALE:
        return(QObject::tr("男"));
    case SEX_FEMAL:
        return(QObject::tr("女"));
    case SEX_OTHER:
        return(QObject::tr("其他"));
    default:
        return(QObject::tr("未知"));
    }
}

void TbwRange::setReferLower(const unsigned int lower){
    _referLower=lower;
}

unsigned int TbwRange::getReferLower() const{
    return(_referLower);
}

QString TbwRange::getReferLowerText() const{
    return(QString("%1").arg(getReferLower()));
}

void TbwRange::setReferUpper(const unsigned int upper){
    _referUpper=upper;
}

unsigned int TbwRange::getReferUpper() const{
    return(_referUpper);
}

QString TbwRange::getReferUpperText() const{
    return(QString("%1").arg(getReferUpper()));
}

TbwRange &TbwRange::operator=(const TbwRange &range){
    if(this==&range){
        return(*this);
    }else{
        _ageLower=range._ageLower;
        _ageUpper=range._ageUpper;
        _sex=range._sex;
        _referLower=range._referLower;
        _referUpper=range._referUpper;
        return(*this);
    }
}

TbwRange::TbwRange(
    const unsigned int ageLower,
    const unsigned int ageUpper,
    const unsigned int sex,
    const unsigned int referLower,
    const unsigned int referUpper)
    :_ageLower(ageLower)
    ,_ageUpper(ageUpper)
    ,_sex(sex)
    ,_referLower(referLower)
    ,_referUpper(referUpper){
}
