#ifndef SUBJ_POOL_H
#define SUBJ_POOL_H

#include<QObject>
#include<QMutex>
#include<QVector>
#include<QSharedPointer>
#include<QSqlDatabase>

template<typename T>
class Singleton;
class SubjInfo;
class Subject;
class TestData;

class SubjPool
    :public QObject{
    Q_OBJECT
public:
    typedef QSharedPointer<Subject> PtrSubj;
    typedef QSharedPointer<const Subject> PtrCSubj;
    typedef QSharedPointer<TestData> PtrTestData;
    typedef QVector<PtrTestData> TestDataV;
public:
    ~SubjPool();
public:
    static SubjPool *instance();
signals:
    void curSubjChanged();
public:
    int pull(QSqlDatabase &db);
    int push(QSqlDatabase &db,
        const SubjInfo &info,const bool isAdd);
    int erase(QSqlDatabase &db,
        const QString &subjId);
    int assign(QSqlDatabase &db,const int subjIdx,
        const TestDataV &testDataV);
    int count() const;
    PtrCSubj get(const int idx) const;
    void setCur(const int iSubj);
    void setCur(const QString &subjId);
    PtrCSubj getCur() const;
private:
    friend class Singleton<SubjPool>;
    typedef QVector<PtrSubj> SubjV;
private:
    explicit SubjPool(QObject *parent=0);
private:
    SubjPool(const SubjPool&);
    SubjPool &operator=(const SubjPool&);
private:
    void add(const PtrSubj &subj);
    void swap(SubjV &subjV);
    bool contain(const QString &subjId) const;
    PtrSubj find(const QString &subjId);
    void sort();
private:
    mutable QMutex _lock;
    int _curSubj;
    SubjV _subjV;
};

#endif // SUBJ_POOL_H
