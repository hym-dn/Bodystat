#include"bluetooth.h"
#include"../../../include/BodystatSDK.h"
#include"bodystat.h"
#include"../data/testdatapool.h"
#include"../db/dbmanager.h"
#include<QMutexLocker>
#include<QDateTime>

Bluetooth::Bluetooth(QObject *parent/*=0*/)
    :Dev(parent)
    ,_thread()
    ,_lock()
    ,_drivInfo(){
    moveToThread(&_thread);
    connect(this,SIGNAL(task(uint,BodyStat*)),
        this,SLOT(onTask(uint,BodyStat*)));
    _thread.start();
}

Bluetooth::~Bluetooth(){
    _thread.quit();
    _thread.wait();
}

QString Bluetooth::getTaskText(const unsigned int id){
    switch(id){
    case TASK_ERR_NONE:
        return(tr("无错误！"));
    case TASK_ERR_DIRV_INVAL:
        return(tr("未能检测到蓝牙驱动！"));
    case TASK_ERR_DEV_INVAL:
        return(tr("蓝牙设备无效！"));
    case TASK_ERR_GET_DIRV_INFO_FAILED:
        return(tr("获取蓝牙驱动信息失败！"));
    case TASK_ERR_UNAU_FALIED:
        return(tr("取消配对失败！"));
    case TASK_ERR_FIND_DEV_FAILED:
        return(tr("搜索设备失败！"));
    case TASK_ERR_NO_DEV:
        return(tr("未能搜索到相关设备！"));
    case TASK_ERR_AUTH_FAILED:
        return(tr("配对失败！"));
    case TASK_ERR_GET_DEV_INFO_FAILED:
        return(tr("获取设备信息失败！"));
    case TASK_ERR_OPEN_PORT_FAILED:
        return(tr("打开设备端口失败！"));
    case TASK_ERR_CONN_DEV_FAILED:
        return(tr("连接设备失败！"));
    case TASK_ERR_GET_MODEL_VERSION_FAILED:
        return(tr("获取设备固件版本失败！"));
    case TASK_ERR_GET_SERIAL_NUMBER_FAILED:
        return(tr("获取设备序列号失败！"));
    case TASK_ERR_GET_CALIB_TIME_FAILED:
        return(tr("获取设备校准时间失败！"));
    case TASK_ERR_DEV_NOT_READY:
        return(tr("设备尚未就绪！"));
    case TASK_ERR_GET_TEST_DATE_FAILED:
        return(tr("获取测试数据失败！"));
    case TASK_ERR_NO_NEW_TEST_DATA:
        return(tr("无新的测试数据！"));
    default:
        return(tr("未知错误！"));
    }
}

void Bluetooth::reset(){
    {
        QMutexLocker locker(&_lock);
        _drivInfo.clear();
    }
    emit drivInfoChanged();
}

const QString &Bluetooth::getDrivInfo() const{
    QMutexLocker locker(&_lock);
    return(_drivInfo);
}

void Bluetooth::scanDev(BodyStat *bodyStat){
    emit task(TASK_ID_SCAN_DEV,bodyStat);
}

void Bluetooth::reloadDev(BodyStat *bodyStat){
    emit task(TASK_ID_RELOAD_DEV,bodyStat);
}

void Bluetooth::unauthDev(BodyStat *bodyStat){
    emit task(TASK_ID_UNAUTH_DEV,bodyStat);
}

void Bluetooth::downloadTestData(BodyStat *bodyStat){
    emit task(TASK_ID_DOWNLOAD_TEST_DATA,bodyStat);
}

