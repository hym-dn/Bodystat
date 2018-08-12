#ifndef PULL_SUBJ_V_TASK_H
#define PULL_SUBJ_V_TASK_H

#include"task.h"

class PullSubjVTask
    :public Task{
public:
    enum{ID=1002,};
public:
    PullSubjVTask(
        const unsigned int proc,
        const bool isDelay=false);
    virtual ~PullSubjVTask();
public:
    virtual unsigned int getId() const;
    virtual int exec(QSqlDatabase &db);
private:
    bool _isDelay;
};

#endif // PULL_SUBJ_V_TASK_H
