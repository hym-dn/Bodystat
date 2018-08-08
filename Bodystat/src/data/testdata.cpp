#include"testdata.h"
#include"../../../Include/BodystatSDK.h"
#include<QObject>

TestData::TestData()
    :_devModel(0)
    ,_devSeriNum(0)
    ,_testDateTime()
    ,_sex(SEX_UNKNOWN)
    ,_age(0)
    ,_height(0)
    ,_weight(0.0)
    ,_activity(0)
    ,_waist(0)
    ,_hip(0)
    ,_iz5kHz(0)
    ,_iz50kHz(0)
    ,_iz100kHz(0)
    ,_iz200kHz(0)
    ,_ir50kHz(0)
    ,_fx50kHz(0)
    ,_fpa50kHz(0){
}

TestData::TestData(const Bodystat::BSMeasurement &meas)
    :_devModel(meas.iDeviceModel)
    ,_devSeriNum(meas.ulDeviceSerialNumber)
    ,_testDateTime(QDateTime::fromTime_t(meas.tTestDate))
    ,_sex(Bodystat::BSMale==meas.iGender?SEX_MALE:SEX_FEMALE)
    ,_age(meas.iAge)
    ,_height(meas.iHeight)
    ,_weight(meas.fWeight)
    ,_activity(meas.iActivity)
    ,_waist(meas.iWaist)
    ,_hip(meas.iHip)
    ,_iz5kHz(meas.iZ_5kHz)
    ,_iz50kHz(meas.iZ_50kHz)
    ,_iz100kHz(meas.iZ_100kHz)
    ,_iz200kHz(meas.iZ_200kHz)
    ,_ir50kHz(meas.iR_50kHz)
    ,_fx50kHz(meas.fX_50kHz)
    ,_fpa50kHz(meas.fPA_50kHz){
}

TestData::TestData(const TestData &src)
    :_devModel(src._devModel)
    ,_devSeriNum(src._devSeriNum)
    ,_testDateTime(src._testDateTime)
    ,_sex(src._sex)
    ,_age(src._age)
    ,_height(src._height)
    ,_weight(src._weight)
    ,_activity(src._activity)
    ,_waist(src._waist)
    ,_hip(src._hip)
    ,_iz5kHz(src._iz5kHz)
    ,_iz50kHz(src._iz50kHz)
    ,_iz100kHz(src._iz100kHz)
    ,_iz200kHz(src._iz200kHz)
    ,_ir50kHz(src._ir50kHz)
    ,_fx50kHz(src._fx50kHz)
    ,_fpa50kHz(src._fpa50kHz){
}

TestData::~TestData(){
}

int TestData::isValid() const{
    // 设备模型
    if(0==_devModel){
        return(-1);
    }
    // 设备序号
    if(0==_devSeriNum){
        return(-2);
    }
    // 测试日期
    if(!_testDateTime.isValid()){
        return(-3);
    }
    // 性别
    if(SEX_UNKNOWN==_sex){
        return(-4);
    }
    // 年龄
    // 身高
    // 体重
    // 活跃度
    // 胸围
    // 臀围
    // ...
    // 返回
    return(0);
}

void TestData::setDevModel(const unsigned int model){
    _devModel=model;
}

unsigned int TestData::getDevModel() const{
    return(_devModel);
}

void TestData::setDevSeriNum(const unsigned long seriNum){
    _devSeriNum=seriNum;
}

unsigned long TestData::getDevSeriNum() const{
    return(_devSeriNum);
}

QString TestData::getDevSeriNumText() const{
    return(QString("%1").arg(getDevSeriNum()));
}

void TestData::setTestDateTime(const QDateTime &dateTime){
    _testDateTime=dateTime;
}

const QDateTime &TestData::getTestDateTime() const{
    return(_testDateTime);
}

QString TestData::getTestDateTimeText() const{
    return(getTestDateTime().toString(
        "yyyy-MM-dd hh:mm:ss"));
}

void TestData::setSex(const Sex sex){
    _sex=sex;
}

TestData::Sex TestData::getSex() const{
    return(_sex);
}

QString TestData::getSexText() const{
    const Sex sex=getSex();
    if(SEX_MALE==sex){
        return(QObject::tr("男"));
    }else if(SEX_FEMALE==sex){
        return(QObject::tr("女"));
    }else if(SEX_OTHER==sex){
        return(QObject::tr("其他"));
    }else{
        return(QObject::tr("未知"));
    }
}

void TestData::setAge(const int age){
    _age=age;
}

int TestData::getAge() const{
    return(_age);
}

QString TestData::getAgeText() const{
    return(QString("%1").arg(getAge()));
}

void TestData::setHeight(const float height){
    _height=height;
}

int TestData::getHeight() const{
    return(_height);
}

QString TestData::getHeightText() const{
    return(QString("%1").arg(getHeight()));
}

void TestData::setWeight(const float weight){
    _weight=weight;
}

float TestData::getWeight() const{
    return(_weight);
}

QString TestData::getWeightText() const{
    return(QString("%1").arg(getWeight(),0,'f',3));
}

void TestData::setActivity(const int activity){
    _activity=activity;
}

int TestData::getActivity() const{
    return(_activity);
}

void TestData::setWaist(const int waist){
    _waist=waist;
}

int TestData::getWaist() const{
    return(_waist);
}

QString TestData::getWaistText() const{
    return(QString("%1").arg(getWaist()));
}

void TestData::setHip(const int hip){
    _hip=hip;
}

int TestData::getHip() const{
    return(_hip);
}

QString TestData::getHipText() const{
    return(QString("%1").arg(getHip()));
}

void TestData::setIz5kHz(const int iz5kHz){
    _iz5kHz=iz5kHz;
}

int TestData::getIz5kHz() const{
    return(_iz5kHz);
}

void TestData::setIz50kHz(const int iz50kHz){
    _iz50kHz=iz50kHz;
}

int TestData::getIz50kHz() const{
    return(_iz50kHz);
}

void TestData::setIz100kHz(const int iz100kHz){
    _iz100kHz=iz100kHz;
}

int TestData::getIz100kHz() const{
    return(_iz100kHz);
}

void TestData::setIz200kHz(const int iz200kHz){
    _iz200kHz=iz200kHz;
}

int TestData::getIz200kHz() const{
    return(_iz200kHz);
}

void TestData::setIr50kHz(const int ir50kHz){
    _ir50kHz=ir50kHz;
}

int TestData::getIr50kHz() const{
    return(_ir50kHz);
}

void TestData::setFx50kHz(const float fx50kHz){
    _fx50kHz=fx50kHz;
}

float TestData::getFx50kHz() const{
    return(_fx50kHz);
}

void TestData::setFpa50kHz(const float fpa50kHz){
    _fpa50kHz=fpa50kHz;
}

float TestData::getFpa50kHz() const{
    return(_fpa50kHz);
}

TestData &TestData::operator=(const TestData &src){
    _devModel=src._devModel;
    _devSeriNum=src._devSeriNum;
    _testDateTime=src._testDateTime;
    _sex=src._sex;
    _age=src._age;
    _height=src._height;
    _weight=src._weight;
    _activity=src._activity;
    _waist=src._waist;
    _hip=src._hip;
    _iz5kHz=src._iz5kHz;
    _iz50kHz=src._iz50kHz;
    _iz100kHz=src._iz100kHz;
    _iz200kHz=src._iz200kHz;
    _ir50kHz=src._ir50kHz;
    _fx50kHz=src._fx50kHz;
    _fpa50kHz=src._fpa50kHz;
    return(*this);
}
