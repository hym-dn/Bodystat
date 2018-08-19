#include"subject.h"
#include"subjinfo.h"
#include"testdata.h"
#include"../data/testdatapool.h"
#include<QObject>
#include<QSqlQuery>
#include<QVariant>
#include<QtAlgorithms>

static bool testDataLessThan(
    const Subject::PtrTestData &l,
    const Subject::PtrTestData &r){
    if(l->getDevModel()<r->getDevModel()){
        return(true);
    }else if(l->getDevModel()==r->getDevModel()){
        if(l->getDevSeriNum()<r->getDevSeriNum()){
            return(true);
        }else if(l->getDevSeriNum()==r->getDevSeriNum()){
            if(l->getTestDateTime()>r->getTestDateTime()){
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
    :_subjInfo(new SubjInfo)
    ,_testDataV(){
    Q_ASSERT(!_subjInfo.isNull());
}

Subject::~Subject(){
}

int Subject::pull(QSqlQuery &query){
    if(_subjInfo->pull(query)<0){
        return(-1);
    }
    bool isEOF=false;
    TestDataV testDataV;
    while(true){
        if(!query.value(11).isNull()){
            PtrTestData testData(new TestData);
            if(testData.isNull()){
                return(-2);
            }
            if(testData->pull(query,11)<0){
                return(-3);
            }
            if(testData->isValid()<0){
                return(-4);
            }
            testDataV.push_back(testData);
        }
        if(!query.next()){
            isEOF=true;
            break;
        }
        if(_subjInfo->getId()!=query.value(0).toString()){
            break;
        }
    }
    _testDataV.swap(testDataV);
    if(isEOF){
        return(0);
    }else{
        return(1);
    }
}

int Subject::push(QSqlQuery &query,
    const SubjInfo &subjInfo,const bool isAdd){
    if(subjInfo.push(query,isAdd)<0){
        return(-1);
    }
    (*_subjInfo)=subjInfo;
    return(0);
}

int Subject::erase(QSqlQuery &query) const{
    return(_subjInfo->erase(query));
}

int Subject::updateAccsDt(QSqlQuery &query,
    const QDateTime &dt){
    return(_subjInfo->updateAccsDt(query,dt));
}

int Subject::assign(QSqlQuery &query,const TestDataV &testDataV){
    if(testDataV.isEmpty()){
        return(-1);
    }
    if(isValid()<0){
        return(-2);
    }
    QString sql(QString("UPDATE TestData SET SubjectID='%1' "
        "WHERE").arg(_subjInfo->getId()));
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

int Subject::unassign(QSqlQuery &query,const int idx){
    if(idx<0||idx>=_testDataV.count()){
        return(-1);
    }
    if(_testDataV[idx]->unassign(query)<0){
        return(-2);
    }
    TestDataPool::instance()->add(_testDataV[idx]);
    _testDataV.removeAt(idx);
    TestDataPool::instance()->sort();
    return(0);
}

int Subject::isValid(QString *msg/*=0*/) const{
    if(_subjInfo->isValid(msg)<0){
        return(-1);
    }
    for(TestDataV::const_iterator itr=_testDataV.begin();
        itr!=_testDataV.end();++itr){
        if((*itr)->isValid()<0){
            if(0!=msg){
                *msg=QObject::tr("测试数据非法！");
            }
            return(-2);
        }
    }
    return(0);
}

void Subject::setSubjInfo(const SubjInfo &subjInfo){
    *_subjInfo=subjInfo;
}

const SubjInfo &Subject::getSubjInfo() const{
    return(*_subjInfo);
}

int Subject::testDataCount() const{
    return(_testDataV.count());
}

Subject::PtrCTestData Subject::getTestData(const int idx) const{
    if(idx<0||idx>=_testDataV.count()){
        return(PtrCTestData());
    }else{
        return(_testDataV.at(idx));
    }
}

bool Subject::containTestData(const unsigned int devModel,
    const unsigned long devSeriNum,const QDateTime &testDateTime) const{
    for(TestDataV::const_iterator itr=_testDataV.begin();itr!=_testDataV.end();++itr){
        if((*itr)->same(devModel,devSeriNum,testDateTime)){
            return(true);
        }
    }
    return(false);
}
