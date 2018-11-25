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
#include<QAlgorithms.h>

static bool testDataLessThan(
    const TestDataPool::PtrToData &l,
    const TestDataPool::PtrToData &r){
    if(l->getDevModel()<r->getDevModel()){
        return(true);
    }else if(l->getDevModel()==r->getDevModel()){

        if(l->getDevSeriNum()<r->getDevSeriNum()){
            return(true);
        }else if(l->getDevSeriNum()==r->getDevSeriNum()){
            if(l->getTestDateTime()>r->getTestDateTime()){
                return(true);
            }else{
                return(false);
            }
        }else{
            return(false);
        }

    }else{
        return(false);
    }
}

TestDataPool::~TestDataPool(){
}

TestDataPool *TestDataPool::instance(){
    return(Singleton<TestDataPool>::instance());
}

int TestDataPool::pull(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    QString sql("SELECT DevModel,DevSeriNum,TestDateTime,"
        "TestNo,Sex,Age,Height,Weight,Activity,Waist,Hip,Iz5kHz,"
        "IZ50kHz,Iz100kHz,Iz200kHz,Ir50kHz,Fx50kHz,Fpa50kHz,"
        "FatPerc,FatKg,LeanPerc,LeanKg,TotalWeight,DryLW,"
        "TBWPerc,TBW,ECWPerc,ECW,ICWPerc,ICW,BCM,ThirdSpace,"
        "Nutrition,Illness,BMR,BMRKg,EstAvg,BMI,BFMI,FFMI,"
        "WaistHip,Wellness,ECWLegacy,TBWLegacy,OHY,SkMuscle,"
        "Cm,Rext,Rint,FC,Alpha,SubjectID FROM TestData WHERE "
        "SubjectID IS NULL ORDER BY DevModel ASC,DevSeriNum ASC,"
        "TestDateTime DESC;");
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    DataV dataV;
    while(query.next()){
        PtrToData data(new TestData);
        if(data.isNull()){
            continue;
        }
        if(data->pull(query)<0){
            continue;
        }
        dataV.push_back(data);
    }
    swap(dataV);
    return(0);
}

int TestDataPool::pull_t(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    QString sql("SELECT TestData.DevModel,TestData.DevSeriNum,"
        "TestData.TestDateTime,TestData.TestNo,TestData.Sex,"
        "TestData.Age,TestData.Height,TestData.Weight,TestData.Activity,"
        "TestData.Waist,TestData.Hip,TestData.Iz5kHz,TestData.IZ50kHz,"
        "TestData.Iz100kHz,TestData.Iz200kHz,TestData.Ir50kHz,"
        "TestData.Fx50kHz,TestData.Fpa50kHz,TestData.FatPerc,"
        "TestData.FatKg,TestData.LeanPerc,TestData.LeanKg,"
        "TestData.TotalWeight,TestData.DryLW,TestData.TBWPerc,TestData.TBW,"
        "TestData.ECWPerc,TestData.ECW,TestData.ICWPerc,TestData.ICW,TestData.BCM,"
        "TestData.ThirdSpace,TestData.Nutrition,TestData.Illness,TestData.BMR,"
        "TestData.BMRKg,TestData.EstAvg,TestData.BMI,TestData.BFMI,TestData.FFMI,"
        "TestData.WaistHip,TestData.Wellness,TestData.ECWLegacy,TestData.TBWLegacy,"
        "TestData.OHY,TestData.SkMuscle,TestData.Cm,TestData.Rext,TestData.Rint,"
        "TestData.FC,TestData.Alpha,TestData.SubjectID,Subject.Name FROM TestData "
        "LEFT JOIN Subject ON TestData.SubjectID=Subject.ID ORDER BY "
        "TestData.DevModel ASC,TestData.DevSeriNum ASC,TestData.TestDateTime DESC;");
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    DataV dataV;
    while(query.next()){
        PtrToData data(new TestData);
        if(data.isNull()){
            continue;
        }
        if(data->pull_t(query)<0){
            continue;
        }
        dataV.push_back(data);
    }
    swap_t(dataV);
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

void TestDataPool::clear_t(){
    QMutexLocker locker(&_lock);
    _dataV_t.swap(DataV());
}

int TestDataPool::count() const{
    QMutexLocker locker(&_lock);
    return(_dataV.count());
}

int TestDataPool::count_t() const{
    QMutexLocker locker(&_lock);
    return(_dataV_t.count());
}

int TestDataPool::add(QSqlDatabase &db,
    const int testNo,const Bodystat::BSMeasurement &mData){
    // 数据库非法
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    // 冲突探测
    if(SubjPool::instance()->containTestData(
        mData.iDeviceModel,mData.ulDeviceSerialNumber,
        QDateTime::fromTime_t(mData.tTestDate))||
       TestDataPool::instance()->contain(mData.iDeviceModel,
        mData.ulDeviceSerialNumber,QDateTime::fromTime_t(
        mData.tTestDate))){
        return(1);
    }
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
    PtrToData data(new TestData(testNo,mData,mRes));
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

int TestDataPool::add(PtrToData &data){
    if(data.isNull()){
        return(-1);
    }
    if(data->isValid()<0){
        return(-2);
    }
    add_(data);
    return(0);
}

TestDataPool::PtrToCData
    TestDataPool::getData(const int idx){
    QMutexLocker locker(&_lock);
    if(idx<0||idx>=_dataV.count()){
        return(PtrToCData());
    }else{
        return(_dataV.at(idx));
    }
}

TestDataPool::PtrToCData
    TestDataPool::getData_t(const int idx){
    QMutexLocker locker(&_lock);
    if(idx<0||idx>=_dataV_t.count()){
        return(PtrToCData());
    }else{
        return(_dataV_t.at(idx));
    }
}

TestDataPool::TestDataPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_dataV()
    ,_dataV_t(){
}

void TestDataPool::add_(PtrToData &data){
    QMutexLocker locker(&_lock);
    _dataV.push_back(data);
}

void TestDataPool::swap(DataV &dataV){
    QMutexLocker locker(&_lock);
    _dataV.swap(dataV);
}

void TestDataPool::swap_t(DataV &dataV){
    QMutexLocker locker(&_lock);
    _dataV_t.swap(dataV);
}

bool TestDataPool::contain(const unsigned int devModel,
    const unsigned int devSeriNum,const QDateTime &testDateTime) const{
    QMutexLocker locker(&_lock);
    for(DataV::const_iterator itr=_dataV.begin();itr!=_dataV.end();++itr){
        if((*itr)->same(devModel,devSeriNum,testDateTime)){
            return(true);
        }
    }
    return(false);
}

void TestDataPool::sort(){
    QMutexLocker locker(&_lock);
    qSort(_dataV.begin(),_dataV.end(),testDataLessThan);
}
