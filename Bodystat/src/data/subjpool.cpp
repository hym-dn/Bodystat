#include"subjpool.h"
#include"../comm/singleton.h"
#include"subject.h"
#include<QMutexLocker>
#include<QSqlQuery>

SubjPool::~SubjPool(){
    delete _curSubj;
}

SubjPool *SubjPool::instance(){
    return(Singleton<SubjPool>::instance());
}

void SubjPool::setCurSubj(const Subject &subj){
    {
        QMutexLocker lock(&_lock);
        *_curSubj=subj;
    }
    emit curSubjChanged();
}

const Subject &SubjPool::getCurSubj() const{
    QMutexLocker lock(&_lock);
    return(*_curSubj);
}

void SubjPool::clearCurSubj(){
    setCurSubj(Subject());
}

int SubjPool::pullSubjV(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    const QString sql("SELECT ID,Name,Birthday,Sex,"
        "TelNo,MobNo,Email,Addr,EntryDateTime,"
        "ModifyDateTime,AccessDateTime FROM Subject "
        "ORDER BY ID ASC;");
    QSqlQuery query(db);
    if(!query.exec(sql)){
        return(-2);
    }
    SubjV subjV;
    while(query.next()){
        PtrSubj subj(new Subject);
        if(subj.isNull()){
            return(-3);
        }
        if(subj->pull(query)<0){
            return(-4);
        }
        subjV.push_back(subj);
    }
    QMutexLocker locker(&_lock);
    _subjV.swap(subjV);
    return(0);
}

int SubjPool::getSubjVCount() const{
    QMutexLocker locker(&_lock);
    return(_subjV.count());
}

const Subject &SubjPool::getSubj(const int index) const{
    QMutexLocker locker(&_lock);
    Q_ASSERT(index>=0&&index<_subjV.count());
    Q_ASSERT(!_subjV.at(index).isNull());
    return(*(_subjV.at(index).data()));
}

QString SubjPool::getSubjBrief(const int index) const{
    QMutexLocker locker(&_lock);
    Q_ASSERT(index>=0&&index<_subjV.count());
    Q_ASSERT(!_subjV.at(index).isNull());
    return(_subjV.at(index)->getBrief());
}

void SubjPool::clearSubjV(){
    QMutexLocker locker(&_lock);
    _subjV.swap(SubjV());
}

SubjPool::SubjPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_curSubj(new Subject)
    ,_subjV(){
}
