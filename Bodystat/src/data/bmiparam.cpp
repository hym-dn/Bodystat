#include"bmiparam.h"
#include"bmirange.h"
#include"testdata.h"
#include<QSqlQuery>

BmiParam::BmiParam()
    :_bmiRangePool(){
}

BmiParam::~BmiParam(){
}

int BmiParam::pull(QSqlQuery &query){
    BmiRangePool pool;
    while(query.next()){
        PtrBmiRange range(new BmiRange);
        if(range.isNull()){
            return(-1);
        }
        if(range->pull(query)<0){
            return(-2);
        }
        pool.push_back(range);
    }
    _bmiRangePool.swap(pool);
    return(0);
}

int BmiParam::getRange(const unsigned int age,
    const unsigned int sex,float &referLower,
    float &referUpper) const{
    for(BmiRangePool::const_iterator iter=_bmiRangePool.begin();
        iter!=_bmiRangePool.end();++iter){
        if((*iter).isNull()){
            continue;
        }
        if((*iter)->isContain(age,sex)>=0){
            referLower=(*iter)->getReferLower();
            referUpper=(*iter)->getReferUpper();
            return(0);
        }
    }
    return(-1);
}

QString BmiParam::getRangeText(
    const unsigned int age,const unsigned int sex) const{
    float referLower=0.0f;
    float referUpper=0.0f;
    if(getRange(age,sex,referLower,referUpper)<0){
        return(QString());
    }else{
        return(QString("%1-%2").arg(referLower,0,'f',1)
            .arg(referUpper,0,'f',1));
    }
}
