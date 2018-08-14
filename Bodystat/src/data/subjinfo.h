#ifndef SUBJ_INFO_H
#define SUBJ_INFO_H

#include<QString>
#include<QDate>
#include<QDateTime>

class QSqlQuery;

class SubjInfo{
public:
    typedef enum{
        SEX_UNKNOWN=0,
        SEX_MALE=1,
        SEX_FEMALE=2,
        SEX_OTHER=3,
    }Sex;
public:
    SubjInfo();
    explicit SubjInfo(const SubjInfo &src);
    ~SubjInfo();
public:
    int pull(QSqlQuery &query);
    int push(QSqlQuery &query,
        const bool isAdd) const;
    int erase(QSqlQuery &query) const;
    int isValid(QString *msg=0) const;
    void setId(const QString &id);
    const QString &getId() const;
    void setName(const QString &name);
    const QString &getName() const;
    void setBirthday(const QDate &birthday);
    const QDate &getBirthday() const;
    QString getBirthdayText() const;
    void setSex(const Sex sex);
    Sex getSex() const;
    QString getSexText() const;
    void setTelNo(const QString &telNo);
    const QString &getTelNo() const;
    void setMobNo(const QString &mobNo);
    const QString &getMobNo() const;
    void setEmail(const QString &email);
    const QString &getEmail() const;
    void setAddr(const QString &addr);
    const QString &getAddr() const;
    void setEntrDt(const QDateTime &dt);
    const QDateTime &getEntrDt() const;
    QString getEntrDtText() const;
    void setModiDt(const QDateTime &dt);
    const QDateTime &getModiDt() const;
    QString getModiDtText() const;
    void setAccsDt(const QDateTime &dt);
    const QDateTime &getAccsDt() const;
    QString getAccsDtText() const;
    QString getBrief() const;
public:
    SubjInfo &operator=(const SubjInfo &src);
private:
    QString _id;
    QString _name;
    QDate _birthday;
    Sex _sex;
    QString _telNo;
    QString _mobNo;
    QString _email;
    QString _addr;
    QDateTime _entrDt;
    QDateTime _modiDt;
    QDateTime _accsDt;
};

#endif // SUBJ_INFO_H
