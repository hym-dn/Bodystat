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
