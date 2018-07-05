#include"taskstream.h"
#include"../comm/singleton.h"
#include"taskproc.h"

TaskStream::~TaskStream(){
}

TaskStream *TaskStream::instance(){
    return(Singleton<TaskStream>::instance());
}

int TaskStream::addTask(
    const PtrTask &task,const ProcTp tp){
    switch(tp){
    case PROC_TP_ROUTINE:
        //return(_taskProcQ[])
        break;
    }
}

TaskStream::TaskStream()
    :_taskProcQ(){
    _taskProcQ.push_back(
        PtrTaskProc(new TaskProc));
}
