#ifndef SUBJECT_H
#define SUBJECT_H

#include<QString>
#include<QDateTime>
#include<QSqlDatabase>

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
    int push(QSqlDatabase &db,const bool isAdd);
    int isValid(QString *msg=0) const;
    void setId(const QString &id);
    const QString &getId() const;
    void setName(const QString &name);
    const QString &getName() const;
    void setAge(const unsigned int age);
    unsigned int getAge() const;
    QString getAgeText() const;
    void setSex(const Sex sex);
    Sex getSex() const;
    void setHeight(const float height);
    float getHeight() const;
    QString getHeightText() const;
    void setWeight(const float weight);
    float getWeight() const;
    QString getWeightText() const;
    void setEntryDateTime(const QDateTime &time);
    const QDateTime &getEntryDateTime() const;
    QString getEntryDateTimeText() const;
    void setModifyDateTime(const QDateTime &time);
    const QDateTime &getModifyDateTime() const;
    QString getModifyDateTimeText() const;
    void setAccessDateTime(const QDateTime &time);
    const QDateTime &getAccessDateTime() const;
    QString getAccessDateTimeText() const;
public:
    Subject &operator=(const Subject &src);
private:
    QString _id;
    QString _name;
    unsigned int _age;
    Sex _sex;
    float _height;
    float _weight;
    QDateTime _entryDateTime;
    QDateTime _modifyDateTime;
    QDateTime _accessDateTime;
};

#endif // SUBJECT_H
