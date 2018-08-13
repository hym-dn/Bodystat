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
        const SubjInfo &subjInfo,
        const bool isAdd);
    int erase(QSqlQuery &query) const;
    int assign(QSqlQuery &query,const TestDataV &testDataV);
    int isValid(QString *msg=0) const;
    void setSubjInfo(const SubjInfo &info);
    const SubjInfo &getSubjInfo() const;
    int getTestDataCount() const;
    PtrCTestData getTestData(const int idx) const;
private:
    typedef QScopedPointer<SubjInfo> PtrInfo;
private:
    Subject(const Subject &);
    Subject &operator=(const Subject &);
private:
    PtrInfo _info;
    TestDataV _testDataV;
};

#endif // SUBJECT_H
