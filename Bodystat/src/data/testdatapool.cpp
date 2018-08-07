#include"testdatapool.h"
#include"../comm/singleton.h"
#include"../../../include/BodystatSDK.h"
#include"testdata.h"
#include<QSqlDatabase>
#include<QDateTime>
#include<QSqlQuery>
#include<QMutexLocker>
#include<QVariant>

TestDataPool::~TestDataPool(){
}

TestDataPool *TestDataPool::instance(){
    return(Singleton<TestDataPool>::instance());
}

void TestDataPool::clear(){
    QMutexLocker locker(&_lock);
    _dataV.clear();
}

int TestDataPool::count() const{
    QMutexLocker locker(&_lock);
    return(_dataV.count());
}

int TestDataPool::add(QSqlDatabase &db,
    const Bodystat::BSMeasurement &mData){
    // 数据库非法
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    // 检测数据是否已经分配
    QString sql=QString("SELECT COUNT(*) FROM TestData WHERE "
        "DevModel=%1 AND DevSeriNum=%2 AND TestDateTime='%3';")
        .arg(mData.iDeviceModel).arg(mData.ulDeviceSerialNumber)
        .arg(QDateTime::fromTime_t(mData.tTestDate).toString(
        "yyyy-MM-dd HH:mm:ss"));
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    if(query.next()&&query.value(0).toInt()>0){// 测试数据已经分配
        return(1);
    }
    // 创建测试
    PtrToData data(new TestData(mData));
    if(data.isNull()){
        return(-3);
    }
    if(data->isValid()<0){
        return(-4);
    }
    // 插入测试数据
    add(data);
    // 返回
    return(0);
}

TestDataPool::TestDataPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_dataV(){
}

void TestDataPool::add(PtrToData &data){
    QMutexLocker locker(&_lock);
    _dataV.push_back(data);
}
