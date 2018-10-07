#ifndef TEST_STAT_TASK_H
#define TEST_STAT_TASK_H

#include"task.h"

class TestStatTask
    :public Task{
public:
    enum{ID=1003,};
public:
    TestStatTask(const unsigned int proc=0);
    virtual ~TestStatTask();
public:
    virtual unsigned int getId() const;
    virtual int exec(QSqlDatabase &db);
};

#endif // TEST_STAT_TASK_H
