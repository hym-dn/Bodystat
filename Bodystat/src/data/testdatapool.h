#ifndef TEST_DATA_POOL_H
#define TEST_DATA_POOL_H

#include<QObject>

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
    friend class Singleton<TestDataPool>;
private:
    explicit TestDataPool(QObject *parent=0);
};

#endif // TEST_DATA_POOL_H
