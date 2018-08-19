#ifndef REPORT_TASK_H
#define REPORT_TASK_H

#include"task.h"
#include<QVector>

class ReportTask
    :public Task{
public:
    enum{ID=1002,};
    typedef QVector<int> TdIdxV;
public:
    explicit ReportTask(const TdIdxV &tdIdxV,
        const unsigned int proc=0);
    virtual ~ReportTask();
public:
    virtual unsigned int getId() const;
    virtual int exec(QSqlDatabase &db);
private:
    const TdIdxV _tdIdxV;
};

#endif // REPORT_TASK_H
