#ifndef SUBJ_POOL_H
#define SUBJ_POOL_H

#include<QObject>
#include<QMutex>
#include<QVector>
#include<QSharedPointer>
#include<QSqlDatabase>

template<typename T>
class Singleton;
class Subject;

class SubjPool
    :public QObject{
    Q_OBJECT
public:
    typedef QSharedPointer<Subject> PtrSubj;
    typedef QVector<PtrSubj> SubjV;
public:
    ~SubjPool();
public:
    static SubjPool *instance();
signals:
    void curSubjChanged();
public:
    void setCurSubj(const Subject &subj);
    const Subject &getCurSubj() const;
    int pullSubjV(QSqlDatabase &db);
private:
    friend class Singleton<SubjPool>;
private:
    explicit SubjPool(QObject *parent=0);
private:
    SubjPool(const SubjPool&);
    SubjPool &operator=(const SubjPool&);
private:
    mutable QMutex _lock;
    Subject *_curSubj;
    SubjV _subjV;
};

#endif // SUBJ_POOL_H
