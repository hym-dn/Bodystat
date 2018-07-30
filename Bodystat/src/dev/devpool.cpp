#include"devpool.h"
#include"../comm/singleton.h"
#include"bluetooth.h"
#include"bodystat.h"

DevPool::~DevPool(){
}

DevPool *DevPool::instance(){
    return(Singleton<DevPool>::instance());
}

Bluetooth *DevPool::getBluetooth(){
    return(dynamic_cast<Bluetooth*>(_devs[0].data()));
}

BodyStat *DevPool::getBodyStat(){
    return(dynamic_cast<BodyStat*>(_devs[1].data()));
}

DevPool::DevPool()
    :_devs(){
    _devs.push_back(DevPtr(new Bluetooth));
    _devs.push_back(DevPtr(new BodyStat));
}
