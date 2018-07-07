#include"taskstream.h"
#include"../comm/singleton.h"
#include"taskproc.h"
#include"task.h"

TaskStream::~TaskStream(){
}

TaskStream *TaskStream::instance(){
    return(Singleton<TaskStream>::instance());
}

int TaskStream::addTask(PtrTask &task){
    if(task.isNull()||task->isValid()<0){
        return(-1);
    }
    _taskProcV[task->getProc()]->addTask(task);
    return(0);
}

TaskStream::TaskStream(QObject *parent/*=0*/)
    :QObject(parent)
    ,_taskProcV(){
    _taskProcV.push_back(PtrTaskProc(new TaskProc));
    connect(_taskProcV[0].data(),
        SIGNAL(taskFinished(unsigned int,int)),
        this,SLOT(onTaskFinished(unsigned int,int)));
}

void TaskStream::onTaskFinished(
    const unsigned int id,const int res){
    emit taskFinished(id,res);
}
