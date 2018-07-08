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
    void clearCurSubj();
    int pullSubjV(QSqlDatabase &db);
    int getSubjVCount() const;
    const Subject &getSubj(const int index) const;
    QString getSubjBrief(const int index) const;
    void clearSubjV();
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
