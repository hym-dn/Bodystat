#include"taskproc.h"
#include"task.h"
#include"../db/dbmanager.h"
#include<QMutexLocker>

TaskProc::TaskProc()
    :QObject(0)
    ,_thr()
    ,_lock(){
    moveToThread(&_thr);
    connect(this,SIGNAL(task()),
        this,SLOT(onTask()));
    _thr.start();
}

TaskProc::~TaskProc(){
    _thr.quit();
    _thr.wait();
}

void TaskProc::addTask(PtrTask &tsk){
    Q_ASSERT((!tsk.isNull())&&(
        tsk->isValid()>=0));
    {
        QMutexLocker locker(&_lock);
        _taskQ.push_back(tsk);
    }
    emit task();
}

void TaskProc::onTask(){
    while(true){
        PtrTask task=popTask();
        if(task.isNull()){
            break;
        }
        const int err=task->exec(
            DBManager::instance()->getDB());
        emit taskDone(task->getId(),err);
    }
}

TaskProc::PtrTask TaskProc::popTask(){
    QMutexLocker locker(&_lock);
    if(_taskQ.isEmpty()){
        return(PtrTask());
    }else{
        PtrTask task=_taskQ.front();
        _taskQ.pop_front();
        return(task);
    }
}
