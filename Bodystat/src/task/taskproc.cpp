﻿#include"taskproc.h"
#include"task.h"
#include"../db/dbmanager.h"
#include<QMutexLocker>

TaskProc::TaskProc()
    :QObject(0)
    ,_thr()
    ,_lock(){
    moveToThread(&_thr);
    connect(this,SIGNAL(taskArrived()),
        this,SLOT(onTaskArrived()));
    _thr.start();
}

TaskProc::~TaskProc(){
    _thr.quit();
    _thr.wait();
}

void TaskProc::addTask(PtrTask &task){
    Q_ASSERT(!task.isNull()&&
        task->isValid()>=0);
    {
        QMutexLocker locker(&_lock);
        _taskQ.push_back(task);
    }
    emit taskArrived();
}

void TaskProc::onTaskArrived(){
    while(true){
        PtrTask task=popTask();
        if(task.isNull()){
            break;
        }
        const int res=task->exec(
            DBManager::instance()->
            getDB());
        emit taskFinished(
            task->getId(),res);
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
