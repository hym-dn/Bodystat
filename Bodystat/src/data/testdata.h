#ifndef TEST_DATA_H
#define TEST_DATA_H

#include<QDateTime>

class QSqlQuery;
namespace Bodystat{
    struct BSMeasurement;
    struct BSResults;
}

class TestData{
public:
    enum{PREC_LIMIT=1,};
    typedef enum{
        SEX_UNKNOWN=0,
        SEX_MALE=1,
        SEX_FEMALE=2,
        SEX_OTHER=3,
    }Sex;
public:
    TestData();
    explicit TestData(
        const int testNo,
        const Bodystat::BSMeasurement &meas,
        const Bodystat::BSResults &ress);
    explicit TestData(const TestData &src);
    ~TestData();
public:
    int pull(QSqlQuery &query,const unsigned long sIdx=0);
    int pull_t(QSqlQuery &query,const unsigned long sIdx=0);
    int push(QSqlQuery &query);
    int unassign(QSqlQuery &query);
    int isValid() const;
    bool same(const unsigned int devModel,
        const unsigned int devSeriNum,
        const QDateTime &testDateTime) const;
    void setDevModel(const unsigned int model);
    unsigned int getDevModel() const;
    QString getDevModelText() const;
    void setDevSeriNum(const unsigned long seriNum);
    unsigned long getDevSeriNum() const;
    QString getDevSeriNumText() const;
    void setTestDateTime(const QDateTime &dateTime);
    const QDateTime &getTestDateTime() const;
    QString getTestDateTimeText() const;
    QString getTestDateText() const;
    void setTestNo(const int testNo);
    int getTestNo() const;
    QString getTestNoText() const;
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
    QString getActivityText() const;
    void setWaist(const int waist);
    int getWaist() const;
    QString getWaistText() const;
    void setHip(const int hip);
    int getHip() const;
    QString getHipText() const;
    void setIz5kHz(const int iz5kHz);
    int getIz5kHz() const;
    QString getIz5kHzText() const;
    void setIz50kHz(const int iz5kHz);
    int getIz50kHz() const;
    QString getIz50kHzText() const;
    void setIz100kHz(const int iz100kHz);
    int getIz100kHz() const;
    QString getIz100kHzText() const;
    void setIz200kHz(const int iz200kHz);
    int getIz200kHz() const;
    QString getIz200kHzText() const;
    void setIr50kHz(const int ir50kHz);
    int getIr50kHz() const;
    QString getIr50kHzText() const;
    void setFx50kHz(const float fx50kHz);
    float getFx50kHz() const;
    QString getFx50kHzText() const;
    void setFpa50kHz(const float fpa50kHz);
    float getFpa50kHz() const;
    QString getFpa50kHzText() const;
    QString getBrief() const;
    void setFatPerc(const float fatPerc);
    float getFatPerc() const;
    QString getFatPercText() const;
    void setFatKg(const float fatKg);
    float getFatKg() const;
    QString getFatKgText() const;
    void setLeanPerc(const float leanPerc);
    float getLeanPerc() const;
    QString getLeanPercText() const;
    void setLeanKg(const float leanKg);
    float getLeanKg() const;
    QString getLeanKgText() const;
    void setTotalWeight(const float totalWeight);
    float getTotalWeight() const;
    QString getTotalWeightText() const;
    void setDryLW(const float dryLW);
    float getDryLW() const;
    QString getDryLWText() const;
    float getDryLWPerc() const;
    QString getDryLWPercText() const;
    void setTbwPerc(const float tbwPerc);
    float getTbwPerc() const;
    QString getTbwPercText() const;
    void setTbw(const float tbw);
    float getTbw() const;
    QString getTbwText() const;
    void setEcwPerc(const float ecwPerc);
    float getEcwPerc() const;
    QString getEcwPercText() const;
    void setEcw(const float ecw);
    float getEcw() const;
    QString getEcwText() const;
    void setIcwPerc(const float icwPerc);
    float getIcwPerc() const;
    QString getIcwPercText() const;
    void setIcw(const float icw);
    float getIcw() const;
    QString getIcwText() const;
    void setBcm(const float bcm);
    float getBcm() const;
    QString getBcmText() const;
    void setThirdSpace(const float thirdSpace);
    float getThirdSpace() const;
    QString getThirdSpaceText() const;
    float getThirdSpacePerc() const;
    QString getThirdSpacePercText() const;
    void setNutrition(const float nutrition);
    float getNutrition() const;
    QString getNutritionText() const;
    void setIllness(const float illness);
    float getIllness() const;
    QString getIllnessText() const;
    void setBmr(const float bmr);
    float getBmr() const;
    QString getBmrText() const;
    void setBmrKg(const float bmrKg);
    float getBmrKg() const;
    QString getBmrKgText() const;
    void setEstAvg(const float estAvg);
    float getEstAvg() const;
    QString getEstAvgText() const;
    void setBmi(const float bmi);
    float getBmi() const;
    QString getBmiText() const;
    void setBfmi(const float bfmi);
    float getBfmi() const;
    QString getBfmiText() const;
    void setFfmi(const float ffmi);
    float getFfmi() const;
    QString getFfmiText() const;
    void setWaistHip(const float waistHip);
    float getWaistHip() const;
    QString getWaistHipText() const;
    void setWellness(const float wellness);
    float getWellness() const;
    QString getWellnessText() const;
    void setEcwLegacy(const float ecwLegacy);
    float getEcwLegacy() const;
    QString getEcwLegacyText() const;
    void setTbwLegacy(const float tbwLegacy);
    float getTbwLegacy() const;
    QString getTbwLegacyText() const;
    void setOhy(const float ohy);
    float getOhy() const;
    QString getOhyText() const;
    void setSkMuscle(const float skMuscle);
    float getSkMuscle() const;
    QString getSkMuscleText() const;
    float calSkMuscle() const;
    QString calSkMuscleText() const;
    void setCm(const float cm);
    float getCm() const;
    QString getCmText() const;
    void setRext(const float rext);
    float getRext() const;
    QString getRextText() const;
    void setRint(const float rint);
    float getRint() const;
    QString getRintText() const;
    void setFc(const float fc);
    float getFc() const;
    QString getFcText() const;
    void setAlpha(const float alpha);
    float getAlpha() const;
    QString getAlphaText() const;
    void setSubjId(const QString &subjId);
    const QString &getSubjId() const;
    void setSubjName(const QString &name);
    const QString &getSubjName() const;
public:
    TestData &operator=(const TestData &src);
private:
    unsigned int _devModel;
    unsigned long _devSeriNum;
    QDateTime _testDateTime;
    int _testNo;
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
    float _fpa50kHz; // 相位角
    float _fatPerc; // 脂肪（%）
    float _fatKg; // 脂肪（kg）
    float _leanPerc; // 瘦肉（%）
    float _leanKg; // 瘦肉（kg）
    float _totalWeight;   // Total Weight (in kg)
    float _dryLW; // 干瘦肉（kg）
    float _tbwPerc; // 总水量（%）
    float _tbw; // 总水量（升）
    float _ecwPerc; // 细胞外液（%）
    float _ecw; // 细胞外液（升）
    float _icwPerc; // 细胞内液（%）
    float _icw; // 细胞内液（升）
    float _bcm; // 人体细胞总量
    float _thirdSpace;	// 第三空间水（升）
    float _nutrition; // 营养指数
    float _illness; // 预测指数
    float _bmr; // 基础代谢率（kcal）
    float _bmrKg; // 体重平均代谢 Basal Metabolic Rate per kilogram in (kcal/kg)
    float _estAvg; // 基础需能量 (kcal)
    float _bmi; // 身体质量指数
    float _bfmi; // 身体脂肪质量指数
    float _ffmi; // 非脂肪质量指数
    float _waistHip; // 腰臀比
    float _wellness; // Wellness Marker (TM)	(MDD only)
    float _ecwLegacy; // Legacy ECW calculation (QuanScan mode)
    float _tbwLegacy;
    float _ohy; // Over hydration
    float _skMuscle; // 骨骼肌
    float _cm; // Cell membrane capacitance
    float _rext; // R extracellular
    float _rint; // R intracellular
    float _fc; // Characteristic frequency
    float _alpha;
    QString _subjId;
    QString _subjName;
};

#endif // TEST_DATA_H
