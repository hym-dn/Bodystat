#ifndef TASK_POOL_H
#define TASK_POOL_H

#include<QObject>
#include<QVector>
#include<QSharedPointer>

template<typename T>
class Singleton;
class TaskProc;
class Task;

class TaskPool
    :public QObject{
    Q_OBJECT
public:
    typedef QSharedPointer<Task> PtrTask;
public:
    ~TaskPool();
signals:
    void taskDone(const unsigned int id,const int err);
public:
    static TaskPool *instance();
public:
    int add(PtrTask &task);
private:
    friend class Singleton<TaskPool>;
    typedef QSharedPointer<TaskProc> PtrTaskProc;
    typedef QVector<PtrTaskProc> TaskProcV;
private:
    TaskPool(QObject *parent=0);
private:
    TaskPool(const TaskPool&);
    TaskPool &operator=(const TaskPool&);
private slots:
    void onTaskDone(const unsigned int id,const int err);
private:
    TaskProcV _taskProcV;
};

#endif // TASK_POOL_H
