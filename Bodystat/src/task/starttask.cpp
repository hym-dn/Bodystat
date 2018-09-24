#include"starttask.h"
#include"../data/subjpool.h"
#include"../data/testdatapool.h"
#include"../data/sysinfopool.h"
#include<QTime>
#include<QThread>

StartTask::StartTask(const unsigned int proc/*=0*/)
    :Task(proc){
}

StartTask::~StartTask(){
}

unsigned int StartTask::getId() const{
    return(ID);
}

int StartTask::exec(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(isValid()<0){
        return(-2);
    }
    QTime tm;
    tm.start();
    if(SysInfoPool::instance()->pull(db)<0){
        return(-3);
    }
    if(SubjPool::instance()->pull(db)<0){
        return(-4);
    }
    if(TestDataPool::instance()->pull(db)<0){
        return(-5);
    }
    const int ms=tm.elapsed();
    if(ms<2000){
        QThread::msleep(2000-ms);
    }
    return(0);
}
