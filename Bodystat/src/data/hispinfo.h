#ifndef HISP_INFO_H
#define HISP_INFO_H

#include<QString>

class QSqlQuery;
class QSqlDatabase;

class HispInfo{
public:
    HispInfo();
    explicit HispInfo(const HispInfo &info);
    ~HispInfo();
public:
    int pull(QSqlQuery &query);
    int push(QSqlDatabase &db);
    int isValid(QString *errMsg=0) const;
    void setHispName(const QString &name);
    const QString &getHispName() const;
    void setSectName(const QString &name);
    const QString &getSectName() const;
    void setCompName(const QString &name);
    const QString &getCompName() const;
public:
    HispInfo &operator=(const HispInfo &info);
private:
    explicit HispInfo(const QString &hispName,
        const QString &sectName,const QString &compName);
private:
    QString _hispName;
    QString _sectName;
    QString _compName;
};

#endif // HISP_INFO_H
