#ifndef BMI_PARAM_H
#define BMI_PARAM_H

#include<QVector>
#include<QSharedPointer>

class BmiRange;
class QSqlQuery;

class BmiParam{
public:
    BmiParam();
    ~BmiParam();
public:
    int pull(QSqlQuery &query);
    int getRange(const unsigned int age,
        const unsigned int sex,float &referLower,
        float &referUpper) const;
    QString getRangeText(const unsigned int age,
        const unsigned int sex) const;
private:
    typedef QSharedPointer<BmiRange> PtrBmiRange;
    typedef QVector<PtrBmiRange> BmiRangePool;
private:
    BmiParam(const BmiParam &);
    BmiParam &operator=(const BmiParam &);
private:
    BmiRangePool _bmiRangePool;
};

#endif // BMI_PARAM_H
