#include"reportcreater.h"
#include"../comm/singleton.h"
#include"../data/subjinfo.h"
#include"../data/subject.h"
#include"../data/subjpool.h"
#include"../data/testdata.h"
#include"word/wordengine.h"
#include<QCoreApplication>
#include<QDir>

static void emptyDir(const QString &dirPath){
    if(!dirPath.isEmpty()){
        QDir dir(dirPath);
        dir.setFilter(QDir::Files);
        int fileCount=dir.count();
        for(int i=0;i<fileCount;i++){
            dir.remove(dir[i]);
        }
    }
}

ReportCreater::~ReportCreater(){
    _thread.quit();
    _thread.wait();
}

ReportCreater *ReportCreater::instance(){
    return(Singleton<ReportCreater>::instance());
}

void ReportCreater::creat(const IdxV idxV){
    emit report(REPORT_ID_BODY_COMP,idxV);
}

ReportCreater::ReportCreater(QObject *parent/*=0*/)
    :QObject(parent)
    ,_thread(){
    moveToThread(&_thread);
    connect(this,SIGNAL(report(const unsigned int,IdxV)),
        this,SLOT(onReport(const unsigned int,IdxV idxV)));
    _thread.start();
}

void ReportCreater::onReport(const unsigned int repId,const IdxV idxV){
    emit startReport(repId);
    if(idxV.empty()){
        emit reportDone(repId,REPORT_ERR_NO_TEST_SEL);
        return;
    }
    SubjInfo subjInfo;
    if(SubjPool::instance()->getCurSubjInfo(subjInfo)<0){
        emit reportDone(repId,REPORT_ERR_GET_SUBJ_FAILED);
        return;
    }
    const QString curPath=QCoreApplication::applicationDirPath();
    emptyDir(curPath+"/temp");
    WordEngine word;
    if(word.open(curPath+"/report/repttmpl.docx")<0){
        emit reportDone(repId,REPORT_ERR_OPEN_TEMPL_FAILED);
        return;
    }
    word.bmToTxt("SubjID",subjInfo.getId());
    word.bmToTxt("SubjName",subjInfo.getName());
    SubjPool::PtrCTestData testData=SubjPool::instance()->
        getCurTestData(idxV.at(0));
    if(testData.isNull()){
        emit reportDone(repId,REPORT_ERR_GET_TEST_DATA_FAILED);
        return;
    }
    word.bmToTxt("Age",testData->getAgeText());
    word.bmToTxt("Sex",testData->getSexText());
    word.bmToTxt("Height",testData->getHeightText());
    word.bmToTxt("Weight",testData->getWeightText());

    word.bmToTxt("Ecw",testData->getEcwText());
    word.bmToTxt("Icw",testData->getIcwText());
    word.bmToTxt("ThirdSpace",testData->getThirdSpaceText());
    word.bmToTxt("DryLW",testData->getDryLWText());
    word.bmToTxt("FatKg",testData->getFatKgText());
    word.bmToTxt("Tbw",testData->getTbwText());
    word.bmToTxt("LeanKg",testData->getLeanKgText());
    word.bmToTxt("LeanKg",testData->getLeanKgText());
    word.bmToTxt("WeightKg",testData->getWeightText());
    word.bmToTxt("EcwPerc",testData->getEcwPercText());
    word.bmToTxt("IcwPerc",testData->getIcwPercText());
    word.bmToTxt("FatPerc",testData->getFatPercText());
    word.bmToTxt("TbwPerc",testData->getTbwPercText());
    word.bmToTxt("LeanPerc",testData->getLeanPercText());
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
    word.bmToTxt("Bfmi",testData->getBfmiText());
    word.bmToTxt("Ffmi",testData->getFfmiText());
    word.bmToTxt("Bcm",testData->getBcmText());
    word.bmToTxt("Nutrition",testData->getNutritionText());
    word.bmToTxt("SkMuscle",testData->getSkMuscleText());
    word.bmToTxt("Fpa50kHz",testData->getFpa50kHzText());
    word.bmToTxt("Weightkg",testData->getWeightText());
    word.bmToTxt("Height01",testData->getHeightText());
    word.bmToTxt("Weight01",testData->getWeightText());
    word.bmToTxt("FatPerc01",testData->getFatPercText());
    word.bmToTxt("Illness01",testData->getIllnessText());
    word.bmToTxt("Fpa50kHz01",testData->getFpa50kHzText());
    word.bmToTxt("TestDateTime01",testData->getTestDateTimeText());
    if(idxV.count()>=2){
        testData=SubjPool::instance()->getCurTestData(idxV.at(1));
        if(testData.isNull()){
            emit reportDone(repId,REPORT_ERR_GET_TEST_DATA_FAILED);
            return;
        }
        word.bmToTxt("Height02",testData->getHeightText());
        word.bmToTxt("Weight02",testData->getWeightText());
        word.bmToTxt("FatPerc02",testData->getFatPercText());
        word.bmToTxt("Illness02",testData->getIllnessText());
        word.bmToTxt("Fpa50kHz02",testData->getFpa50kHzText());
        word.bmToTxt("TestDateTime02",testData->getTestDateTimeText());
    }
    if(idxV.count()>=3){
        testData=SubjPool::instance()->getCurTestData(idxV.at(2));
        if(testData.isNull()){
            emit reportDone(repId,REPORT_ERR_GET_TEST_DATA_FAILED);
            return;
        }
        word.bmToTxt("Height03",testData->getHeightText());
        word.bmToTxt("Weight03",testData->getWeightText());
        word.bmToTxt("FatPerc03",testData->getFatPercText());
        word.bmToTxt("Illness03",testData->getIllnessText());
        word.bmToTxt("Fpa50kHz03",testData->getFpa50kHzText());
        word.bmToTxt("TestDateTime03",testData->getTestDateTimeText());
    }
    if(idxV.count()>=4){
        testData=SubjPool::instance()->getCurTestData(idxV.at(3));
        if(testData.isNull()){
            emit reportDone(repId,REPORT_ERR_GET_TEST_DATA_FAILED);
            return;
        }
        word.bmToTxt("Height04",testData->getHeightText());
        word.bmToTxt("Weight04",testData->getWeightText());
        word.bmToTxt("FatPerc04",testData->getFatPercText());
        word.bmToTxt("Illness04",testData->getIllnessText());
        word.bmToTxt("Fpa50kHz04",testData->getFpa50kHzText());
        word.bmToTxt("TestDateTime04",testData->getTestDateTimeText());
    }
    /*
    if(word.toPdf(curPath+"/temp/repttmpl.pdf")){
        emit reportDone(repId,REPORT_ERR_TO_PDF_FAILED);
        return;
    }
    */
    word.saveAs(curPath+"/temp/repttmpl.docx");
    emit reportDone(repId,REPORT_ERR_NONE);
    return;
}
