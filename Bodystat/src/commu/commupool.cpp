#include"commupool.h"
#include"../comm/singleton.h"

CommuPool::~CommuPool(){
}

CommuPool *CommuPool::instance(){
    return(Singleton<CommuPool>::instance());
}

CommuPool::CommuPool(){
}
