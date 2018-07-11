#include"btcommu.h"
#include"../../../include/BodystatSDK.h"
#include<QMutexLocker>

BTCommu::BTCommu(QObject *parent/*=0*/)
    :Commu(parent)
    ,_lock()
    ,_stackInfo(){
}

BTCommu::~BTCommu(){
}

int BTCommu::isValid() const{
    QMutexLocker locker(&_lock);
    if(Bodystat::BSIsDeviceInstallInProgress(0)){
        return(-1);
    }
    if(!Bodystat::BSIsBTAvailable()){
        return(-2);
    }
    return(0);
}

int BTCommu::readStackInfo(){
    {
        QMutexLocker locker(&_lock);
        TCHAR buf[1024];
        if(!Bodystat::BSGetBTStackInfo(buf,1024)){
            return(-1);
        }
        _stackInfo=QString::fromUtf16((ushort*)buf);
    }
    emit stackInfoChanged();
    return(0);
}
