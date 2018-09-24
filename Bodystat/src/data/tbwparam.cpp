#include"tbwparam.h"
#include"tbwrange.h"
#include<QSqlQuery>

TbwParam::TbwParam()
    :_tbwRangePool(){
}

TbwParam::~TbwParam(){
}

int TbwParam::pull(QSqlQuery &query){
    TbwRangePool pool;
    while(query.next()){
        PtrTbwRange range(new TbwRange);
        if(range.isNull()){
            return(-1);
        }
        if(range->pull(query)<0){
            return(-2);
        }
        pool.push_back(range);
    }
    _tbwRangePool.swap(pool);
    return(0);
}

int TbwParam::getRange(const unsigned int age,
    const unsigned int sex,unsigned int &referLower,
    unsigned int &referUpper) const{
    for(TbwRangePool::const_iterator iter=_tbwRangePool.begin();
        iter!=_tbwRangePool.end();++iter){
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

QString TbwParam::getRangeText(
    const unsigned int age,const unsigned int sex) const{
    unsigned int referLower=0;
    unsigned int referUpper=0;
    if(getRange(age,sex,referLower,referUpper)<0){
        return(QString());
    }else{
        return(QString("%1-%2").arg(referLower).arg(referUpper));
    }
}
