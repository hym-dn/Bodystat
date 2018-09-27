#include"testdata.h"
#include"../../../Include/BodystatSDK.h"
#include"../dev/bodystat.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>

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
    ,_fpa50kHz(0)
    ,_fatPerc(0.0)
    ,_fatKg(0.0)
    ,_leanPerc(0.0)
    ,_leanKg(0.0)
    ,_totalWeight(0.0)
    ,_dryLW(0.0)
    ,_tbwPerc(0.0)
    ,_tbw(0.0)
    ,_ecwPerc(0.0)
    ,_ecw(0.0)
    ,_icwPerc(0.0)
    ,_icw(0.0)
    ,_bcm(0.0)
    ,_thirdSpace(0.0)
    ,_nutrition(0.0)
    ,_illness(0.0)
    ,_bmr(0.0)
    ,_bmrKg(0.0)
    ,_estAvg(0.0)
    ,_bmi(0.0)
    ,_bfmi(0.0)
    ,_ffmi(0.0)
    ,_waistHip(0.0)
    ,_wellness(0.0)
    ,_ecwLegacy(0.0)
    ,_tbwLegacy(0.0)
    ,_ohy(0.0)
    ,_skMuscle(0.0)
    ,_cm(0.0)
    ,_rext(0.0)
    ,_rint(0.0)
    ,_fc(0.0)
    ,_alpha(0.0)
    ,_subjId(){
}

