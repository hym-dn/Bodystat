#ifndef COMMU_POOL_H
#define COMMU_POOL_H

template<typename T>
class Singleton;
class BTCommu;

class CommuPool{
public:
    virtual ~CommuPool();
public:
    static CommuPool *instance();
private:
    friend class Singleton<CommuPool>;
private:
    CommuPool();
};

#endif // COMMU_POOL_H
