#ifndef SYS_INFO_POOL_H
#define SYS_INFO_POOL_H

#include<QObject>
#include<QSharedPointer>
#include<QMutex>

template<typename T>
class Singleton;
class HispInfo;
class FatParam;
class TbwParam;
class LeanParam;
class BmiParam;
class QSqlDatabase;

class SysInfoPool
    :public QObject{
    Q_OBJECT
public:
    typedef QSharedPointer<HispInfo> PtrHispInfo;
    typedef QSharedPointer<const HispInfo> PtrCHispInfo;
public:
    virtual ~SysInfoPool();
public:
    static SysInfoPool *instance();
public:
    int pull(QSqlDatabase &db);
    int push(PtrHispInfo &hispInfo,QSqlDatabase &db);
    PtrCHispInfo getHispInfo() const;
    QString getTbwRangeText(const unsigned int age,
        const unsigned int sex) const;
    QString getLeanRangeText(const unsigned int age,
        const unsigned int sex) const;
    QString getBmiRangeText(const unsigned int age,
        const unsigned int sex) const;
private:
    friend Singleton<SysInfoPool>;
    typedef QSharedPointer<FatParam> PtrFatParam;
    typedef QSharedPointer<TbwParam> PtrTbwParam;
    typedef QSharedPointer<LeanParam> PtrLeanParam;
    typedef QSharedPointer<BmiParam> PtrBmiParam;
private:
    explicit SysInfoPool(QObject *parent=0);
private:
    SysInfoPool(const SysInfoPool &);
    SysInfoPool &operator=(const SysInfoPool &);
private:
    mutable QMutex _lock;
    PtrHispInfo _hispInfo;
    PtrFatParam _fatParam;
    PtrTbwParam _tbwParam;
    PtrLeanParam _leanParam;
    PtrBmiParam _bmiParam;
};

#endif // SYS_INFO_POOL_H
