#include"taskpool.h"
#include"../comm/singleton.h"
#include"taskproc.h"
#include"task.h"

TaskPool::~TaskPool(){
}

TaskPool *TaskPool::instance(){
    return(Singleton<TaskPool>::instance());
}

int TaskPool::add(PtrTask &task){
    if((task.isNull())||(
        task->isValid()<0)){
        return(-1);
    }
    _taskProcV[task->getProc()]->
        addTask(task);
    return(0);
}

TaskPool::TaskPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_taskProcV(){
    _taskProcV.push_back(PtrTaskProc(new TaskProc));
    connect(_taskProcV[0].data(),SIGNAL(taskDone(
        const unsigned int,const int)),this,SLOT(
        onTaskDone(const unsigned int,const int)));
}

void TaskPool::onTaskDone(
    const unsigned int id,const int err){
    emit taskDone(id,err);
}
