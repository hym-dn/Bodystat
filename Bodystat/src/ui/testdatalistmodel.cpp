#include"testdatalistmodel.h"
#include"../data/subjpool.h"
#include"../data/testdata.h"

TestDataListModel::TestDataListModel(QObject *parent/*=0*/)
    :QAbstractListModel(parent){
}

TestDataListModel::~TestDataListModel(){
}

void TestDataListModel::update(){
    beginResetModel();
    endResetModel();
}

int TestDataListModel::rowCount(const QModelIndex &/*parent*/) const{
    return(SubjPool::instance()->getCurTestDataCount());
}

QVariant TestDataListModel::data(const QModelIndex &index,int role) const{
    if(!index.isValid()){
        return(QVariant());
    }else if(Qt::DisplayRole==role){
        SubjPool::PtrCTestData testData=SubjPool::
            instance()->getCurTestData(index.row());
        if(testData.isNull()){
            return(QVariant());
        }else{
            return(testData->getTestDateTimeText());
        }
    }else{
        return QVariant();
    }
}
