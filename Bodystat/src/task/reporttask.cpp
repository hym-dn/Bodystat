#include"reporttask.h"
#include"../data/subject.h"
#include"../data/subjinfo.h"
#include"../data/subjpool.h"
#include"../data/testdata.h"
#include"../report/word/wordengine.h"
#include"../report/graphic/chart.h"
#include"../data/hispinfo.h"
#include"../data/sysinfopool.h"
#include<QTime>
#include<QThread>
#include<QDir>
#include<QCoreApplication>

static void clearDir(const QString &path){
    if(!path.isEmpty()){
        QDir dir(path);
        dir.setFilter(QDir::Files);
        const int fileCount=dir.count();
        for(int i=0;i<fileCount;i++){
            dir.remove(dir[i]);
        }
    }
}

ReportTask::ReportTask(const TdIdxV &tdIdxV,
    const unsigned int proc/*=0*/)
    :Task(proc)
    ,_tdIdxV(tdIdxV){
}

ReportTask::~ReportTask(){
}

unsigned int ReportTask::getId() const{
    return(ID);
}

int ReportTask::exec(QSqlDatabase & /*db*/){
    if(isValid()<0){
        return(-1);
    }
    QTime tm;
    tm.start();
    const QString curPath=QCoreApplication::applicationDirPath();
    const QString tempPath=curPath+"/temp";
    const QString templPath=curPath+"/report/templ";
    const QString templName="/reptmpl.docx";
    const QString pdfName="/report.pdf";
    const QString docName="/report.docx";
    clearDir(tempPath);
    if(_tdIdxV.empty()){
        return(-2);
    }
    WordEngine word;
    if(word.open(templPath+templName)<0){
        return(-3);
    }
    word.bmToTxt("HispInfo",SysInfoPool::
        instance()->getHispInfo()->getHispName()+
        SysInfoPool::instance()->getHispInfo()->
        getSectName());
    SubjInfo subjInfo;
    if(SubjPool::instance()->getCurSubjInfo(subjInfo)<0){
        return(-4);
    }
    // word.bmToTxt("ID",subjInfo.getId());
    word.bmToTxt("Name",subjInfo.getName());
    SubjPool::PtrCTestData testData;
    testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(0));
    if(testData.isNull()){
        return(-5);
    }
    word.bmToTxt("ID",testData->getTestNoText());
    word.bmToTxt("Age",testData->getAgeText());
    word.bmToTxt("Sex",testData->getSexText());
    word.bmToTxt("Height",testData->getHeightText());
    word.bmToTxt("Weight",testData->getWeightText());
    word.bmToTxt("Ecw",testData->getEcwText());
    word.bmToTxt("Icw",testData->getIcwText());
    word.bmToTxt("ThirdSpace",testData->getThirdSpaceText());
    word.bmToTxt("Tbw",testData->getTbwText());
    unsigned int tbwLower=0;
    unsigned int tbwUpper=0;
    SysInfoPool::instance()->getTbwRange(
        testData->getAge(),testData->getSex(),
        tbwLower,tbwUpper);
    double dTbwLower=static_cast<double>(tbwLower)/100.0;
    double dTbwUpper=static_cast<double>(tbwUpper)/100.0;
    QString strTbwRange=QString("%1-%2").arg(
        testData->getTbw()*dTbwLower,0,'f',1).arg(
        testData->getTbw()*dTbwUpper,0,'f',1);
    word.bmToTxt("TbwRange",strTbwRange);
    word.bmToTxt("DryLW",testData->getDryLWText());
    word.bmToTxt("LeanKg",testData->getLeanKgText());
    unsigned int leanLower=0;
    unsigned int leanUpper=0;
    SysInfoPool::instance()->getLeanRange(
        testData->getAge(),testData->getSex(),
        leanLower,leanUpper);
    double dLeanLower=static_cast<double>(leanLower)/100.0;
    double dLeanUpper=static_cast<double>(leanUpper)/100.0;
    QString strLeanRange=QString("%1-%2").arg(
        testData->getLeanKg()*dLeanLower,0,'f',1).arg(
        testData->getLeanKg()*dLeanUpper,0,'f',1);
    word.bmToTxt("LeanKgRange",strLeanRange);
    word.bmToTxt("FatKg",testData->getFatKgText());
    float lw=0.0,up=0.0;
    SysInfoPool::instance()->getFatRange(
        testData->getAge(),testData->getSex(),lw,up);
    double dLw=lw/100.0;
    double dUp=up/100.0;
    QString strFatKgRange=QString("%1-%2").arg(
        testData->getFatKg()*dLw,0,'f',1).arg(
        testData->getFatKg()*dUp,0,'f',1);
    word.bmToTxt("FatKgRange",strFatKgRange);
    word.bmToTxt("WeightKg",testData->getWeightText());    
    //float stLw=testData->getLeanKg()/(1-lw/100.0f);
    float ndLw=20.0f*(testData->getHeight()/100.0f)*(testData->getHeight()/100.0f);
    //float stUp=testData->getLeanKg()/(1-up/100.0f);
    float ndUp=22.0f*(testData->getHeight()/100.0f)*(testData->getHeight()/100.0f);
    word.bmToTxt("WeightRange",QString("%1-%2").arg(static_cast<int>(ndLw))
        .arg(static_cast<int>(ndUp)));
    word.bmToTxt("EcwPerc",testData->getEcwPercText());
    if(TestData::SEX_MALE==testData->getSex()){
        word.bmToTxt("EcwPercRange","26");
    }else{
        word.bmToTxt("EcwPercRange","20");
    }
    word.bmToTxt("IcwPerc",testData->getIcwPercText());
    if(TestData::SEX_MALE==testData->getSex()){
        word.bmToTxt("IcwPercRange","34");
    }else{
        word.bmToTxt("IcwPercRange","30");
    }
    word.bmToTxt("ThirdSpacePerc",testData->getThirdSpacePercText());
    word.bmToTxt("TbwPerc",testData->getTbwPercText());
    word.bmToTxt("TbwPercRange",SysInfoPool::instance()->
        getTbwRangeText(testData->getAge(),testData->getSex()));
    word.bmToTxt("DryLWPerc",testData->getDryLWPercText());
    word.bmToTxt("FatPerc",testData->getFatPercText());
    word.bmToTxt("FatPercRange",SysInfoPool::instance()->
        getFatRangeText(testData->getAge(),testData->getSex()));
    word.bmToTxt("LeanPerc",testData->getLeanPercText());
    word.bmToTxt("LeanPercRange",SysInfoPool::instance()->
        getLeanRangeText(testData->getAge(),testData->getSex()));
    word.bmToTxt("Iz5kHz",testData->getIz5kHzText());
    word.bmToTxt("Iz50kHz",testData->getIz50kHzText());
    word.bmToTxt("Iz100kHz",testData->getIz100kHzText());
    word.bmToTxt("Iz200kHz",testData->getIz200kHzText());
    word.bmToTxt("Illness",testData->getIllnessText());
    word.bmToTxt("Bmr",testData->getBmrText());
    word.bmToTxt("BmrKg",testData->getBmrKgText());
    word.bmToTxt("EstAvg",testData->getEstAvgText());
    word.bmToTxt("WaistHip",testData->getWaistHipText());
    word.bmToTxt("Bmi",testData->getBmiText());
    //word.bmToTxt("BmiRange",SysInfoPool::instance()->
        //getBmiRangeText(testData->getAge(),testData->getSex()));
    word.bmToTxt("Bfmi",testData->getBfmiText());
    word.bmToTxt("Ffmi",testData->getFfmiText());
    word.bmToTxt("Bcm",testData->getBcmText());
    word.bmToTxt("Nutrition",testData->getNutritionText());
    word.bmToTxt("SkMuscle",testData->calSkMuscleText());
    word.bmToTxt("Fpa50kHz",testData->getFpa50kHzText());
    word.bmToTxt("WeightRight",testData->getWeightText());
    word.bmToTxt("TargetWeight",QString("%1~%2").arg(
        static_cast<int>(ndLw)).arg(static_cast<int>(ndUp)));
    word.bmToTxt("CompanyName",SysInfoPool::instance()->getCompName());
    Chart::Points heightPoints;
    Chart::Points weightPoints;
    Chart::Points fatPercPoints;
    Chart::Points tclPoints;
    Chart::Points illnessPoints;
    Chart::Points fpa50kHzPoints;
    heightPoints.push_back(testData->getHeight());
    weightPoints.push_back(testData->getWeight());
    fatPercPoints.push_back(testData->getFatPerc());
    tclPoints.push_back((testData->getEcw()+
        testData->getIcw()+testData->getThirdSpace())/
        testData->getWeight()*100.0);
    illnessPoints.push_back(testData->getIllness());
    fpa50kHzPoints.push_back(testData->getFpa50kHz());
    word.bmToTxt("TestDateTime01",testData->getTestDateText());
    if(_tdIdxV.count()>=2){
        testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(1));
        if(testData.isNull()){
            return(-6);
        }
        heightPoints.push_back(testData->getHeight());
        weightPoints.push_back(testData->getWeight());
        fatPercPoints.push_back(testData->getFatPerc());
        illnessPoints.push_back(testData->getIllness());
        tclPoints.push_back((testData->getEcw()+
            testData->getIcw()+testData->getThirdSpace())/
            testData->getWeight()*100.0);
        fpa50kHzPoints.push_back(testData->getFpa50kHz());
        word.bmToTxt("TestDateTime02",testData->getTestDateText());
    }
    if(_tdIdxV.count()>=3){
        testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(2));
        if(testData.isNull()){
            return(-7);
        }
        heightPoints.push_back(testData->getHeight());
        weightPoints.push_back(testData->getWeight());
        fatPercPoints.push_back(testData->getFatPerc());
        illnessPoints.push_back(testData->getIllness());
        tclPoints.push_back((testData->getEcw()+
            testData->getIcw()+testData->getThirdSpace())/
            testData->getWeight()*100.0);
        fpa50kHzPoints.push_back(testData->getFpa50kHz());
        word.bmToTxt("TestDateTime03",testData->getTestDateText());
    }
    if(_tdIdxV.count()>=4){
        testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(3));
        if(testData.isNull()){
            return(-8);
        }
        heightPoints.push_back(testData->getHeight());
        weightPoints.push_back(testData->getWeight());
        fatPercPoints.push_back(testData->getFatPerc());
        illnessPoints.push_back(testData->getIllness());
        tclPoints.push_back((testData->getEcw()+
            testData->getIcw()+testData->getThirdSpace())/
            testData->getWeight()*100.0);
        fpa50kHzPoints.push_back(testData->getFpa50kHz());
        word.bmToTxt("TestDateTime04",testData->getTestDateText());
    }
    Chart heightChart(heightPoints);
    heightChart.save(QCoreApplication::applicationDirPath()+"/temp/height.png");
    word.bmToImg("HeightCurve",QCoreApplication::applicationDirPath()+"/temp/height.png");
    Chart weightChart(weightPoints);
    weightChart.save(QCoreApplication::applicationDirPath()+"/temp/weight.png");
    word.bmToImg("WeightCurve",QCoreApplication::applicationDirPath()+"/temp/weight.png");
    Chart fatPercChart(fatPercPoints);
    fatPercChart.save(QCoreApplication::applicationDirPath()+"/temp/fatperc.png");
    word.bmToImg("FatPercCurve",QCoreApplication::applicationDirPath()+"/temp/fatperc.png");
    Chart illnessChart(illnessPoints);
    illnessChart.save(QCoreApplication::applicationDirPath()+"/temp/illness.png");
    word.bmToImg("IllnessCurve",QCoreApplication::applicationDirPath()+"/temp/illness.png");
    Chart tclChart(tclPoints);
    tclChart.save(QCoreApplication::applicationDirPath()+"/temp/tcl.png");
    word.bmToImg("TclCurve",QCoreApplication::applicationDirPath()+"/temp/tcl.png");
    Chart fpa50kHzChart(fpa50kHzPoints);
    fpa50kHzChart.save(QCoreApplication::applicationDirPath()+"/temp/fpa50kHz.png");
    word.bmToImg("fpa50kHzCurve",QCoreApplication::applicationDirPath()+"/temp/fpa50kHz.png");
    if(word.toPDF(tempPath+pdfName)<0){
        return(-9);
    }
    if(word.saveAs(tempPath+docName)<0){
        return(-10);
    }
    word.close();
    const int ms=tm.elapsed();
    if(ms<2000){
        QThread::msleep(2000-ms);
    }
    return(0);
}
