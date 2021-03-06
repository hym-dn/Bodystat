﻿#include"bodystat.h"
#include"../../../include/BodystatSDK.h"
#include<QMutexLocker>

BodyStat::BodyStat(QObject *parent/*=0*/)
    :Dev(parent)
    ,_lock()
    ,_name()
    ,_bda()
    ,_port()
    ,_isOpen(false)
    ,_isConnect(false)
    ,_model(0)
    ,_majorV(0)
    ,_minorV(0)
    ,_psoc2V(0)
    ,_eepromV(0)
    ,_seriNum(0)
    ,_calibDate(){
}

BodyStat::~BodyStat(){
}

QString BodyStat::getModelText(
    const unsigned int model){
    if(model<Bodystat::BSUnknown||
        model>Bodystat::BSMultiScanTouch){
        return(QString());
    }
    TCHAR modTxt[32]={0};
    if(Bodystat::NoError!=Bodystat::
        BSGetDeviceModelName(static_cast<
        Bodystat::BSDeviceModel>(model),
        modTxt,32)){
        return(QString());
    }else{
        return(QString::fromUtf16((ushort*)modTxt));
    }
}

void BodyStat::reset(){
    {
        QMutexLocker locker(&_lock);
        _name.clear();
        _bda.clear();
        _port.clear();
        _isOpen=false;
        _isConnect=false;
        _model=0;
        _majorV=0;
        _minorV=0;
        _psoc2V=0;
        _eepromV=0;
        _seriNum=0;
        _calibDate=QDate();
    }
    emit nameChanged();
    emit firmwareVChanged();
    emit seriNumChanged();
    emit calibDateChanged();
    emit modelChanged();
}

void BodyStat::setName(const QString &name){
    {
        QMutexLocker locker(&_lock);
        _name=name;
    }
    emit nameChanged();
}

const QString &BodyStat::getName() const{
    QMutexLocker locker(&_lock);
    return(_name);
}

void BodyStat::setBda(const QString &bda){
    QMutexLocker locker(&_lock);
    _bda=bda;
}

const QString &BodyStat::getBda() const{
    QMutexLocker locker(&_lock);
    return(_bda);
}

void BodyStat::setPort(const QString &port){
    QMutexLocker locker(&_lock);
    _port=port;
}

const QString &BodyStat::getPort() const{
    QMutexLocker locker(&_lock);
    return(_port);
}

void BodyStat::setModel(const unsigned int model){
    {
        QMutexLocker locker(&_lock);
        _model=model;
    }
    emit modelChanged();
}

unsigned int BodyStat::getModel() const{
    QMutexLocker locker(&_lock);
    return(_model);
}

QString BodyStat::getModelText() const{
    return(getModelText(getModel()));
}

void BodyStat::setIsOpen(const bool isOpen){
    QMutexLocker locker(&_lock);
    _isOpen=isOpen;
}

bool BodyStat::getIsOpen() const{
    QMutexLocker locker(&_lock);
    return(_isOpen);
}

void BodyStat::setIsConnect(const bool isConnect){
    QMutexLocker locker(&_lock);
    _isConnect=isConnect;
}

bool BodyStat::getIsConnect() const{
    QMutexLocker locker(&_lock);
    return(_isConnect);
}

void BodyStat::setFirmwareV(
    const unsigned char majorV,
    const unsigned char minorV,
    const unsigned char psoc2V,
    const unsigned char eepromV){
    {
        QMutexLocker locker(&_lock);
        _majorV=majorV;
        _minorV=minorV;
        _psoc2V=psoc2V;
        _eepromV=eepromV;
    }
    emit firmwareVChanged();
}

QString BodyStat::getFirmwareVText() const{
    QMutexLocker locker(&_lock);
    return(QString("%1.%2.%3.%4").arg(
        _majorV).arg(_minorV).arg(
        _psoc2V).arg(_eepromV));
}

void BodyStat::setSeriNum(const unsigned long seriNum){
    {
        QMutexLocker locker(&_lock);
        _seriNum=seriNum;
    }
    emit seriNumChanged();
}

unsigned long BodyStat::getSeriNum() const{
    QMutexLocker locker(&_lock);
    return(_seriNum);
}

void BodyStat::setCalibDate(const QDate &calibDate){
    {
        QMutexLocker locker(&_lock);
        _calibDate=calibDate;
    }
    emit calibDateChanged();
}

const QDate &BodyStat::getCalibDate() const{
    QMutexLocker locker(&_lock);
    return(_calibDate);
}

QString BodyStat::getCalibDateText() const{
    return(getCalibDate().toString("yyyy-MM-dd"));
}
