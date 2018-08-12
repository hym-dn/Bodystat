#include"subject.h"
#include"subjinfo.h"
#include"testdata.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>
#include<QtAlgorithms>

static bool testDataLessThan(const Subject::PtrTestData &l,
    const Subject::PtrTestData &r){
    if(l->getDevModel()<r->getDevModel()){
        return(true);
    }else if(l->getDevModel()==r->getDevModel()){
        if(l->getDevSeriNum()<r->getDevSeriNum()){
            return(true);
        }else if(l->getDevSeriNum()==r->getDevSeriNum()){
            if(l->getTestDateTime()<r->getTestDateTime()){
                return(true);
            }else{
                return(false);
            }
        }else{
            return(false);
        }
    }else{
        return(false);
    }
}

Subject::Subject()
    :_info(new SubjInfo)
    ,_testDataV(){
    Q_ASSERT(!_info.isNull());
}

Subject::~Subject(){
}

int Subject::pull(QSqlQuery &query){
    // 主题信息
    if(_info->pull(query)<0){
        return(-1);
    }
    // 测试数据
    bool isEnd=false;
    TestDataV dataV;
    while(true){
        if(!query.value(11).isNull()){
            PtrTestData data(new TestData);
            if(data.isNull()){
                return(-2);
            }
            if(data->pull(query,11)<0){
                return(-3);
            }
            if(data->isValid()<0){
                return(-4);
            }
            dataV.push_back(data);
        }
        if(!query.next()){
            isEnd=true;
            break;
        }
        if(_info->getId()!=
            query.value(0).toString()){
            break;
        }
    }
    _testDataV.swap(dataV);
    // 返回
    if(isEnd){ // 记录尾
        return(0);
    }else{ // 非记录尾
        return(1);
    }
}

int Subject::push(QSqlQuery &query,
    const SubjInfo &info,const bool isAdd){
    if(info.push(query,isAdd)<0){
        return(-1);
    }
    (*_info)=info;
    return(0);
}

int Subject::erase(QSqlQuery &query) const{
    return(_info->erase(query));
}

int Subject::assign(QSqlQuery &query,const TestDataV &testDataV){
    if(testDataV.isEmpty()){
        return(-1);
    }
    if(isValid()<0){
        return(-2);
    }
    QString sql(QString("UPDATE TestData SET SubjectID='%1' WHERE")
        .arg(_info->getId()));
    for(TestDataV::const_iterator itr=testDataV.begin();
        itr!=testDataV.end();++itr){
        if((*itr).isNull()){
            return(-3);
        }
        if((*itr)->isValid()<0){
            return(-4);
        }
        if(itr!=testDataV.begin()){
            sql+=" OR";
        }
        sql+=QString(" (DevModel=%1 AND DevSeriNum=%2 "
            "AND TestDateTime=#%3#)").arg((*itr)->getDevModel())
            .arg((*itr)->getDevSeriNum()).arg((*itr)->
            getTestDateTimeText());
    }
    sql+=";";
    if(!query.exec(sql)){
        return(-5);
    }
    _testDataV.append(testDataV);
    qSort(_testDataV.begin(),_testDataV.end(),testDataLessThan);
    return(0);
}

int Subject::isValid(QString *msg/*=0*/) const{
    // 主题信息
    if(_info->isValid(msg)<0){
        return(-1);
    }
    // 测试数据
    for(TestDataV::const_iterator itr=_testDataV.begin();
        itr!=_testDataV.end();++itr){
        if((*itr)->isValid()<0){
            if(0!=msg){
                *msg=QObject::tr("测试数据非法！");
            }
            return(-2);
        }
    }
    // 返回
    return(0);
}

void Subject::setSubjInfo(const SubjInfo &info){
    *_info=info;
}

const SubjInfo &Subject::getSubjInfo() const{
    return(*_info);
}
