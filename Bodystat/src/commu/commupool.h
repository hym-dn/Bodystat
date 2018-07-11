#ifndef COMMU_POOL_H
#define COMMU_POOL_H

template<typename T>
class Singalton;

class CommuPool{
public:
    virtual ~CommuPool();
private:
    CommuPool();
};

#endif // COMMU_POOL_H
