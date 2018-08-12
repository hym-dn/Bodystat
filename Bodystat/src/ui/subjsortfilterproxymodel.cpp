#include"subjsortfilterproxymodel.h"
#include"../data/subjinfo.h"
#include"../data/subject.h"
#include"../data/subjpool.h"

SubjSortFilterProxyModel::SubjSortFilterProxyModel(
    QObject *parent/*=Q_NULLPTR*/)
    :QSortFilterProxyModel(parent)
    ,_matchString(){
}

SubjSortFilterProxyModel::~SubjSortFilterProxyModel(){
}

void SubjSortFilterProxyModel::setMatchString(
    const QString &string){
    beginResetModel();
    _matchString=string;
    endResetModel();
}

const QString &SubjSortFilterProxyModel::
    getMatchString() const{
    return(_matchString);
}

bool SubjSortFilterProxyModel::filterAcceptsRow(
    int source_row,const QModelIndex &source_parent) const{
    if(_matchString.isEmpty()){
        return(true);
    }else{
        const QModelIndex srcIndex=sourceModel()->
            index(source_row,0,source_parent);
        SubjPool::PtrCSubj subj=SubjPool::instance()
            ->get(srcIndex.row());
        if(subj.isNull()){
            return(false);
        }else{
            return(((subj->getSubjInfo()).getBrief())
                .contains(_matchString));
        }
    }
}
