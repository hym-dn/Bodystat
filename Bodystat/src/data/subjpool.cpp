#include"subjpool.h"
#include"../comm/singleton.h"
#include"subjinfo.h"
#include"subject.h"
#include"../db/dbmanager.h"
#include<QMutexLocker>
#include<QSqlQuery>
#include<QtAlgorithms>

static bool subjLessThan(const SubjPool::PtrSubj &l,
    const SubjPool::PtrSubj &r){
    return(l->getSubjInfo().getAccsDt()>r->
        getSubjInfo().getAccsDt());
}

SubjPool::~SubjPool(){
}

SubjPool *SubjPool::instance(){
    return(Singleton<SubjPool>::instance());
}

int SubjPool::pull(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    const QString sql(
        "SELECT Subject.ID,Subject.Name,Subject.Birthday,"
        "Subject.Sex,Subject.TelNo,Subject.MobNo,Subject.Email,"
        "Subject.Addr,Subject.EntryDateTime,Subject.ModifyDateTime,"
        "Subject.AccessDateTime,TestData.DevModel,TestData.DevSeriNum,"
        "TestData.TestDateTime,TestData.Sex,TestData.Age,TestData.Height,"
        "TestData.Weight,TestData.Activity,TestData.Waist,TestData.Hip,"
        "TestData.Iz5kHz,TestData.IZ50kHz,TestData.Iz100kHz,TestData.Iz200kHz,"
        "TestData.Ir50kHz,TestData.Fx50kHz,TestData.Fpa50kHz,TestData.FatPerc,"
        "TestData.FatKg,TestData.LeanPerc,TestData.LeanKg,TestData.TotalWeight,"
        "TestData.DryLW,TestData.TBWPerc,TestData.TBW,TestData.ECWPerc,TestData.ECW,"
        "TestData.ICWPerc,TestData.ICW,TestData.BCM,TestData.ThirdSpace,"
        "TestData.Nutrition,TestData.Illness,TestData.BMR,TestData.BMRKg,TestData.EstAvg,"
        "TestData.BMI,TestData.BFMI,TestData.FFMI,TestData.WaistHip,TestData.Wellness,"
        "TestData.ECWLegacy,TestData.TBWLegacy,TestData.OHY,TestData.SkMuscle,"
        "TestData.Cm,TestData.Rext,TestData.Rint,TestData.FC,TestData.Alpha,"
        "TestData.SubjectID FROM Subject LEFT JOIN TestData ON "
        "Subject.ID=TestData.SubjectID ORDER BY Subject.AccessDateTime DESC,"
        "Subject.ID ASC,TestData.DevModel ASC,TestData.DevSeriNum ASC,"
        "TestData.TestDateTime ASC;");
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    SubjV subjV;
    if(query.next()){
        while(true){
            PtrSubj subj(new Subject);
            if(subj.isNull()){
                return(-3);
            }
            const int res=subj->pull(query);
            if(res<0){
                return(-4);
            }
            subjV.push_back(subj);
            if(0==res){
                break;
            }
        }
    }
    swapSubj(subjV);
    return(0);
}

int SubjPool::push(QSqlDatabase &db,
    const SubjInfo &subjInfo,const bool isAdd){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(subjInfo.isValid()<0){
        return(-2);
    }
    QSqlQuery query(db);
    if(isAdd){
        if(containSubj(subjInfo.getId())){ // 冲突
            return(1);
        }
        PtrSubj subj(new Subject);
        if(subj.isNull()){
            return(-3);
        }
        if(subj->push(query,subjInfo,true)<0){
            return(-4);
        }
        addSubj(subj);
        sortSubj();
    }else{
        QMutexLocker locker(&_lock);
        PtrSubj subj=findSubj(subjInfo.getId());
        if(subj.isNull()){
            return(-5);
        }
        if(subj->push(query,subjInfo,false)<0){
            return(-6);
        }
    }    
    return(0);
}

int SubjPool::erase(QSqlDatabase &db,const QString &subjId){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(subjId.isEmpty()){
        return(-2);
    }
    QMutexLocker locker(&_lock);
    for(SubjV::iterator itr=_subjV.begin();
        itr!=_subjV.end();++itr){
        if(subjId==(*itr)->getSubjInfo().getId()){
            QSqlQuery query(db);
            if((*itr)->erase(query)<0){
                return(-3);
            }
            _subjV.erase(itr);
            return(0);
        }
    }
    return(-4);
}

int SubjPool::assign(QSqlDatabase &db,
    const int subjIdx,const TestDataV &testDataV){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    QMutexLocker locker(&_lock);
    if(subjIdx<0||subjIdx>=_subjV.count()){
        return(-2);
    }
    QSqlQuery query(db);
    if(_subjV[subjIdx]->assign(query,testDataV)<0){
        return(-3);
    }
    return(0);
}

int SubjPool::unassign(QSqlDatabase &db){
    return(unassign(db,getCurSubjIdx(),getCurTestDataIdx()));
}

