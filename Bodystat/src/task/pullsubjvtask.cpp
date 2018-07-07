#include"pullsubjvtask.h"
#include"../data/subjpool.h"

PullSubjVTask::PullSubjVTask()
    :Task(){
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
    if(!isValid()){
        return(-2);
    }
    if(SubjPool::instance()->pullSubjV(db)<0){
        return(-3);
    }
    return(0);
}
