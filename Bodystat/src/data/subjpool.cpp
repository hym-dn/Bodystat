#include"subjpool.h"
#include"../comm/singleton.h"
#include"subjinfo.h"
#include"subject.h"
#include<QMutexLocker>
#include<QSqlQuery>
#include<QtAlgorithms>

static bool subjLessThan(
    const SubjPool::PtrSubj &l,const SubjPool::PtrSubj &r){
    return(l->getSubjInfo().getEntrDt()<
        r->getSubjInfo().getEntrDt());
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
        "Subject.ID=TestData.SubjectID ORDER BY Subject.EntryDateTime ASC,"
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
            if(0==res){ // 记录尾
                break;
            }
        }
    }
    swap(subjV);
    return(0);
}

int SubjPool::push(QSqlDatabase &db,
    const SubjInfo &info,const bool isAdd){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(info.isValid()<0){
        return(-2);
    }
    QSqlQuery query(db);
    if(isAdd){
        if(contain(info.getId())){
            return(1);
        }
        PtrSubj subj(new Subject);
        if(subj.isNull()){
            return(-3);
        }
        if(subj->push(query,info,true)<0){
            return(-4);
        }
        add(subj);
        sort();
    }else{
        QMutexLocker locker(&_lock);
        PtrSubj subj=find(info.getId());
        if(subj.isNull()){
            return(-5);
        }
        if(subj->push(query,info,false)<0){
            return(-6);
        }
    }
    return(0);
}

int SubjPool::erase(QSqlDatabase &db,
    const QString &subjId){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(subjId.isEmpty()){
        return(-2);
    }
    QMutexLocker locker(&_lock);
    for(SubjV::iterator itr=_subjV.begin();
        itr!=_subjV.end();++itr){
        if((*itr)->getSubjInfo().getId()==subjId){
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

int SubjPool::count() const{
    QMutexLocker locker(&_lock);
    return(_subjV.count());
}

SubjPool::PtrCSubj SubjPool::get(const int i) const{
    QMutexLocker locker(&_lock);
    if(i<0||i>=_subjV.count()){
        return(PtrCSubj());
    }else{
        return(_subjV.at(i));
    }
}

void SubjPool::setCur(const int iSubj){
    {
        QMutexLocker locker(&_lock);
        _curSubj=iSubj;
    }
    emit curSubjChanged();
}

void SubjPool::setCur(const QString &subjId){
    {
        QMutexLocker locker(&_lock);
        for(int i=0;i<_subjV.count();++i){
            if(subjId==_subjV.at(i)->getSubjInfo().getId()){
                _curSubj=i;
            }
        }
    }
    emit curSubjChanged();
}

SubjPool::PtrCSubj SubjPool::getCur() const{
    QMutexLocker locker(&_lock);
    if(_curSubj<0||_curSubj>=_subjV.count()){
        return(PtrCSubj());
    }else{
        return(_subjV.at(_curSubj));
    }
}

SubjPool::SubjPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_curSubj(-1)
    ,_subjV(){
}

void SubjPool::add(const PtrSubj &subj){
    QMutexLocker locker(&_lock);
    _subjV.push_back(subj);
}

void SubjPool::swap(SubjV &subjV){
    QMutexLocker locker(&_lock);
    _subjV.swap(subjV);
}

bool SubjPool::contain(const QString &subjId) const{
    QMutexLocker locker(&_lock);
    for(SubjV::const_iterator itr=_subjV.begin();
        itr!=_subjV.end();++itr){
        if((*itr)->getSubjInfo().getId()==subjId){
            return(true);
        }
    }
    return(false);
}

SubjPool::PtrSubj SubjPool::find(const QString &subjId){
    for(SubjV::iterator itr=_subjV.begin();
        itr!=_subjV.end();++itr){
        if((*itr)->getSubjInfo().getId()==subjId){
            return(*itr);
        }
    }
    return(PtrSubj());
}

void SubjPool::sort(){
    QMutexLocker locker(&_lock);
    qSort(_subjV.begin(),_subjV.end(),
        subjLessThan);
}
