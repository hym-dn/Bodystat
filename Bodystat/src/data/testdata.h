#ifndef TEST_DATA_H
#define TEST_DATA_H

#include<QDateTime>

namespace Bodystat{
    struct BSMeasurement;
}

class TestData{
public:
    typedef enum{
        SEX_UNKNOWN=0,
        SEX_MALE=1,
        SEX_FEMALE=2,
        SEX_OTHER=3,
    }Sex;
public:
    TestData();
    explicit TestData(const Bodystat::BSMeasurement &meas);
    explicit TestData(const TestData &src);
    ~TestData();
public:
    int isValid() const;
    void setDevModel(const unsigned int model);
    unsigned int getDevModel() const;
    void setDevSeriNum(const unsigned long seriNum);
    unsigned long getDevSeriNum() const;
    QString getDevSeriNumText() const;
    void setTestDateTime(const QDateTime &dateTime);
    const QDateTime &getTestDateTime() const;
    QString getTestDateTimeText() const;
    void setSex(const Sex sex);
    Sex getSex() const;
    QString getSexText() const;
    void setAge(const int age);
    int getAge() const;
    QString getAgeText() const;
    void setHeight(const float height);
    int getHeight() const;
    QString getHeightText() const;
    void setWeight(const float weight);
    float getWeight() const;
    QString getWeightText() const;
    void setActivity(const int activity);
    int getActivity() const;
    void setWaist(const int waist);
    int getWaist() const;
    QString getWaistText() const;
    void setHip(const int hip);
    int getHip() const;
    QString getHipText() const;
    void setIz5kHz(const int iz5kHz);
    int getIz5kHz() const;
    void setIz50kHz(const int iz5kHz);
    int getIz50kHz() const;
    void setIz100kHz(const int iz100kHz);
    int getIz100kHz() const;
    void setIz200kHz(const int iz200kHz);
    int getIz200kHz() const;
    void setIr50kHz(const int ir50kHz);
    int getIr50kHz() const;
    void setFx50kHz(const float fx50kHz);
    float getFx50kHz() const;
    void setFpa50kHz(const float fpa50kHz);
    float getFpa50kHz() const;
public:
    TestData &operator=(const TestData &src);
private:
    unsigned int _devModel;
    unsigned long _devSeriNum;
    QDateTime _testDateTime;
    Sex _sex;
    int _age;
    int _height;
    float _weight;
    int _activity;
    int _waist;
    int _hip;
    int _iz5kHz;
    int _iz50kHz;
    int _iz100kHz;
    int _iz200kHz;
    int _ir50kHz;
    float _fx50kHz;
    float _fpa50kHz;
};

#endif // TEST_DATA_H
