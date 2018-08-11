#ifndef TASK_PROC_H
#define TASK_PROC_H

#include<QObject>
#include<QThread>
#include<QMutex>
#include<QQueue>
#include<QSharedPointer>

class Task;

class TaskProc
    :public QObject{
    Q_OBJECT
public:
    typedef QSharedPointer<Task> PtrTask;
public:
    TaskProc();
    ~TaskProc();
signals:
    void task();
    void taskDone(const unsigned int id,const int err);
public:
    void setId(const unsigned int id);
    unsigned int getId() const;
    void addTask(PtrTask &tsk);
private:
    typedef QQueue<PtrTask> TaskQ;
private:
    TaskProc(const TaskProc&);
    TaskProc &operator=(const TaskProc&);
private slots:
    void onTask();
private:
    PtrTask popTask();
private:
    QThread _thr;
    mutable QMutex _lock;
    TaskQ _taskQ;
};

#endif // TASK_PROC_H
