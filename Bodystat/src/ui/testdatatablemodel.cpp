#include"testdatatablemodel.h"
#include"../data/testdatapool.h"

TestDataTableModel::TestDataTableModel(
    QObject *parent/*=0*/)
    :QAbstractTableModel(parent){
}

TestDataTableModel::~TestDataTableModel(){
}

QVariant TestDataTableModel::headerData(
    int section,Qt::Orientation orientation,
    int role) const{
    //水平表头
    if((Qt::Horizontal==orientation)&&(
        Qt::DisplayRole==role)){
        if(0==section){
            return(tr("测试数据"));
        }else if(1==section){
            return(tr("测试号."));
        }else if(2==section){
            return(tr("测试参考"));
        }else if(3==section){
            return(tr("测试组"));
        }else if(4==section){
            return(tr("主题名称"));
        }else if(5==section){
            return(tr("主题参考"));
        }else if(6==section){
            return(tr("年龄"));
        }else if(7==section){
            return(tr("性别"));
        }else if(8==section){
            return(tr("身高"));
        }else if(9==section){
            return(tr("体重"));
        }else if(10==section){
            return(tr("腰围"));
        }else if(11==section){
            return(tr("臀围"));
        }else{
            return(QVariant());
        }
    }
    //显示其它
    else{
        return(QVariant());
    }
}

int TestDataTableModel::rowCount(
    const QModelIndex & /*parent*/) const{
    /*
    if(!parent.isValid()){
        return(0);
    }
    */
    return(TestDataPool::instance()->count());
}

int TestDataTableModel::columnCount(
    const QModelIndex & /*parent*/) const{
    /*
    if(!parent.isValid()){
        return(0);
    }
    */
    return(COLUMN_COUNT);
}

QVariant TestDataTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
