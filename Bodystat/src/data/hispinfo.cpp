#include"hispinfo.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>
#include<QSqlDatabase>

HispInfo::HispInfo()
    :HispInfo("","",""){
}

HispInfo::HispInfo(const HispInfo &info)
    :HispInfo(info._hispName,info._sectName,info._compName){
}

HispInfo::~HispInfo(){
}

int HispInfo::pull(QSqlQuery &query){
    if(!query.isActive()||!query.isValid()){
        return(-1);
    }
    _hispName=query.value(0).toString();
    _sectName=query.value(1).toString();
    _compName=query.value(2).toString();
    if(isValid()<0){
        return(-2);
    }
    return(0);
}

int HispInfo::push(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(isValid()<0){
        return(-2);
    }
    QString sql=QString("UPDATE HispInfo SET "
        "HispName='%1',SectName='%2',CompName='%3';").arg(
        getHispName()).arg(getSectName()).arg(getCompName());
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-3);
    }
    return(0);
}

int HispInfo::isValid(QString *errMsg/*=0*/) const{
    if(_hispName.isEmpty()){
        if(0!=errMsg){
            (*errMsg)=QObject::tr("医院名称不能为空！");
        }
        return(-1);
    }
    if(_sectName.isEmpty()){
        if(0!=errMsg){
            (*errMsg)=QObject::tr("科室名称不能为空！");
        }
        return(-2);
    }
    return(0);
}

void HispInfo::setHispName(const QString &name){
    _hispName=name;
}

const QString &HispInfo::getHispName() const{
    return(_hispName);
}

void HispInfo::setSectName(const QString &name){
    _sectName=name;
}

const QString &HispInfo::getSectName() const{
    return(_sectName);
}

void HispInfo::setCompName(const QString &name){
    _compName=name;
}

const QString &HispInfo::getCompName() const{
    return(_compName);
}

HispInfo &HispInfo::operator=(const HispInfo &info){
    _hispName=info._hispName;
    _sectName=info._sectName;
    _compName=info._compName;
    return(*this);
}

HispInfo::HispInfo(const QString &hispName,
    const QString &sectName,const QString &compName)
    :_hispName(hispName)
    ,_sectName(sectName)
    ,_compName(compName){
}
