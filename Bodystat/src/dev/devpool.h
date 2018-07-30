#ifndef DEV_POOL_H
#define DEV_POOL_H

#include<QSharedPointer>
#include<QVector>

template<typename T>
class Singleton;
class Dev;
class Bluetooth;
class BodyStat;

class DevPool{
public:
    ~DevPool();
public:
    static DevPool *instance();
public:
    Bluetooth *getBluetooth();
    BodyStat *getBodyStat();
private:
    typedef QSharedPointer<Dev> DevPtr;
    typedef QVector<DevPtr> DevPtrVec;
    friend class Singleton<DevPool>;
private:
    DevPool();
private:
    DevPool(const DevPool &);
    DevPool &operator=(const DevPool &);
private:
    DevPtrVec _devs;
};

#endif // DEV_POOL_H
