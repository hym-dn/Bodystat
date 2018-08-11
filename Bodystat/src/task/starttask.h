#ifndef STAR_TTASK_H
#define STAR_TTASK_H

#include"task.h"

class StartTask
    :public Task{
public:
    enum{ID=1001,};
public:
    StartTask(const unsigned int proc=0);
    virtual ~StartTask();
public:
    virtual unsigned int getId() const;
    virtual int exec(QSqlDatabase &db);
};

#endif // STAR_TTASK_H
