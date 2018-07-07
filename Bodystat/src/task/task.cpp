#include"task.h"

Task::Task(const unsigned int proc)
    :_proc(proc){
}

Task::~Task(){
}

unsigned int Task::getProc() const{
    return(_proc);
}

int Task::isValid() const{
    return(0);
}
