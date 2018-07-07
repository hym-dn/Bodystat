#include"taskstream.h"
#include"../comm/singleton.h"
#include"taskproc.h"

TaskStream::~TaskStream(){
}

TaskStream *TaskStream::instance(){
    return(Singleton<TaskStream>::instance());
}

int TaskStream::addTask(PtrTask &task,const ProcTp tp){
    return(_taskProcV[tp]->addTask(task));
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
