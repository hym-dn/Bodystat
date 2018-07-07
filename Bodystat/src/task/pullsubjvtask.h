#ifndef PULL_SUBJ_V_TASK_H
#define PULL_SUBJ_V_TASK_H

#include"task.h"

class PullSubjVTask
    :public Task{
public:
    enum{ID=1001,};
public:
    PullSubjVTask(const unsigned int proc);
    virtual ~PullSubjVTask();
public:
    virtual unsigned int getId() const;
    virtual int exec(QSqlDatabase &db);
};

#endif // PULL_SUBJ_V_TASK_H
