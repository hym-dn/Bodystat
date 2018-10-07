#include"sysinfopool.h"
#include"../comm/singleton.h"
#include"hispinfo.h"
#include"fatparam.h"
#include"tbwparam.h"
#include"leanparam.h"
#include"bmiparam.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMutexLocker>

SysInfoPool::~SysInfoPool(){
}

SysInfoPool *SysInfoPool::instance(){
    return(Singleton<SysInfoPool>::instance());
}

int SysInfoPool::pull(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    QString sql("SELECT HispName,SectName FROM HispInfo;");
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    if(!query.next()){
        return(-3);
    }
    PtrHispInfo hispInfo(new HispInfo);
    if(hispInfo.isNull()){
        return(-4);
    }
    if(hispInfo->pull(query)<0){
        return(-5);
    }
    sql="SELECT AgeLower,AgeUpper,Sex,ReferLower,ReferUpper "
        "FROM FatParam ORDER BY Sex ASC,AgeLower ASC,AgeUpper "
        "ASC;";
    if(!query.exec(sql)){
        return(-6);
    }
    PtrFatParam fatParam(new FatParam);
    if(fatParam.isNull()){
        return(-7);
    }
    if(fatParam->pull(query)<0){
        return(-8);
    }
    sql="SELECT AgeLower,AgeUpper,Sex,ReferLower,ReferUpper "
        "FROM TbwParam ORDER BY Sex ASC,AgeLower ASC,AgeUpper "
        "ASC;";
    if(!query.exec(sql)){
        return(-9);
    }
    PtrTbwParam tbwParam(new TbwParam);
    if(tbwParam.isNull()){
        return(-10);
    }
    if(tbwParam->pull(query)<0){
        return(-11);
    }
    sql="SELECT AgeLower,AgeUpper,Sex,ReferLower,ReferUpper "
        "FROM LeanParam ORDER BY Sex ASC,AgeLower ASC,AgeUpper "
        "ASC;";
    if(!query.exec(sql)){
        return(-12);
    }
    PtrLeanParam leanParam(new LeanParam);
    if(leanParam.isNull()){
        return(-13);
    }
    if(leanParam->pull(query)<0){
        return(-14);
    }
    sql="SELECT AgeLower,AgeUpper,Sex,ReferLower,ReferUpper "
        "FROM BmiParam ORDER BY Sex ASC,AgeLower ASC,AgeUpper "
        "ASC;";
    if(!query.exec(sql)){
        return(-15);
    }
    PtrBmiParam bmiParam(new BmiParam);
    if(bmiParam.isNull()){
        return(-16);
    }
    if(bmiParam->pull(query)<0){
        return(-17);
    }
    QMutexLocker locker(&_lock);
    _hispInfo=hispInfo;
    _fatParam=fatParam;
    _tbwParam=tbwParam;
    _leanParam=leanParam;
    _bmiParam=bmiParam;
    return(0);
}

int SysInfoPool::push(PtrHispInfo &hispInfo,QSqlDatabase &db){
    if(hispInfo.isNull()){
        return(-1);
    }
    if(hispInfo->push(db)<0){
        return(-2);
    }
    QMutexLocker locker(&_lock);
    _hispInfo=hispInfo;
    return(0);
}

SysInfoPool::PtrCHispInfo SysInfoPool::getHispInfo() const{
    QMutexLocker locker(&_lock);
    return(_hispInfo);
}

QString SysInfoPool::getTbwRangeText(
    const unsigned int age,const unsigned int sex) const{
    QMutexLocker locker(&_lock);
    return(_tbwParam->getRangeText(age,sex));
}

QString SysInfoPool::getLeanRangeText(
    const unsigned int age,const unsigned int sex) const{
    QMutexLocker locker(&_lock);
    return(_leanParam->getRangeText(age,sex));
}

QString SysInfoPool::getBmiRangeText(
    const unsigned int age,const unsigned int sex) const{
    QMutexLocker locker(&_lock);
    return(_bmiParam->getRangeText(age,sex));
}

int SysInfoPool::getFatRange(const unsigned int age,
    const unsigned int sex,float &referLower,
    float &referUpper) const{
    QMutexLocker locker(&_lock);
    return(_fatParam->getRange(age,sex,referLower,referUpper));
}

QString SysInfoPool::getFatRangeText(
    const unsigned int age,const unsigned int sex) const{
    QMutexLocker locker(&_lock);
    return(_fatParam->getRangeText(age,sex));
}

SysInfoPool::SysInfoPool(QObject *parent)
    :QObject(parent)
    ,_lock()
    ,_hispInfo(new HispInfo)
    ,_fatParam(new FatParam)
    ,_tbwParam(new TbwParam)
    ,_leanParam(new LeanParam)
    ,_bmiParam(new BmiParam){
}
