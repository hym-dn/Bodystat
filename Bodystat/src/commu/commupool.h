#ifndef COMMU_POOL_H
#define COMMU_POOL_H

#include<QScopedPointer>

template<typename T>
class Singleton;
class BTCommu;

class CommuPool{
public:
    ~CommuPool();
public:
    static CommuPool *instance();
public:
    BTCommu *getBtCom();
private:
    typedef QScopedPointer<BTCommu> BtComPtr;
    friend class Singleton<CommuPool>;
private:
    CommuPool();
private:
    CommuPool(const CommuPool &);
    CommuPool &operator=(const CommuPool &);
private:
    BtComPtr _btCom;
};

#endif // COMMU_POOL_H
