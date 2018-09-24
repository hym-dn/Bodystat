#ifndef LEAN_PARAM_H
#define LEAN_PARAM_H

#include<QVector>
#include<QSharedPointer>

class LeanRange;
class QSqlQuery;

class LeanParam{
public:
    LeanParam();
    ~LeanParam();
public:
    int pull(QSqlQuery &query);
    int getRange(const unsigned int age,
        const unsigned int sex,unsigned int &referLower,
        unsigned int &referUpper) const;
    QString getRangeText(const unsigned int age,
        const unsigned int sex) const;
private:
    typedef QSharedPointer<LeanRange> PtrLeanRange;
    typedef QVector<PtrLeanRange> LeanRangePool;
private:
    LeanParam(const LeanParam &);
    LeanParam &operator=(const LeanParam &);
private:
    LeanRangePool _leanRangePool;
};

#endif // LEAN_PARAM_H
