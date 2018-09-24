#ifndef FAT_RANGE_H
#define FAT_RANGE_H

class QString;
class QSqlQuery;

class FatRange{
public:
    typedef enum{
        SEX_UNKNOWN=0,
        SEX_MALE=1,
        SEX_FEMAL=2,
        SEX_OTNER=3,
    }Sex;
public:
    FatRange();
    explicit FatRange(const FatRange &range);
    ~FatRange();
public:
    int pull(QSqlQuery &query);
    int isValid(QString *errMsg=0) const;
    int isContain(const unsigned int age,
        const unsigned int sex) const;
    void setAgeLower(const unsigned int lower);
    unsigned int getAgeLower() const;
    void setAgeUpper(const unsigned int upper);
    unsigned int getAgeUpper() const;
    void setSex(const unsigned int sex);
    unsigned int getSex() const;
    void setReferLower(const unsigned int lower);
    unsigned int getReferLower() const;
    void setReferUpper(const unsigned int upper);
    unsigned int getReferUpper() const;
public:
    FatRange &operator=(const FatRange &range);
private:
    FatRange(
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

#endif // FAT_RANGE_H
