#ifndef TBW_RANGE_H
#define TBW_RANGE_H

class QString;
class QSqlQuery;

class TbwRange{
public:
    typedef enum{
        SEX_UNKNOWN=0,
        SEX_MALE=1,
        SEX_FEMAL=2,
        SEX_OTHER=3,
    }Sex;
public:
    TbwRange();
    explicit TbwRange(const TbwRange &range);
    ~TbwRange();
public:
    int pull(QSqlQuery &query);
    int isValid(QString *errMsg=0) const;
    int isContain(const unsigned int age,
        const unsigned int sex) const;
    void setAgeLower(const unsigned int lower);
    unsigned int getAgeLower() const;
    QString getAgeLowerText() const;
    void setAgeUpper(const unsigned int upper);
    unsigned int getAgeUpper() const;
    QString getAgeUpperText() const;
    void setSex(const unsigned int sex);
    unsigned int getSex() const;
    QString getSexText() const;
    void setReferLower(const unsigned int lower);
    unsigned int getReferLower() const;
    QString getReferLowerText() const;
    void setReferUpper(const unsigned int upper);
    unsigned int getReferUpper() const;
    QString getReferUpperText() const;
public:
    TbwRange &operator=(const TbwRange &range);
private:
    TbwRange(
        const unsigned int ageLower,
        const unsigned int ageUpper,
        const unsigned int sex,
        const unsigned int referLower,
        const unsigned int referUpper);
private:
    unsigned int _ageLower;
    unsigned int _ageUpper;
    unsigned int _sex;
    unsigned int _referLower;
    unsigned int _referUpper;
};

#endif // TBW_RANGE_H
