#include"subjlistmodel.h"
#include"../data/subjpool.h"

SubjListModel::SubjListModel(
    QObject *parent/*=0*/)
    :QAbstractListModel(parent){
}

SubjListModel::~SubjListModel(){
}

int SubjListModel::rowCount(
    const QModelIndex &/*parent*/) const{
    return(SubjPool::instance()->getSubjVCount());
}

QVariant SubjListModel::data(
    const QModelIndex &index,int role) const{
    if(!index.isValid()){
        return(QVariant());
    }else if(Qt::DisplayRole==role){
        return(SubjPool::instance()->
            getSubjBrief(index.row()));
    }else{
        return QVariant();
    }
}
