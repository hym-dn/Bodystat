#ifndef TASK_H
#define TASK_H

#include<QSqlDatabase>

class Task{
public:
    Task();
    virtual ~Task();
public:
    virtual int isValid() const;
    virtual unsigned int getId() const=0;
    virtual int exec(QSqlDatabase &db)=0;
private:
    Task(const Task&);
    Task &operator=(const Task&);
};

#endif // TASK_H
