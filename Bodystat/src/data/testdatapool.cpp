#include"testdatapool.h"
#include"../comm/singleton.h"
#include"../../../include/BodystatSDK.h"
#include"testdata.h"
#include"subjinfo.h"
#include"subject.h"
#include"subjpool.h"
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

int TestDataPool::pull(QSqlDatabase &db){
    // 数据库非法
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    // 查找SQL
    QString sql("SELECT DevModel,DevSeriNum,TestDateTime,"
        "Sex,Age,Height,Weight,Activity,Waist,Hip,Iz5kHz,"
        "IZ50kHz,Iz100kHz,Iz200kHz,Ir50kHz,Fx50kHz,Fpa50kHz,"
        "FatPerc,FatKg,LeanPerc,LeanKg,TotalWeight,DryLW,"
        "TBWPerc,TBW,ECWPerc,ECW,ICWPerc,ICW,BCM,ThirdSpace,"
        "Nutrition,Illness,BMR,BMRKg,EstAvg,BMI,BFMI,FFMI,"
        "WaistHip,Wellness,ECWLegacy,TBWLegacy,OHY,SkMuscle,"
        "Cm,Rext,Rint,FC,Alpha,SubjectID FROM TestData WHERE "
        "SubjectID IS null ORDER BY DevModel,DevSeriNum,"
        "TestDateTime ASC;");
    // 执行SQL
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    // 获取测试数据
    DataV dataV;
    while(query.next()){
        // 创建测试数据
        PtrToData data(new TestData);
        if(data.isNull()){
            continue;
        }
        // 下载测试数据
        if(data->pull(query)<0){
            continue;
        }
        // 加入向量
        dataV.push_back(data);
    }
    // 交换向量
    swap(dataV);
    // 返回
    return(0);
}

int TestDataPool::assign(QSqlDatabase &db,
    const int subjIdx,const QSet<int> &tdIdxS){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(tdIdxS.isEmpty()){
        return(-2);
    }
    QMutexLocker locker(&_lock);
    DataV aDataV;
    DataV rDataV;
    for(int i=0;i<_dataV.count();++i){
        if(tdIdxS.contains(i)){
            aDataV.push_back(_dataV[i]);
        }else{
            rDataV.push_back(_dataV[i]);
        }
    }
    if(SubjPool::instance()->assign(db,subjIdx,aDataV)<0){
        return(-3);
    }
    _dataV.swap(rDataV);
    return(0);
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
    // 检测测试分配
    /*
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
    */
    // 换算测试结果
    Bodystat::BSResults mRes;
    if(Bodystat::NoError!=Bodystat::BSCalculateResults(
        &mData,&mRes,Bodystat::BSAnalysisModeBoth)){
        return(-3);
    }
    // 创建测试
    PtrToData data(new TestData(mData,mRes));
    if(data.isNull()){
        return(-4);
    }
    // 推送测试
    QSqlQuery query_t(db);
    if(data->push(query_t)<0){
        return(-5);
    }
    // 插入测试数据
    add(data);
    // 返回
    return(0);
}

TestDataPool::PtrToCData
    TestDataPool::getData(const int i){
    QMutexLocker locker(&_lock);
    if(i>=_dataV.count()){
        return(PtrToCData());
    }else{
        return(_dataV.at(i));
    }
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

void TestDataPool::swap(DataV &dataV){
    QMutexLocker locker(&_lock);
    _dataV.swap(dataV);
}
