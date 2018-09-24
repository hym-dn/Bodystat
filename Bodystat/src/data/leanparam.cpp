#include"leanparam.h"
#include"leanrange.h"
#include<QSqlQuery>

LeanParam::LeanParam()
    :_leanRangePool(){
}

LeanParam::~LeanParam(){
}

int LeanParam::pull(QSqlQuery &query){
    LeanRangePool pool;
    while(query.next()){
        PtrLeanRange range(new LeanRange);
        if(range.isNull()){
            return(-1);
        }
        if(range->pull(query)<0){
            return(-2);
        }
        pool.push_back(range);
    }
    _leanRangePool.swap(pool);
    return(0);
}

int LeanParam::getRange(const unsigned int age,
    const unsigned int sex,unsigned int &referLower,
    unsigned int &referUpper) const{
    for(LeanRangePool::const_iterator iter=_leanRangePool.begin();
        iter!=_leanRangePool.end();++iter){
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

QString LeanParam::getRangeText(
    const unsigned int age,const unsigned int sex) const{
    unsigned int referLower=0;
    unsigned int referUpper=0;
    if(getRange(age,sex,referLower,referUpper)<0){
        return(QString());
    }else{
        return(QString("%1-%2").arg(referLower).arg(referUpper));
    }
}
