#include"cursubjtest.h"
#include"../comm/singleton.h"
#include"../data/subject.h"
#include<QMutexLocker>

CurSubjTest::~CurSubjTest(){
    delete _subj;
}

CurSubjTest *CurSubjTest::instance(){
    return(Singleton<CurSubjTest>::instance());
}

void CurSubjTest::setSubj(const Subject &subj){
    {
        QMutexLocker lock(&_lock);
        *_subj=subj;
    }
    emit subjChanged();
}

const Subject &CurSubjTest::getSubj() const{
    QMutexLocker lock(&_lock);
    return(*_subj);
}

CurSubjTest::CurSubjTest(QObject *parent/*=0*/)
    :QObject(parent)
    ,_subj(new Subject){
}