void Bluetooth::onTask(const unsigned int id,BodyStat *bodyStat){
    // 任务启动
    emit taskStart(id);
    // 超时时限
    static unsigned short timeout=7;
    // 连接设备或重载设备
    if(TASK_ID_SCAN_DEV==id||TASK_ID_RELOAD_DEV==id){
        // 重置蓝牙、设备
        if(TASK_ID_SCAN_DEV==id){
            reset();
        }
        bodyStat->reset();
        // 扫描设备
        if(TASK_ID_SCAN_DEV==id){
            // 蓝牙驱动尚未安装
            if(Bodystat::BSIsDeviceInstallInProgress(0)){
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
        }
        // 获取设备信息
        TCHAR devName[512]={0};
        TCHAR bda[18]={0};
        TCHAR port[256]={0};
        if(!Bodystat::BSGetBTBodystatDevice(
            devName,512,bda,18,port,256,timeout)){
            emit taskDone(id,TASK_ERR_GET_DEV_INFO_FAILED);
            return;
        }
        bodyStat->setName(QString::fromUtf16((ushort*)devName));
        bodyStat->setBda(QString::fromUtf16((ushort*)bda));
        bodyStat->setPort(QString::fromUtf16((ushort*)port));
        // 连接设备
        if(Bodystat::NoError!=Bodystat::BSOpenComport(port,256)){
            emit taskDone(id,TASK_ERR_OPEN_PORT_FAILED);
            return;
        }
        bodyStat->setIsOpen(true);
        if(Bodystat::NoError!=Bodystat::BSConnect()){
            emit taskDone(id,TASK_ERR_CONN_DEV_FAILED);
            return;
        }
        bodyStat->setIsConnect(true);
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
        bodyStat->setModel(model);
        bodyStat->setFirmwareV(majorV,minorV,psoc2V,eepromV);
        // 读取序列号
        unsigned long seriNum=0;
        if(Bodystat::NoError!=Bodystat::BSReadSerialNumber(&seriNum)){
            emit taskDone(id,TASK_ERR_GET_SERIAL_NUMBER_FAILED);
            return;
        }
        bodyStat->setSeriNum(seriNum);
        // 读取校准日期
        __time64_t time;
        if(Bodystat::NoError!=Bodystat::BSReadCalibrationTime(&time)){
            emit taskDone(id,TASK_ERR_GET_CALIB_TIME_FAILED);
            return;
        }
        bodyStat->setCalibDate(QDateTime::fromTime_t(time).date());
        // 发送无误信号
        emit taskDone(id,TASK_ERR_NONE);
        // 返回
        return;
    }
    // 取消配对设备
    else if(TASK_ID_UNAUTH_DEV==id){
        // 重置蓝牙、设备
        reset();
        bodyStat->reset();
        // 断开连接
        Bodystat::BSCloseComport();
        // 擦除配对
        if(!Bodystat::BSUnAuthenticateBTDevices(1,0,timeout)){
            emit taskDone(id,TASK_ERR_UNAU_FALIED);
            return;
        }
        // 发送无误信号
        emit taskDone(id,TASK_ERR_NONE);
        // 返回
        return;
    }
    // 下载测试数据
    else if(TASK_ID_DOWNLOAD_TEST_DATA==id){
        // 设备尚未连接
        if(!bodyStat->getIsOpen()||
            !bodyStat->getIsConnect()){
            // 发送信号
            emit taskDone(id,TASK_ERR_DEV_NOT_READY);
            // 返回
            return;
        }
        // 声明测试数据
        Bodystat::BSRawData rawData;
        rawData.iRecordArraySize=
            Bodystat::BS_RAWDATA_ARRAYSIZE;
        // 读取测试数据
        if(Bodystat::NoError!=
            Bodystat::BSReadStoredTestData(&rawData)){
            // 发送信号
            emit taskDone(id,TASK_ERR_GET_TEST_DATE_FAILED);
            // 返回
            return;
        }
        // 清除测试数据
        // TestDataPool::instance()->clear();
        // 追加测试数据
        for(int i=0;i<rawData.iTotalNumRecs;++i){
            rawData.record[i].iFrequencies=0;
            rawData.record[i].pMultifreqData=0;
            TestDataPool::instance()->add(
                DBManager::instance()->getDB(),rawData.record[i]);
        }
        // 测试数据排序
        TestDataPool::instance()->sort();
        // 如果无测试数据
        if(TestDataPool::instance()->count()<=0){
            emit taskDone(id,TASK_ERR_NO_NEW_TEST_DATA);
        }
        // 发送无误信号
        else{
            emit taskDone(id,TASK_ERR_NONE);
        }
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
