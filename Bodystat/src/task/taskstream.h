#ifndef TASK_STREAM_H
#define TASK_STREAM_H

#include<QObject>
#include<QVector>
#include<QSharedPointer>

template<typename T>
class Singleton;
class TaskProc;
class Task;

class TaskStream
    :public QObject{
    Q_OBJECT
public:
    enum{PROC_ROUTINE=0,};
    typedef QSharedPointer<Task> PtrTask;
public:
    ~TaskStream();
signals:
    void taskFinished(
        const unsigned int id,
        const int res);
public:
    static TaskStream *instance();
public:
    int addTask(PtrTask &task);
private:
    friend class Singleton<TaskStream>;
    typedef QSharedPointer<TaskProc> PtrTaskProc;
    typedef QVector<PtrTaskProc> TaskProcV;
private:
    TaskStream(QObject *parent=0);
private:
    TaskStream(const TaskStream&);
    TaskStream &operator=(const TaskStream&);
private slots:
    void onTaskFinished(
        const unsigned int id,const int res);
private:
    TaskProcV _taskProcV;
};

#endif // TASK_STREAM_H
