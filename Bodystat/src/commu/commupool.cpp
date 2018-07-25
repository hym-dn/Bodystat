#include"commupool.h"
#include"../comm/singleton.h"
#include"../commu/btcommu.h"

CommuPool::~CommuPool(){
}

CommuPool *CommuPool::instance(){
    return(Singleton<CommuPool>::instance());
}

BTCommu *CommuPool::getBtCom(){
    return(_btCom.data());
}

CommuPool::CommuPool()
    :_btCom(new BTCommu){
}
