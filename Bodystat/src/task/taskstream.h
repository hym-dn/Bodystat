#ifndef TASK_STREAM_H
#define TASK_STREAM_H

#include<QQueue>
#include<QSharedPointer>

template<typename T>
class Singleton;
class TaskProc;
class Task;

class TaskStream{
public:
    typedef enum{
        PROC_TP_ROUTINE=0,
    }ProcTp;
    typedef QSharedPointer<Task> PtrTask;
public:
    ~TaskStream();
public:
    static TaskStream *instance();
public:
    int addTask(const PtrTask &task,
        const ProcTp tp);
private:
    friend class Singleton<TaskStream>;
    typedef QSharedPointer<TaskProc> PtrTaskProc;
    typedef QQueue<PtrTaskProc> TaskProcQ;
private:
    TaskStream();
private:
    TaskStream(const TaskStream&);
    TaskStream &operator=(const TaskStream&);
private:
    TaskProcQ _taskProcQ;
};

#endif // TASK_STREAM_H
