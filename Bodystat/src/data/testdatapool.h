#ifndef TEST_DATA_POOL_H
#define TEST_DATA_POOL_H

#include<QObject>
#include<QSharedPointer>
#include<QVector>
#include<QMutex>

template<typename T>
class Singleton;
class TestData;

class TestDataPool
    :public QObject{
    Q_OBJECT
public:
    virtual ~TestDataPool();
public:
    static TestDataPool *instance();
private:
    typedef QSharedPointer<TestData> PtrTestData;
    typedef QVector<PtrTestData> TestDataV;
    friend class Singleton<TestDataPool>;
private:
    explicit TestDataPool(QObject *parent=0);
private:
    TestDataPool(const TestDataPool &);
    TestDataPool &operator=(const TestDataPool &);
private:
    QMutex _lock;
    TestDataV _testDataV;
};

#endif // TEST_DATA_POOL_H
