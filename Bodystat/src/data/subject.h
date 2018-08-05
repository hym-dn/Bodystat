#ifndef SUBJECT_H
#define SUBJECT_H

#include<QString>
#include<QDateTime>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDate>

class Subject{
public:
    typedef enum{
        SEX_UNKNOWN=0,
        SEX_MALE=1,
        SEX_FEMALE=2,
        SEX_OTHER=3,
    }Sex;
public:
    Subject();
    Subject(const Subject &src);
    ~Subject();
public:
    int pull(QSqlQuery &query);
    int push(QSqlDatabase &db,const bool isAdd);
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
    void setEntryDateTime(const QDateTime &time);
    const QDateTime &getEntryDateTime() const;
    QString getEntryDateTimeText() const;
    void setModifyDateTime(const QDateTime &time);
    const QDateTime &getModifyDateTime() const;
    QString getModifyDateTimeText() const;
    void setAccessDateTime(const QDateTime &time);
    const QDateTime &getAccessDateTime() const;
    QString getAccessDateTimeText() const;
    QString getBrief() const;
public:
    Subject &operator=(const Subject &src);
private:
    QString _id;
    QString _name;
    QDate _birthday;
    Sex _sex;
    QString _telNo;
    QString _mobNo;
    QString _email;
    QString _addr;
    QDateTime _entryDateTime;
    QDateTime _modifyDateTime;
    QDateTime _accessDateTime;
};

#endif // SUBJECT_H
