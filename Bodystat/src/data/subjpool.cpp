#include"subjpool.h"
#include"../comm/singleton.h"
#include"subject.h"
#include<QMutexLocker>

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

SubjPool::SubjPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_curSubj(new Subject){
}
