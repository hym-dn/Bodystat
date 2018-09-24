#ifndef FAT_PARAM_H
#define FAT_PARAM_H

#include<QVector>
#include<QSharedPointer>

class FatRange;
class QSqlQuery;

class FatParam{
public:
    FatParam();
    ~FatParam();
public:
    int pull(QSqlQuery &query);
private:
    typedef QSharedPointer<FatRange> PtrFatRange;
    typedef QVector<PtrFatRange> FatRangePool;
private:
    FatParam(const FatParam &);
    FatParam &operator=(const FatParam &);
private:
    FatRangePool _fatRangePool;
};

#endif // FAT_PARAM_H
