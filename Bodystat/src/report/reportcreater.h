#ifndef REPORT_CREATER_H
#define REPORT_CREATER_H

#include<QObject>
#include<QThread>
#include<QVector>

template<typename T>
class Singleton;


class ReportCreater
    :public QObject{
    Q_OBJECT
public:
    typedef enum{
        REPORT_ID_BODY_COMP=3001,
    }ReportID;
    typedef enum{
        REPORT_ERR_NONE=4000,
        REPORT_ERR_NO_TEST_SEL=4001,
        REPORT_ERR_GET_SUBJ_FAILED=4002,
        REPORT_ERR_OPEN_TEMPL_FAILED=4003,
        REPORT_ERR_GET_TEST_DATA_FAILED=4004,
        REPORT_ERR_TO_PDF_FAILED=4005,
    }ReportErr;
    typedef QVector<int> IdxV;
public:
    virtual ~ReportCreater();
public:
    static ReportCreater *instance();
public:
    void creat(const IdxV idxV);
signals:
    void startReport(const unsigned int repId);
    void report(const unsigned int repId,const IdxV idxV);
    void reportDone(const unsigned int repId,const unsigned int err);
private:
    friend class Singleton<ReportCreater>;
private:
    explicit ReportCreater(QObject *parent=0);
public slots:
    void onReport(const unsigned int repId,const IdxV idxV);
private:
    ReportCreater(const ReportCreater&);
    ReportCreater &operator=(const ReportCreater&);
private:
    QThread _thread;
};

#endif // REPORT_CREATER_H
