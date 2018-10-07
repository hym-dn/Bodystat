#include"teststatlistmodel.h"
#include"../data/testdatapool.h"
#include"../data/testdata.h"

TestStatListModel::TestStatListModel(
    QObject *parent/*=0*/)
    :QAbstractListModel(parent){
}

TestStatListModel::~TestStatListModel(){
}

int TestStatListModel::rowCount(
    const QModelIndex &/*parent*/) const{
    return(TestDataPool::instance()->count_t());
}

QVariant TestStatListModel::data(
    const QModelIndex &index,int role) const{
    if(!index.isValid()){
        return(QVariant());
    }else if(Qt::DisplayRole==role){
        TestDataPool::PtrToCData test=
            TestDataPool::instance()->
            getData_t(index.row());
        if(test.isNull()){
            return(QVariant());
        }else{
            return(test->getBrief());
        }
    }else{
        return QVariant();
    }
}
