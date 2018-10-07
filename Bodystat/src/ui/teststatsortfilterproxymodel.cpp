#include"teststatsortfilterproxymodel.h"
#include"../data/testdata.h"
#include"../data/testdatapool.h"

TestStatSortFilterProxyModel::TestStatSortFilterProxyModel(
    QObject *parent/*=Q_NULLPTR*/)
    :QSortFilterProxyModel(parent)
    ,_matchString(){
}

TestStatSortFilterProxyModel::~TestStatSortFilterProxyModel(){
}

void TestStatSortFilterProxyModel::setMatchString(
    const QString &string){
    beginResetModel();
    _matchString=string;
    endResetModel();
}

const QString &TestStatSortFilterProxyModel::
    getMatchString() const{
    return(_matchString);
}

bool TestStatSortFilterProxyModel::filterAcceptsRow(
    int source_row,const QModelIndex &source_parent) const{
    if(_matchString.isEmpty()){
        return(true);
    }else{
        const QModelIndex srcIndex=sourceModel()->
            index(source_row,0,source_parent);
        TestDataPool::PtrToCData test=
            TestDataPool::instance()->getData_t(srcIndex.row());
        if(test.isNull()){
            return(false);
        }else{
            return(test->getBrief().contains(_matchString));
        }
    }
}
