#ifndef TEST_DATA_POOL_H
#define TEST_DATA_POOL_H

#include<QObject>
#include<QSharedPointer>
#include<QVector>
#include<QMutex>
#include<QSet>

template<typename T>
class Singleton;
class TestData;
class QSqlDatabase;
namespace Bodystat{
    struct BSMeasurement;
}

class TestDataPool
    :public QObject{
    Q_OBJECT
public:
    typedef QSharedPointer<const TestData> PtrToCData;
public:
    virtual ~TestDataPool();
public:
    static TestDataPool *instance();
public:
    int pull(QSqlDatabase &db);
    int assign(QSqlDatabase &db,const int subjIdx,
        const QSet<int> &tdIdxS);
    void clear();
    int count() const;
    int add(QSqlDatabase &db,
        const Bodystat::BSMeasurement &mData);
    PtrToCData getData(const int idx);
private:
    typedef QSharedPointer<TestData> PtrToData;
    typedef QVector<PtrToData> DataV;
    friend class Singleton<TestDataPool>;
private:
    explicit TestDataPool(QObject *parent=0);
private:
    void add(PtrToData &data);
    void swap(DataV &dataV);
    bool contain(const unsigned int devModel,
        const unsigned int devSeriNum,
        const QDateTime &testDateTime) const;
private:
    TestDataPool(const TestDataPool &);
    TestDataPool &operator=(const TestDataPool &);
private:
    mutable QMutex _lock;
    DataV _dataV;
};

#endif // TEST_DATA_POOL_H
