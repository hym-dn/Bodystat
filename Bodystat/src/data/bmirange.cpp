#include"bmirange.h"
#include"testdata.h"
#include<QObject>
#include<QVariant>
#include<QSqlQuery>

BmiRange::BmiRange()
    :BmiRange(0,0,0,0.0f,0.0f){
}

BmiRange::BmiRange(const BmiRange &range)
    :BmiRange(range._ageLower,range._ageUpper,
        range._sex,range._referLower,
        range._referUpper){
}

BmiRange::~BmiRange(){
}

int BmiRange::pull(QSqlQuery &query){
    if(!query.isActive()||!query.isValid()){
        return(-1);
    }
    _ageLower=query.value(0).toUInt();
    _ageUpper=query.value(1).toUInt();
    _sex=query.value(2).toUInt();
    _referLower=query.value(3).toFloat();
    _referUpper=query.value(4).toFloat();
    if(isValid()<0){
        return(-2);
    }
    return(0);
}

int BmiRange::isValid(QString *errMsg/*=0*/) const{
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

int BmiRange::isContain(
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

void BmiRange::setAgeLower(const unsigned int lower){
    _ageLower=lower;
}

unsigned int BmiRange::getAgeLower() const{
    return(_ageLower);
}

QString BmiRange::getAgeLowerText() const{
    return(QString("%1").arg(getAgeLower()));
}

void BmiRange::setAgeUpper(const unsigned int upper){
    _ageUpper=upper;
}

unsigned int BmiRange::getAgeUpper() const{
    return(_ageUpper);
}

QString BmiRange::getAgeUpperText() const{
    return(QString("%1").arg(getAgeUpper()));
}

void BmiRange::setSex(const unsigned int sex){
    _sex=sex;
}

unsigned int BmiRange::getSex() const{
    return(_sex);
}

QString BmiRange::getSexText() const{
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

void BmiRange::setReferLower(const float lower){
    _referLower=lower;
}

float BmiRange::getReferLower() const{
    return(_referLower);
}

QString BmiRange::getReferLowerText() const{
    return(QString("%1").arg(getReferLower(),
        0,'f',TestData::PREC_LIMIT));
}

void BmiRange::setReferUpper(const float upper){
    _referUpper=upper;
}

float BmiRange::getReferUpper() const{
    return(_referUpper);
}

QString BmiRange::getReferUpperText() const{
    return(QString("%1").arg(getReferUpper(),
        0,'f',TestData::PREC_LIMIT));
}

BmiRange &BmiRange::operator=(const BmiRange &range){
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

BmiRange::BmiRange(const unsigned int ageLower,
    const unsigned int ageUpper,
    const unsigned int sex,
    const float referLower,
    const float referUpper)
    :_ageLower(ageLower)
    ,_ageUpper(ageUpper)
    ,_sex(sex)
    ,_referLower(referLower)
    ,_referUpper(referUpper){
}
