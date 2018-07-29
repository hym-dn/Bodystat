﻿#include"bluetooth.h"
#include"../../../include/BodystatSDK.h"
#include"bodystat.h"
#include<QMutexLocker>
#include<QDateTime>

Bluetooth::Bluetooth(QObject *parent/*=0*/)
    :Dev(parent)
    ,_thread()
    ,_lock()
    ,_drivInfo(){
    moveToThread(&_thread);
    _thread.start();
}

Bluetooth::~Bluetooth(){
    _thread.quit();
    _thread.wait();
}

const QString &Bluetooth::getDrivInfo() const{
    QMutexLocker locker(&_lock);
    return(_drivInfo);
}

void Bluetooth::onTask(
    const unsigned int id,BodyStat &bodyStat){
    // 连接设备
    if(TASK_ID_CON_DEV==id){
        // 蓝牙驱动尚未安装
        if(!Bodystat::BSIsDeviceInstallInProgress(0)){
            emit taskDone(id,TASK_ERR_DIRV_INVAL);
            return;
        }
        // 蓝牙设备无效
        if(!Bodystat::BSIsBTAvailable()){
            emit taskDone(id,TASK_ERR_DEV_INVAL);
            return;
        }
        // 蓝牙驱动信息
        setDrivInfo("");
        TCHAR dirvInfo[1024]={0};
        if(!Bodystat::BSGetBTStackInfo(dirvInfo,1024)){
            emit taskDone(id,TASK_ERR_GET_DIRV_INFO_FAILED);
            return;
        }
        setDrivInfo(QString::fromUtf16((ushort*)dirvInfo));
        // 断开连接
        Bodystat::BSCloseComport();
        // 擦除配对
        static unsigned short timeout=7;
        if(!Bodystat::BSUnAuthenticateBTDevices(1,0,timeout)){
            emit taskDone(id,TASK_ERR_UNAU_FALIED);
            return;
        }
        // 搜索设备
        int newDev=0;
        int authDev=0;
        if(!Bodystat::BSSearchBTDevices(
            newDev,authDev,1,0,timeout)){ // 失败
            emit taskDone(id,TASK_ERR_FIND_DEV_FAILED);
            return;
        }else if(newDev<=0){ // 无设备
            timeout=min(timeout*2,45);
            emit taskDone(id,TASK_ERR_NO_DEV);
            return;
        }
        // Bodystat设备配对
        if(!Bodystat::BSAuthenticateBTDevice(0,timeout)){
            emit taskDone(id,TASK_ERR_AUTH_FAILED);
            return;
        }
        // 获取设备信息
        TCHAR devName[512]={0};
        TCHAR bda[18]={0};
        TCHAR port[256]={0};
        bodyStat.reset();
        if(!Bodystat::BSGetBTBodystatDevice(
            devName,512,bda,18,port,256,timeout)){
            emit taskDone(id,TASK_ERR_GET_DEV_INFO_FAILED);
            return;
        }
        bodyStat.setName(QString::fromUtf16((ushort*)devName));
        bodyStat.setBda(QString::fromUtf16((ushort*)bda));
        bodyStat.setPort(QString::fromUtf16((ushort*)port));
        // 连接设备
        if(Bodystat::NoError!=Bodystat::BSOpenComport(port,256)){
            emit taskDone(id,TASK_ERR_OPEN_PORT_FAILED);
            return;
        }
        bodyStat.setIsOpen(true);
        if(Bodystat::NoError!=Bodystat::BSConnect()){
            emit taskDone(id,TASK_ERR_CONN_DEV_FAILED);
            return;
        }
        bodyStat.setIsConnect(true);
        // 读取设备模型、固件版本
        Bodystat::BSDeviceModel model=Bodystat::BSUnknown;
        unsigned char majorV=0;
        unsigned char minorV=0;
        unsigned char psoc2V=0;
        unsigned char eepromV=0;
        unsigned char bluthV=0;
        if(Bodystat::NoError!=Bodystat::BSReadModelVersion(
            &model,&majorV,&minorV,&psoc2V,&eepromV,&bluthV)){
            emit taskDone(id,TASK_ERR_GET_MODEL_VERSION_FAILED);
            return;
        }
        bodyStat.setModel(model);
        bodyStat.setFirmwareV(majorV,minorV,psoc2V,eepromV);
        // 读取序列号
        unsigned long seriNum=0;
        if(Bodystat::NoError!=Bodystat::BSReadSerialNumber(&seriNum)){
            emit taskDone(id,TASK_ERR_GET_SERIAL_NUMBER_FAILED);
            return;
        }
        bodyStat.setSeriNum(seriNum);
        // 读取校准日期
        __time64_t time;
        if(Bodystat::NoError!=Bodystat::BSReadCalibrationTime(&time)){
            emit taskDone(id,TASK_ERR_GET_CALIB_TIME_FAILED);
            return;
        }
        bodyStat.setCalibDate(QDateTime::fromTime_t(time).date());
        // 发送无误信号
        emit taskDone(id,TASK_ERR_NONE);
        // 返回
        return;
    }
}

void Bluetooth::setDrivInfo(const QString &drivInfo){
    {
        QMutexLocker locker(&_lock);
        _drivInfo=drivInfo;
    }
    emit drivInfoChanged();
}
