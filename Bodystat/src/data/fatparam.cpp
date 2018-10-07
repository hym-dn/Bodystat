#include"fatparam.h"
#include"fatrange.h"
#include<QSqlQuery>

FatParam::FatParam()
    :_fatRangePool(){
}

FatParam::~FatParam(){
}

int FatParam::pull(QSqlQuery &query){
    FatRangePool pool;
    while(query.next()){
        PtrFatRange range(new FatRange);
        if(range.isNull()){
            return(-1);
        }
        if(range->pull(query)<0){
            return(-2);
        }
        pool.push_back(range);
    }
    _fatRangePool.swap(pool);
    return(0);
}

int FatParam::getRange(const unsigned int age,
    const unsigned int sex,float &referLower,
    float &referUpper) const{
    for(FatRangePool::const_iterator iter=_fatRangePool.begin();
        iter!=_fatRangePool.end();++iter){
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

QString FatParam::getRangeText(const unsigned int age,
    const unsigned int sex) const{
    float referLower=0.0f;
    float referUpper=0.0f;
    if(getRange(age,sex,referLower,referUpper)<0){
        return(QString());
    }else{
        return(QString("%1-%2").arg(referLower,0,'f',1)
            .arg(referUpper,0,'f',1));
    }
}
