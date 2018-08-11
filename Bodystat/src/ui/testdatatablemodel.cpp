#include"testdatatablemodel.h"
#include"../data/testdata.h"
#include"../data/testdatapool.h"

TestDataTableModel::TestDataTableModel(
    QObject *parent/*=0*/)
    :QAbstractTableModel(parent){
}

TestDataTableModel::~TestDataTableModel(){
}

void TestDataTableModel::update(){
    beginResetModel();
    endResetModel();
}

QVariant TestDataTableModel::headerData(
    int section,Qt::Orientation orientation,
    int role) const{
    //水平表头
    if((Qt::Horizontal==orientation)&&(
        Qt::DisplayRole==role)){
        if(0==section){
            return(tr("设备"));
        }else if(1==section){
            return(tr("测试数据"));
        }else if(2==section){
            return(tr("测试号."));
        }else if(3==section){
            return(tr("测试参考"));
        }else if(4==section){
            return(tr("测试组"));
        }else if(5==section){
            return(tr("主题名称"));
        }else if(6==section){
            return(tr("主题参考"));
        }else if(7==section){
            return(tr("年龄"));
        }else if(8==section){
            return(tr("性别"));
        }else if(9==section){
            return(tr("身高"));
        }else if(10==section){
            return(tr("体重"));
        }else if(11==section){
            return(tr("腰围"));
        }else if(12==section){
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

QVariant TestDataTableModel::data(
    const QModelIndex &index,int role) const{
    // 索引无效
    if(!index.isValid()){
        return(QVariant());
    }
    // 索引有效
    else{
        // 显示角色
        if((Qt::DisplayRole==role)||(
            Qt::UserRole==role)){
            // 获取测试数据
            TestDataPool::PtrToCData testData=
                TestDataPool::instance()->
                getData(index.row());
            // 获取测试数据失败
            if(testData.isNull()){
                return(QVariant());
            }
            // 获取测试数据成功
            else{
                // 设备
                if(0==index.column()){
                    return(testData->getDevModelText());
                }
                // 测试数据
                else if(1==index.column()){
                    return(testData->getTestDateTimeText());
                }
                // 测试号
                else if(2==index.column()){
                    return(testData->getDevSeriNumText());
                }
                // 测试参考
                else if(3==index.column()){
                    return(QVariant());
                }
                // 测试组
                else if(4==index.column()){
                    return(QVariant());
                }
                // 主题名称
                else if(5==index.column()){
                    return(QVariant());
                }
                // 主题参考
                else if(6==index.column()){
                    return(QVariant());
                }
                // 年龄
                else if(7==index.column()){
                    return(testData->getAgeText());
                }
                // 性别
                else if(8==index.column()){
                    return(testData->getSexText());
                }
                // 身高
                else if(9==index.column()){
                    return(testData->getHeightText());
                }
                // 体重
                else if(10==index.column()){
                    return(testData->getWeightText());
                }
                // 腰围
                else if(11==index.column()){
                    return(testData->getWaistText());
                }
                // 臀围
                else if(12==index.column()){
                    return(testData->getHipText());
                }
                // 显示其它
                else{
                    return(QVariant());
                }
            } // 获取测试数据成功
        }
        // 其它角色
        else{
            return(QVariant());
        }
    }
}
