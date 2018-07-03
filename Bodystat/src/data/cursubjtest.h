#ifndef CUR_SUBJ_TEST_H
#define CUR_SUBJ_TEST_H

#include<QObject>
#include<QMutex>

template<typename T>
class Singleton;
class Subject;

class CurSubjTest
    :public QObject{
    Q_OBJECT
public:
    ~CurSubjTest();
public:
    static CurSubjTest *instance();
signals:
    void subjChanged();
public:
    void setSubj(const Subject &subj);
    const Subject &getSubj() const;
private:
    friend class Singleton<CurSubjTest>;
private:
    explicit CurSubjTest(QObject *parent=0);
private:
    CurSubjTest(const CurSubjTest &);
    CurSubjTest &operator=(const CurSubjTest &);
private:
    mutable QMutex _lock;
    Subject *_subj;
};

#endif // CUR_SUBJ_TEST_H