TestData::TestData(
    const Bodystat::BSMeasurement &meas,
    const Bodystat::BSResults &ress)
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
    ,_fpa50kHz(meas.fPA_50kHz)
    ,_fatPerc(ress.fFatPerc)
    ,_fatKg(ress.fFatKg)
    ,_leanPerc(ress.fLeanPerc)
    ,_leanKg(ress.fLeanKg)
    ,_totalWeight(ress.fTotalWeight)
    ,_dryLW(ress.fDryLW)
    ,_tbwPerc(ress.fTBWPerc)
    ,_tbw(ress.fTBW)
    ,_ecwPerc(ress.fECWPerc)
    ,_ecw(ress.fECW)
    ,_icwPerc(ress.fICWPerc)
    ,_icw(ress.fICW)
    ,_bcm(ress.fBCM)
    ,_thirdSpace(ress.fThirdSpace)
    ,_nutrition(ress.fNutrition)
    ,_illness(ress.fIllness)
    ,_bmr(ress.fBMR)
    ,_bmrKg(ress.fBMRkg)
    ,_estAvg(ress.fEstAvg)
    ,_bmi(ress.fBMI)
    ,_bfmi(ress.fBFMI)
    ,_ffmi(ress.fFFMI)
    ,_waistHip(ress.fWaistHip)
    ,_wellness(ress.fWellness)
    ,_ecwLegacy(ress.fECW_Legacy)
    ,_tbwLegacy(ress.fTBW_Legacy)
    ,_ohy(ress.fOHY)
    ,_skMuscle(ress.fSkMuscle)
    ,_cm(ress.fCm)
    ,_rext(ress.fRext)
    ,_rint(ress.fRint)
    ,_fc(ress.fFc)
    ,_alpha(ress.fAlpha)
    ,_subjId(){
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
    ,_fpa50kHz(src._fpa50kHz)
    ,_fatPerc(src._fatPerc)
    ,_fatKg(src._fatKg)
    ,_leanPerc(src._leanPerc)
    ,_leanKg(src._leanKg)
    ,_totalWeight(src._totalWeight)
    ,_dryLW(src._dryLW)
    ,_tbwPerc(src._tbwPerc)
    ,_tbw(src._tbw)
    ,_ecwPerc(src._ecwPerc)
    ,_ecw(src._ecw)
    ,_icwPerc(src._icwPerc)
    ,_icw(src._icw)
    ,_bcm(src._bcm)
    ,_thirdSpace(src._thirdSpace)
    ,_nutrition(src._nutrition)
    ,_illness(src._illness)
    ,_bmr(src._bmr)
    ,_bmrKg(src._bmrKg)
    ,_estAvg(src._estAvg)
    ,_bmi(src._bmi)
    ,_bfmi(src._bfmi)
    ,_ffmi(src._ffmi)
    ,_waistHip(src._waistHip)
    ,_wellness(src._wellness)
    ,_ecwLegacy(src._ecwLegacy)
    ,_tbwLegacy(src._tbwLegacy)
    ,_ohy(src._ohy)
    ,_skMuscle(src._skMuscle)
    ,_cm(src._cm)
    ,_rext(src._rext)
    ,_rint(src._rint)
    ,_fc(src._fc)
    ,_alpha(src._alpha)
    ,_subjId(src._subjId){
}

TestData::~TestData(){
}

int TestData::pull(QSqlQuery &query,const unsigned long sIdx/*=0*/){
    if(!query.isValid()){
        return(-1);
    }
    bool ok=false;
    _devModel=query.value(sIdx+0).toUInt(&ok);
    if(!ok){
        return(-2);
    }
    _devSeriNum=query.value(sIdx+1).toUInt(&ok);
    if(!ok){
        return(-3);
    }
    _testDateTime=query.value(sIdx+2).toDateTime();
    unsigned int uInt=query.value(sIdx+3).toUInt(&ok);
    if(!ok){
        return(-4);
    }
    if(uInt>SEX_OTHER){
        return(-5);
    }
    _sex=static_cast<Sex>(uInt);
    _age=query.value(sIdx+4).toInt(&ok);
    if(!ok){
        return(-6);
    }
    _height=query.value(sIdx+5).toInt(&ok);
    if(!ok){
        return(-7);
    }
    _weight=query.value(sIdx+6).toFloat(&ok);
    if(!ok){
        return(-8);
    }
    _activity=query.value(sIdx+7).toInt(&ok);
    if(!ok){
        return(-9);
    }
    _waist=query.value(sIdx+8).toInt(&ok);
    if(!ok){
        return(-10);
    }
    _hip=query.value(sIdx+9).toInt(&ok);
    if(!ok){
        return(-11);
    }
    _iz5kHz=query.value(sIdx+10).toInt(&ok);
    if(!ok){
        return(-12);
    }
    _iz50kHz=query.value(sIdx+11).toInt(&ok);
    if(!ok){
        return(-13);
    }
    _iz100kHz=query.value(sIdx+12).toInt(&ok);
    if(!ok){
        return(-14);
    }
    _iz200kHz=query.value(sIdx+13).toInt(&ok);
    if(!ok){
        return(-15);
    }
    _ir50kHz=query.value(sIdx+14).toFloat(&ok);
    if(!ok){
        return(-16);
    }
    _fx50kHz=query.value(sIdx+15).toFloat(&ok);
    if(!ok){
        return(-17);
    }
    _fpa50kHz=query.value(sIdx+16).toFloat(&ok);
    if(!ok){
        return(-18);
    }
    _fatPerc=query.value(sIdx+17).toFloat(&ok);
    if(!ok){
        return(-19);
    }
    _fatKg=query.value(sIdx+18).toFloat(&ok);
    if(!ok){
        return(-20);
    }
    _leanPerc=query.value(sIdx+19).toFloat(&ok);
    if(!ok){
        return(-21);
    }
    _leanKg=query.value(sIdx+20).toFloat(&ok);
    if(!ok){
        return(-22);
    }
    _totalWeight=query.value(sIdx+21).toFloat(&ok);
    if(!ok){
        return(-23);
    }
    _dryLW=query.value(sIdx+22).toFloat(&ok);
    if(!ok){
        return(-24);
    }
    _tbwPerc=query.value(sIdx+23).toFloat(&ok);
    if(!ok){
        return(-25);
    }
    _tbw=query.value(sIdx+24).toFloat(&ok);
    if(!ok){
        return(-26);
    }
    _ecwPerc=query.value(sIdx+25).toFloat(&ok);
    if(!ok){
        return(-27);
    }
    _ecw=query.value(sIdx+26).toFloat(&ok);
    if(!ok){
        return(-28);
    }
    _icwPerc=query.value(sIdx+27).toFloat(&ok);
    if(!ok){
        return(-29);
    }
    _icw=query.value(sIdx+28).toFloat(&ok);
    if(!ok){
        return(-30);
    }
    _bcm=query.value(sIdx+29).toFloat(&ok);
    if(!ok){
        return(-31);
    }
    _thirdSpace=query.value(sIdx+30).toFloat(&ok);
    if(!ok){
        return(-32);
    }
    _nutrition=query.value(sIdx+31).toFloat(&ok);
    if(!ok){
        return(-33);
    }
    _illness=query.value(sIdx+32).toFloat(&ok);
    if(!ok){
        return(-34);
    }
    _bmr=query.value(sIdx+33).toFloat(&ok);
    if(!ok){
        return(-35);
    }
    _bmrKg=query.value(sIdx+34).toFloat(&ok);
    if(!ok){
        return(-36);
    }
    _estAvg=query.value(sIdx+35).toFloat(&ok);
    if(!ok){
        return(-37);
    }
    _bmi=query.value(sIdx+36).toFloat(&ok);
    if(!ok){
        return(-38);
    }
    _bfmi=query.value(sIdx+37).toFloat(&ok);
    if(!ok){
        return(-39);
    }
    _ffmi=query.value(sIdx+38).toFloat(&ok);
    if(!ok){
        return(-40);
    }
    _waistHip=query.value(sIdx+39).toFloat(&ok);
    if(!ok){
        return(-41);
    }
    _wellness=query.value(sIdx+40).toFloat(&ok);
    if(!ok){
        return(-42);
    }
    _ecwLegacy=query.value(sIdx+41).toFloat(&ok);
    if(!ok){
        return(-43);
    }
    _tbwLegacy=query.value(sIdx+42).toFloat(&ok);
    if(!ok){
        return(-44);
    }
    _ohy=query.value(sIdx+43).toFloat(&ok);
    if(!ok){
        return(-45);
    }
    _skMuscle=query.value(sIdx+44).toFloat(&ok);
    if(!ok){
        return(-46);
    }
    _cm=query.value(sIdx+45).toFloat(&ok);
    if(!ok){
        return(-47);
    }
    _rext=query.value(sIdx+46).toFloat(&ok);
    if(!ok){
        return(-48);
    }
    _rint=query.value(sIdx+47).toFloat(&ok);
    if(!ok){
        return(-49);
    }
    _fc=query.value(sIdx+48).toFloat(&ok);
    if(!ok){
        return(-50);
    }
    _alpha=query.value(sIdx+49).toFloat(&ok);
    if(!ok){
        return(-51);
    }
    if(query.value(sIdx+50).isNull()){
        _subjId.clear();
    }else{
        _subjId=query.value(sIdx+50).toString();
    }
    if(isValid()<0){
        return(-52);
    }
    return(0);
}

int TestData::push(QSqlQuery &query){
    if(isValid()<0){
        return(-1);
    }
    QString subjId="null";
    if(!getSubjId().isEmpty()){
        subjId=QString("'%1'").arg(getSubjId());
    }
    const QString sql=QString("INSERT INTO TestData ("
        "DevModel,DevSeriNum,TestDateTime,Sex,Age,"
        "Height,Weight,Activity,Waist,Hip,Iz5kHz,"
        "IZ50kHz,Iz100kHz,Iz200kHz,Ir50kHz,Fx50kHz,"
        "Fpa50kHz,FatPerc,FatKg,LeanPerc,LeanKg,TotalWeight,"
        "DryLW,TBWPerc,TBW,ECWPerc,ECW,ICWPerc,ICW,BCM,"
        "ThirdSpace,Nutrition,Illness,BMR,BMRKg,EstAvg,BMI,"
        "BFMI,FFMI,WaistHip,Wellness,ECWLegacy,TBWLegacy,"
        "OHY,SkMuscle,Cm,Rext,Rint,FC,Alpha,SubjectID) "
        "VALUES(%1,%2,'%3',%4,%5,%6,%7,%8,%9,%10,%11,%12,"
        "%13,%14,%15,%16,%17,%18,%19,%20,%21,%22,%23,%24,"
        "%25,%26,%27,%28,%29,%30,%31,%32,%33,%34,%35,%36,"
        "%37,%38,%39,%40,%41,%42,%43,%44,%45,%46,%47,%48,"
        "%49,%50,%51);").arg(getDevModel()).arg(getDevSeriNum())
        .arg(getTestDateTimeText()).arg(getSex()).arg(getAge())
        .arg(getHeight()).arg(getWeight()).arg(getActivity())
        .arg(getWaist()).arg(getHip()).arg(getIz5kHz())
        .arg(getIz50kHz()).arg(getIz100kHz()).arg(getIz200kHz())
        .arg(getIr50kHz()).arg(getFx50kHz()).arg(getFpa50kHz())
        .arg(getFatPerc()).arg(getFatKg()).arg(getLeanPerc())
        .arg(getLeanKg()).arg(getTotalWeight()).arg(getDryLW())
        .arg(getTbwPerc()).arg(getTbw()).arg(getEcwPerc())
        .arg(getEcw()).arg(getIcwPerc()).arg(getIcw()).arg(getBcm())
        .arg(getThirdSpace()).arg(getNutrition()).arg(getIllness())
        .arg(getBmr()).arg(getBmrKg()).arg(getEstAvg()).arg(getBmi())
        .arg(getBfmi()).arg(getFfmi()).arg(getWaistHip())
        .arg(getWellness()).arg(getEcwLegacy()).arg(getTbwLegacy())
        .arg(getOhy()).arg(getSkMuscle()).arg(getCm()).arg(getRext())
        .arg(getRint()).arg(getFc()).arg(getAlpha()).arg(subjId);
    if(!query.exec(sql)){
        return(-1);
    }
    return(0);
}

int TestData::unassign(QSqlQuery &query){
    if(isValid()<0){
        return(-1);
    }
    const QString sql(QString("UPDATE TestData SET SubjectID=%1 "
        "WHERE DevModel=%2 AND DevSeriNum=%3 AND TestDateTime=#%4#;")
        .arg("null").arg(getDevModel()).arg(getDevSeriNum()).arg(
        getTestDateTimeText()));
    if(!query.exec(sql)){
        return(-2);
    }
    setSubjId("");
    return(0);
}

int TestData::isValid() const{
    if(0==_devModel){
        return(-1);
    }else if(0==_devSeriNum){
        return(-2);
    }else if(!_testDateTime.isValid()){
        return(-3);
    }else if(SEX_UNKNOWN==_sex){
        return(-4);
    }else{
        return(0);
    }
}

bool TestData::same(const unsigned int devModel,
    const unsigned int devSeriNum,const QDateTime &testDateTime) const{
    return(devModel==getDevModel()&&devSeriNum==getDevSeriNum()&&
        testDateTime==getTestDateTime());
}

void TestData::setDevModel(const unsigned int model){
    _devModel=model;
}

unsigned int TestData::getDevModel() const{
    return(_devModel);
}

QString TestData::getDevModelText() const{
    return(BodyStat::getModelText(getDevModel()));
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

QString TestData::getTestDateText() const{
    return(getTestDateTime().toString("yyyy-MM-dd"));
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
    return(QString("%1").arg(getWeight(),
        0,'f',PREC_LIMIT));
}

void TestData::setActivity(const int activity){
    _activity=activity;
}

int TestData::getActivity() const{
    return(_activity);
}

QString TestData::getActivityText() const{
    return(QString("%1").arg(getActivity()));
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

QString TestData::getIz5kHzText() const{
    return(QString("%1").arg(getIz5kHz()));
}

void TestData::setIz50kHz(const int iz50kHz){
    _iz50kHz=iz50kHz;
}

int TestData::getIz50kHz() const{
    return(_iz50kHz);
}

QString TestData::getIz50kHzText() const{
    return(QString("%1").arg(getIz50kHz()));
}

void TestData::setIz100kHz(const int iz100kHz){
    _iz100kHz=iz100kHz;
}

int TestData::getIz100kHz() const{
    return(_iz100kHz);
}

QString TestData::getIz100kHzText() const{
    return(QString("%1").arg(getIz100kHz()));
}

void TestData::setIz200kHz(const int iz200kHz){
    _iz200kHz=iz200kHz;
}

int TestData::getIz200kHz() const{
    return(_iz200kHz);
}

QString TestData::getIz200kHzText() const{
    return(QString("%1").arg(getIz200kHz()));
}

void TestData::setIr50kHz(const int ir50kHz){
    _ir50kHz=ir50kHz;
}

int TestData::getIr50kHz() const{
    return(_ir50kHz);
}

QString TestData::getIr50kHzText() const{
    return(QString("%1").arg(getIr50kHz()));
}

void TestData::setFx50kHz(const float fx50kHz){
    _fx50kHz=fx50kHz;
}

float TestData::getFx50kHz() const{
    return(_fx50kHz);
}

QString TestData::getFx50kHzText() const{
    return(QString("%1").arg(getFx50kHz(),
        0,'f',PREC_LIMIT));
}

void TestData::setFpa50kHz(const float fpa50kHz){
    _fpa50kHz=fpa50kHz;
}

float TestData::getFpa50kHz() const{
    return(_fpa50kHz);
}

QString TestData::getFpa50kHzText() const{
    return(QString("%1").arg(getFpa50kHz(),
        0,'f',PREC_LIMIT));
}

void TestData::setFatPerc(const float fatPerc){
    _fatPerc=fatPerc;
}

float TestData::getFatPerc() const{
    return(_fatPerc);
}

QString TestData::getFatPercText() const{
    return(QString("%1").arg(getFatPerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setFatKg(const float fatKg){
    _fatKg=fatKg;
}

float TestData::getFatKg() const{
    return(_fatKg);
}

QString TestData::getFatKgText() const{
    return(QString("%1").arg(getFatKg(),
        0,'f',PREC_LIMIT));
}

void TestData::setLeanPerc(const float leanPerc){
    _leanPerc=leanPerc;
}

float TestData::getLeanPerc() const{
    return(_leanPerc);
}

QString TestData::getLeanPercText() const{
    return(QString("%1").arg(getLeanPerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setLeanKg(const float leanKg){
    _leanKg=leanKg;
}

float TestData::getLeanKg() const{
    return(_leanKg);
}

QString TestData::getLeanKgText() const{
    return(QString("%1").arg(getLeanKg(),
        0,'f',PREC_LIMIT));
}

void TestData::setTotalWeight(const float totalWeight){
    _totalWeight=totalWeight;
}

float TestData::getTotalWeight() const{
    return(_totalWeight);
}

QString TestData::getTotalWeightText() const{
    return(QString("%1").arg(getTotalWeight(),
        0,'f',PREC_LIMIT));
}

void TestData::setDryLW(const float dryLW){
    _dryLW=dryLW;
}

float TestData::getDryLW() const{
   return(_dryLW);
}

QString TestData::getDryLWText() const{
    return(QString("%1").arg(getDryLW(),
        0,'f',PREC_LIMIT));
}

float TestData::getDryLWPerc() const{
    if(fabs(0.0-getWeight())<0.001){
        return(0.0);
    }else{
        return(getDryLW()/getWeight()*100.0);
    }
}

QString TestData::getDryLWPercText() const{
    return(QString("%1").arg(getDryLWPerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setTbwPerc(const float tbwPerc){
    _tbwPerc=tbwPerc;
}

float TestData::getTbwPerc() const{
    return(_tbwPerc);
}

QString TestData::getTbwPercText() const{
    return(QString("%1").arg(getTbwPerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setTbw(const float tbw){
    _tbw=tbw;
}

float TestData::getTbw() const{
    return(_tbw);
}

QString TestData::getTbwText() const{
    return(QString("%1").arg(getTbw(),
        0,'f',PREC_LIMIT));
}

void TestData::setEcwPerc(const float ecwPerc){
    _ecwPerc=ecwPerc;
}

float TestData::getEcwPerc() const{
    return(_ecwPerc);
}

QString TestData::getEcwPercText() const{
    return(QString("%1").arg(getEcwPerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setEcw(const float ecw){
    _ecw=ecw;
}

float TestData::getEcw() const{
    return(_ecw);
}

QString TestData::getEcwText() const{
    return(QString("%1").arg(getEcw(),
        0,'f',PREC_LIMIT));
}

void TestData::setIcwPerc(const float icwPerc){
    _icwPerc=icwPerc;
}

float TestData::getIcwPerc() const{
    return(_icwPerc);
}

QString TestData::getIcwPercText() const{
    return(QString("%1").arg(getIcwPerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setIcw(const float icw){
    _icw=icw;
}

float TestData::getIcw() const{
    return(_icw);
}

QString TestData::getIcwText() const{
    return(QString("%1").arg(getIcw(),
        0,'f',PREC_LIMIT));
}

void TestData::setBcm(const float bcm){
    _bcm=bcm;
}

float TestData::getBcm() const{
    return(_bcm);
}

QString TestData::getBcmText() const{
    return(QString("%1").arg(getBcm(),
        0,'f',PREC_LIMIT));
}

void TestData::setThirdSpace(const float thirdSpace){
    _thirdSpace=thirdSpace;
}

float TestData::getThirdSpace() const{
    return(_thirdSpace);
}

QString TestData::getThirdSpaceText() const{
    return(QString("%1").arg(getThirdSpace(),
        0,'f',PREC_LIMIT));
}

float TestData::getThirdSpacePerc() const{
    if(fabs(0.0-getWeight())<0.001){
        return(0.0);
    }else{
        return(getThirdSpace()/getWeight()*100.0);
    }
}

QString TestData::getThirdSpacePercText() const{
    return(QString("%1").arg(getThirdSpacePerc(),
        0,'f',PREC_LIMIT));
}

void TestData::setNutrition(const float nutrition){
    _nutrition=nutrition;
}

float TestData::getNutrition() const{
    return(_nutrition);
}

QString TestData::getNutritionText() const{
    return(QString("%1").arg(getNutrition(),
        0,'f',PREC_LIMIT));
}

void TestData::setIllness(const float illness){
    _illness=illness;
}

float TestData::getIllness() const{
    return(_illness);
}

QString TestData::getIllnessText() const{
    return(QString("%1").arg(getIllness(),
        0,'f',PREC_LIMIT));
}

void TestData::setBmr(const float bmr){
    _bmr=bmr;
}

float TestData::getBmr() const{
    return(_bmr);
}

QString TestData::getBmrText() const{
    return(QString("%1").arg(getBmr(),
        0,'f',PREC_LIMIT));
}

void TestData::setBmrKg(const float bmrKg){
    _bmrKg=bmrKg;
}

float TestData::getBmrKg() const{
    return(_bmrKg);
}

QString TestData::getBmrKgText() const{
    return(QString("%1").arg(getBmrKg(),
        0,'f',PREC_LIMIT));
}

void TestData::setEstAvg(const float estAvg){
    _estAvg=estAvg;
}

float TestData::getEstAvg() const{
    return(_estAvg);
}

QString TestData::getEstAvgText() const{
    return(QString("%1").arg(getEstAvg(),
        0,'f',PREC_LIMIT));
}

void TestData::setBmi(const float bmi){
    _bmi=bmi;
}

float TestData::getBmi() const{
    return(_bmi);
}

QString TestData::getBmiText() const{
    return(QString("%1").arg(getBmi(),
        0,'f',PREC_LIMIT));
}

void TestData::setBfmi(const float bfmi){
    _bfmi=bfmi;
}

float TestData::getBfmi() const{
    return(_bfmi);
}

QString TestData::getBfmiText() const{
    return(QString("%1").arg(getBfmi(),
        0,'f',PREC_LIMIT));
}

void TestData::setFfmi(const float ffmi){
    _ffmi=ffmi;
}

float TestData::getFfmi() const{
    return(_ffmi);
}

QString TestData::getFfmiText() const{
    return(QString("%1").arg(getFfmi(),
        0,'f',PREC_LIMIT));
}

void TestData::setWaistHip(const float waistHip){
    _waistHip=waistHip;
}

float TestData::getWaistHip() const{
    return(_waistHip);
}

QString TestData::getWaistHipText() const{
    return(QString("%1").arg(getWaistHip(),
        0,'f',PREC_LIMIT));
}

void TestData::setWellness(const float wellness){
    _wellness=wellness;
}

float TestData::getWellness() const{
    return(_wellness);
}

QString TestData::getWellnessText() const{
    return(QString("%1").arg(getWellness(),
        0,'f',PREC_LIMIT));
}

void TestData::setEcwLegacy(const float ecwLegacy){
    _ecwLegacy=ecwLegacy;
}

float TestData::getEcwLegacy() const{
    return(_ecwLegacy);
}

QString TestData::getEcwLegacyText() const{
    return(QString("%1").arg(getEcwLegacy(),
        0,'f',PREC_LIMIT));
}

void TestData::setTbwLegacy(const float tbwLegacy){
    _tbwLegacy=tbwLegacy;
}

float TestData::getTbwLegacy() const{
    return(_tbwLegacy);
}

QString TestData::getTbwLegacyText() const{
    return(QString("%1").arg(getTbwLegacy(),
        0,'f',PREC_LIMIT));
}

void TestData::setOhy(const float ohy){
    _ohy=ohy;
}

float TestData::getOhy() const{
    return(_ohy);
}

QString TestData::getOhyText() const{
    return(QString("%1").arg(getOhy(),
        0,'f',PREC_LIMIT));
}

void TestData::setSkMuscle(const float skMuscle){
    _skMuscle=skMuscle;
}

float TestData::getSkMuscle() const{
    return(_skMuscle);
}

QString TestData::getSkMuscleText() const{
    return(QString("%1").arg(getSkMuscle(),
        0,'f',PREC_LIMIT));
}

float TestData::calSkMuscle() const{
    return((0.401*getHeight()*getHeight()/getIz50kHz())+
        (3.825*(SEX_MALE==getSex()?1.0:0.0))-(0.071*getAge())+5.102);
}

QString TestData::calSkMuscleText() const{
    return(QString("%1").arg(calSkMuscle(),
        0,'f',PREC_LIMIT));
}

void TestData::setCm(const float cm){
    _cm=cm;
}

float TestData::getCm() const{
    return(_cm);
}

QString TestData::getCmText() const{
    return(QString("%1").arg(getCm(),
        0,'f',PREC_LIMIT));
}

void TestData::setRext(const float rext){
    _rext=rext;
}

float TestData::getRext() const{
    return(_rext);
}

QString TestData::getRextText() const{
    return(QString("%1").arg(getRext(),
        0,'f',PREC_LIMIT));
}

void TestData::setRint(const float rint){
    _rint=rint;
}

float TestData::getRint() const{
    return(_rint);
}

QString TestData::getRintText() const{
    return(QString("%1").arg(getRint(),
        0,'f',PREC_LIMIT));
}

void TestData::setFc(const float fc){
    _fc=fc;
}

float TestData::getFc() const{
    return(_fc);
}

QString TestData::getFcText() const{
    return(QString("%1").arg(getFc(),
        0,'f',PREC_LIMIT));
}

void TestData::setAlpha(const float alpha){
    _alpha=alpha;
}

float TestData::getAlpha() const{
    return(_alpha);
}

QString TestData::getAlphaText() const{
    return(QString("%1").arg(getAlpha(),
        0,'f',PREC_LIMIT));
}

void TestData::setSubjId(const QString &subjId){
    _subjId=subjId;
}

const QString &TestData::getSubjId() const{
    return(_subjId);
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
    _fatPerc=src._fatPerc;
    _fatKg=src._fatKg;
    _leanPerc=src._leanPerc;
    _leanKg=src._leanKg;
    _totalWeight=src._totalWeight;
    _dryLW=src._dryLW;
    _tbwPerc=src._tbwPerc;
    _tbw=src._tbw;
    _ecwPerc=src._ecwPerc;
    _ecw=src._ecw;
    _icwPerc=src._icwPerc;
    _icw=src._icw;
    _bcm=src._bcm;
    _thirdSpace=src._thirdSpace;
    _nutrition=src._nutrition;
    _illness=src._illness;
    _bmr=src._bmr;
    _bmrKg=src._bmrKg;
    _estAvg=src._estAvg;
    _bmi=src._bmi;
    _bfmi=src._bfmi;
    _ffmi=src._ffmi;
    _waistHip=src._waistHip;
    _wellness=src._wellness;
    _ecwLegacy=src._ecwLegacy;
    _tbwLegacy=src._tbwLegacy;
    _ohy=src._ohy;
    _skMuscle=src._skMuscle;
    _cm=src._cm;
    _rext=src._rext;
    _rint=src._rint;
    _fc=src._fc;
    _alpha=src._alpha;
    _subjId=src._subjId;
    return(*this);
}
