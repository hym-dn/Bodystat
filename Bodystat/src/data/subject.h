#ifndef SUBJECT_H
#define SUBJECT_H

#include<QString>
#include<QDateTime>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDate>
#include<QScopedPointer>
#include<QSharedPointer>
#include<QVector>

class SubjInfo;
class TestData;

class Subject{
public:
    typedef QSharedPointer<TestData> PtrTestData;
    typedef QSharedPointer<const TestData> PtrCTestData;
    typedef QVector<PtrTestData> TestDataV;
public:
    Subject();
    ~Subject();
public:
    int pull(QSqlQuery &query);
    int push(QSqlQuery &query,
        const SubjInfo &subjInfo,const bool isAdd);
    int erase(QSqlQuery &query) const;
    int assign(QSqlQuery &query,const TestDataV &testDataV);
    int unassign(QSqlQuery &query,const int idx);
    int updateAccsDt(QSqlQuery &query,
        const QDateTime &dt);
    int isValid(QString *msg=0) const;
    void setSubjInfo(const SubjInfo &subjInfo);
    const SubjInfo &getSubjInfo() const;
    int testDataCount() const;
    PtrCTestData getTestData(const int idx) const;
    bool containTestData(
        const unsigned int devModel,
        const unsigned long devSeriNum,
        const QDateTime &testDateTime) const;
private:
    typedef QScopedPointer<SubjInfo> PtrSubjInfo;
private:
    Subject(const Subject &);
    Subject &operator=(const Subject &);
private:
    PtrSubjInfo _subjInfo;
    TestDataV _testDataV;
};

#endif // SUBJECT_H
