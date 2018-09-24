#include"fatrange.h"
#include<QObject>
#include<QVariant>
#include<QSqlQuery>

FatRange::FatRange()
    :FatRange(0,0,0,0,0){
}

FatRange::FatRange(const FatRange &range)
    :FatRange(range._ageLower,range._ageUpper,
        range._sex,range._referLower,
        range._referUpper){
}

FatRange::~FatRange(){
}

int FatRange::pull(QSqlQuery &query){
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

int FatRange::isValid(QString *errMsg/*=0*/) const{
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

int FatRange::isContain(
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

void FatRange::setAgeLower(const unsigned int lower){
    _ageLower=lower;
}

unsigned int FatRange::getAgeLower() const{
    return(_ageLower);
}

void FatRange::setAgeUpper(const unsigned int upper){
    _ageUpper=upper;
}

unsigned int FatRange::getAgeUpper() const{
    return(_ageUpper);
}

void FatRange::setSex(const unsigned int sex){
    _sex=sex;
}

unsigned int FatRange::getSex() const{
    return(_sex);
}

void FatRange::setReferLower(const unsigned int lower){
    _referLower=lower;
}

unsigned int FatRange::getReferLower() const{
    return(_referLower);
}

void FatRange::setReferUpper(const unsigned int upper){
    _referUpper=upper;
}

unsigned int FatRange::getReferUpper() const{
    return(_referUpper);
}

FatRange &FatRange::operator=(const FatRange &range){
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

FatRange::FatRange(
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
