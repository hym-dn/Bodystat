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
    typedef QSharedPointer<const TestData> PtrCTestData;
    typedef QVector<PtrTestData> TestDataV;
public:
    ~SubjPool();
public:
    static SubjPool *instance();
signals:
    void curSubjChanged();
    void curTestDataChanged();
public:
    int pull(QSqlDatabase &db);
    int push(QSqlDatabase &db,
        const SubjInfo &subjInfo,const bool isAdd);
    int erase(QSqlDatabase &db,const QString &subjId);
    int assign(QSqlDatabase &db,const int subjIdx,
        const TestDataV &testDataV);
    int unassign(QSqlDatabase &db);
    int unassign(QSqlDatabase &db,const int subjIdx,
        const int testDataIdx);
    int count() const;
    int getSubjInfo(const int idx,SubjInfo &subjInfo) const;
    void setCurSubj(const int subjIdx);
    void setCurSubj(const QString &subjId);
    int getCurSubjIdx() const;
    int getCurSubjInfo(SubjInfo &subjInfo) const;
    void setCurTestData(const int testDataIdx);
    PtrCTestData getCurTestData() const;
    int curTestDataCount() const;
    int getCurTestDataIdx() const;
    PtrCTestData getCurTestData(const int idx) const;
    bool containTestData(
        const unsigned int devModel,
        const unsigned long devSeriNum,
        const QDateTime &testDateTime) const;
private:
    friend class Singleton<SubjPool>;
    typedef QVector<PtrSubj> SubjV;
private:
    explicit SubjPool(QObject *parent=0);
private:
    SubjPool(const SubjPool&);
    SubjPool &operator=(const SubjPool&);
private:
    void addSubj(const PtrSubj &subj);
    void swapSubj(SubjV &subjV);
    bool containSubj(const QString &subjId) const;
    void sortSubj();
    PtrSubj findSubj(const QString &subjId);
private:
    mutable QMutex _lock;
    int _curSubj;
    int _curTestData;
    SubjV _subjV;
};

#endif // SUBJ_POOL_H
