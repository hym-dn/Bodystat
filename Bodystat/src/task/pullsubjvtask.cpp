#include"pullsubjvtask.h"
#include"../data/subjpool.h"
#include<QTime>
#include<QThread>

PullSubjVTask::PullSubjVTask(
    const unsigned int proc,
    const bool isDelay/*=false*/)
    :Task(proc)
    ,_isDelay(isDelay){
}

PullSubjVTask::~PullSubjVTask(){
}

unsigned int PullSubjVTask::getId() const{
    return(ID);
}

int PullSubjVTask::exec(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(isValid()<0){
        return(-2);
    }
    QTime tm;
    if(_isDelay){
        tm.start();
    }
    if(SubjPool::instance()->pull(db)<0){
        return(-3);
    }
    if(_isDelay){
        const int ms=tm.elapsed();
        if(ms<2000){
            QThread::msleep(2000-ms);
        }
    }
    return(0);
}
