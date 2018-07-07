#ifndef TASK_H
#define TASK_H

#include<QSqlDatabase>

class Task{
public:
    Task(const unsigned int proc);
    virtual ~Task();
public:
    unsigned int getProc() const;
public:
    virtual int isValid() const;
    virtual unsigned int getId() const=0;
    virtual int exec(QSqlDatabase &db)=0;
private:
    Task(const Task&);
    Task &operator=(const Task&);
private:
    const unsigned int _proc;
};

#endif // TASK_H
