#include"testdatapool.h"
#include"../comm/singleton.h"

TestDataPool::~TestDataPool(){
}

TestDataPool *TestDataPool::instance(){
    return(Singleton<TestDataPool>::instance());
}

TestDataPool::TestDataPool(QObject *parent/*=0*/)
    :QObject(parent)
    ,_lock()
    ,_testDataV(){
}
