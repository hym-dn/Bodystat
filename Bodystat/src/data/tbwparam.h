#ifndef TBW_PARAM_H
#define TBW_PARAM_H

#include<QVector>
#include<QSharedPointer>

class TbwRange;
class QSqlQuery;

class TbwParam{
public:
    TbwParam();
    ~TbwParam();
public:
    int pull(QSqlQuery &query);
    int getRange(const unsigned int age,
        const unsigned int sex,unsigned int &referLower,
        unsigned int &referUpper) const;
    QString getRangeText(const unsigned int age,
        const unsigned int sex) const;
private:
    typedef QSharedPointer<TbwRange> PtrTbwRange;
    typedef QVector<PtrTbwRange> TbwRangePool;
private:
    TbwParam(const TbwParam &);
    TbwParam &operator=(const TbwParam &);
private:
    TbwRangePool _tbwRangePool;
};

#endif // TBW_PARAM_H
