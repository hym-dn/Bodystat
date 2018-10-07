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
    int getRange(const unsigned int age,
        const unsigned int sex,float &referLower,
        float &referUpper) const;
    QString getRangeText(const unsigned int age,
        const unsigned int sex) const;
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
