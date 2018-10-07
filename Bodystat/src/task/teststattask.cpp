#include"teststattask.h"
#include"../data/testdatapool.h"
#include<QTime>
#include<QThread>

TestStatTask::TestStatTask(const unsigned int proc/*=0*/)
    :Task(proc){
}

TestStatTask::~TestStatTask(){
}

unsigned int TestStatTask::getId() const{
    return(ID);
}

int TestStatTask::exec(QSqlDatabase &db){
    if(!db.isValid()||!db.isOpen()){
        return(-1);
    }
    if(isValid()<0){
        return(-2);
    }
    QTime tm;
    tm.start();
    if(TestDataPool::instance()->pull_t(db)<0){
        return(-3);
    }
    const int ms=tm.elapsed();
    if(ms<2000){
        QThread::msleep(2000-ms);
    }
    return(0);
}
