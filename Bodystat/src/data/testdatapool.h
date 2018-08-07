#ifndef TEST_DATA_POOL_H
#define TEST_DATA_POOL_H

#include<QObject>
#include<QSharedPointer>
#include<QVector>
#include<QMutex>

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
    virtual ~TestDataPool();
public:
    static TestDataPool *instance();
public:
    void clear();
    int count() const;
    int add(QSqlDatabase &db,
        const Bodystat::BSMeasurement &mData);
private:
    typedef QSharedPointer<TestData> PtrToData;
    typedef QVector<PtrToData> DataV;
    friend class Singleton<TestDataPool>;
private:
    explicit TestDataPool(QObject *parent=0);
private:
    void add(PtrToData &data);
private:
    TestDataPool(const TestDataPool &);
    TestDataPool &operator=(const TestDataPool &);
private:
    mutable QMutex _lock;
    DataV _dataV;
};

#endif // TEST_DATA_POOL_H
