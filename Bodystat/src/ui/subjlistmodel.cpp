#include"subjlistmodel.h"
#include"../data/subjinfo.h"
#include"../data/subject.h"
#include"../data/subjpool.h"

SubjListModel::SubjListModel(
    QObject *parent/*=0*/)
    :QAbstractListModel(parent){
}

SubjListModel::~SubjListModel(){
}

int SubjListModel::rowCount(
    const QModelIndex &/*parent*/) const{
    return(SubjPool::instance()->count());
}

QVariant SubjListModel::data(
    const QModelIndex &index,int role) const{
    if(!index.isValid()){
        return(QVariant());
    }else if(Qt::DisplayRole==role){
        SubjPool::PtrCSubj subj=SubjPool::
            instance()->get(index.row());
        if(subj.isNull()){
            return(QVariant());
        }else{
            return(subj->getSubjInfo().getBrief());
        }
    }else{
        return QVariant();
    }
}