int SubjPool::unassign(QSqlDatabase &db,
    const int subjIdx,const int testDataIdx){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    QMutexLocker locker(&_lock);
    if(subjIdx<0||subjIdx>=_subjV.count()){
        return(-2);
    }
    QSqlQuery query(db);
    if(_subjV[subjIdx]->unassign(query,testDataIdx)<0){
        return(-3);
    }
    return(0);
}

int SubjPool::count() const{
    QMutexLocker locker(&_lock);
    return(_subjV.count());
}

int SubjPool::getSubjInfo(const int idx,
    SubjInfo &subjInfo) const{
    QMutexLocker locker(&_lock);
    if(idx<0||idx>=_subjV.count()){
        return(-1);
    }else{
        subjInfo=_subjV.at(idx)->getSubjInfo();
        return(0);
    }
}

void SubjPool::setCurSubj(const int subjIdx){
    QString subjId;
    {
        QMutexLocker locker(&_lock);
        if(subjIdx>=0&&subjIdx<_subjV.count()){
            subjId=_subjV[subjIdx]->getSubjInfo().getId();
        }
    }
    setCurSubj(subjId);
}

void SubjPool::setCurSubj(const QString &subjId){
    if(subjId.isEmpty()){
        {
            QMutexLocker locker(&_lock);
            _curSubj=-1;
            _curTestData=-1;
        }
        emit curSubjChanged();
        emit curTestDataChanged();
        return;
    }
    {
        QMutexLocker locker(&_lock);
        PtrSubj subj=findSubj(subjId);
        if(subj.isNull()){
            _curSubj=-1;
            _curTestData=-1;
            emit curSubjChanged();
            emit curTestDataChanged();
            return;
        }
        QSqlQuery query(DBManager::instance()->getDB());
        subj->updateAccsDt(query,QDateTime::currentDateTime());
        qSort(_subjV.begin(),_subjV.end(),subjLessThan);
        for(int i=0;i<_subjV.count();++i){
            if(subjId==_subjV.at(i)->getSubjInfo().getId()){
                _curSubj=i;
                _curTestData=-1;
                break;
            }
        }
    }
    emit curSubjChanged();
    emit curTestDataChanged();
}

int SubjPool::getCurSubjIdx() const{
    QMutexLocker locker(&_lock);
    return(_curSubj);
}

int SubjPool::getCurSubjInfo(SubjInfo &subjInfo) const{
    QMutexLocker locker(&_lock);
    if(_curSubj<0||_curSubj>=_subjV.count()){
        return(-1);
    }else{
        subjInfo=_subjV.at(_curSubj)->getSubjInfo();
        return(0);
    }
}

void SubjPool::setCurTestData(const int testDataIdx){
    {
        QMutexLocker locker(&_lock);
        _curTestData=testDataIdx;
    }
    emit curTestDataChanged();
}

SubjPool::PtrCTestData SubjPool::getCurTestData() const{
    return(getCurTestData(getCurTestDataIdx()));
}

bool SubjPool::containTestData(const unsigned int devModel,
    const unsigned long devSeriNum,const QDateTime &testDateTime) const{
    QMutexLocker locker(&_lock);
    for(SubjV::const_iterator itr=_subjV.begin();itr!=_subjV.end();++itr){
        if((*itr)->containTestData(devModel,devSeriNum,testDateTime)){
            return(true);
        }
    }
    return(false);
}

int SubjPool::curTestDataCount() const{
    QMutexLocker locker(&_lock);
    if(_curSubj<0||_curSubj>=_subjV.count()){
        return(0);
    }else{
        return(_subjV.at(_curSubj)->testDataCount());
    }
}

int SubjPool::getCurTestDataIdx() const{
    QMutexLocker locker(&_lock);
    return(_curTestData);
}

SubjPool::PtrCTestData SubjPool::getCurTestData(const int idx) const{
    QMutexLocker locker(&_lock);
    if(_curSubj<0||_curSubj>=_subjV.count()){
        return(PtrCTestData());
    }else{
        return(_subjV.at(_curSubj)->getTestData(idx));
    }
}

SubjPool::SubjPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_curSubj(-1)
    ,_curTestData(-1)
    ,_subjV(){
}

void SubjPool::addSubj(const PtrSubj &subj){
    QMutexLocker locker(&_lock);
    _subjV.push_back(subj);
}

void SubjPool::swapSubj(SubjV &subjV){
    QMutexLocker locker(&_lock);
    _subjV.swap(subjV);
}

bool SubjPool::containSubj(const QString &subjId) const{
    QMutexLocker locker(&_lock);
    for(SubjV::const_iterator itr=_subjV.begin();
        itr!=_subjV.end();++itr){
        if((*itr)->getSubjInfo().getId()==subjId){
            return(true);
        }
    }
    return(false);
}

void SubjPool::sortSubj(){
    QMutexLocker locker(&_lock);
    qSort(_subjV.begin(),_subjV.end(),subjLessThan);
}

SubjPool::PtrSubj SubjPool::findSubj(const QString &subjId){
    for(SubjV::iterator itr=_subjV.begin();
        itr!=_subjV.end();++itr){
        if((*itr)->getSubjInfo().getId()==subjId){
            return(*itr);
        }
    }
    return(PtrSubj());
}
