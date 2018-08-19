#include"reporttask.h"
#include"../data/subject.h"
#include"../data/subjinfo.h"
#include"../data/subjpool.h"
#include"../data/testdata.h"
#include"../report/word/wordengine.h"
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
    SubjInfo subjInfo;
    if(SubjPool::instance()->getCurSubjInfo(subjInfo)<0){
        return(-4);
    }
    word.bmToTxt("ID",subjInfo.getId());
    word.bmToTxt("Name",subjInfo.getName());
    SubjPool::PtrCTestData testData;
    testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(0));
    if(testData.isNull()){
        return(-5);
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
    word.bmToTxt("WeightRight",testData->getWeightText());
    word.bmToTxt("Height01",testData->getHeightText());
    word.bmToTxt("Weight01",testData->getWeightText());
    word.bmToTxt("FatPerc01",testData->getFatPercText());
    word.bmToTxt("Illness01",testData->getIllnessText());
    word.bmToTxt("Fpa50kHz01",testData->getFpa50kHzText());
    word.bmToTxt("TestDateTime01",testData->getTestDateTimeText());
    if(_tdIdxV.count()>=2){
        testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(1));
        if(testData.isNull()){
            return(-6);
        }
        word.bmToTxt("Height02",testData->getHeightText());
        word.bmToTxt("Weight02",testData->getWeightText());
        word.bmToTxt("FatPerc02",testData->getFatPercText());
        word.bmToTxt("Illness02",testData->getIllnessText());
        word.bmToTxt("Fpa50kHz02",testData->getFpa50kHzText());
        word.bmToTxt("TestDateTime02",testData->getTestDateTimeText());
    }
    if(_tdIdxV.count()>=3){
        testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(2));
        if(testData.isNull()){
            return(-7);
        }
        word.bmToTxt("Height03",testData->getHeightText());
        word.bmToTxt("Weight03",testData->getWeightText());
        word.bmToTxt("FatPerc03",testData->getFatPercText());
        word.bmToTxt("Illness03",testData->getIllnessText());
        word.bmToTxt("Fpa50kHz03",testData->getFpa50kHzText());
        word.bmToTxt("TestDateTime03",testData->getTestDateTimeText());
    }
    if(_tdIdxV.count()>=4){
        testData=SubjPool::instance()->getCurTestData(_tdIdxV.at(3));
        if(testData.isNull()){
            return(-8);
        }
        word.bmToTxt("Height04",testData->getHeightText());
        word.bmToTxt("Weight04",testData->getWeightText());
        word.bmToTxt("FatPerc04",testData->getFatPercText());
        word.bmToTxt("Illness04",testData->getIllnessText());
        word.bmToTxt("Fpa50kHz04",testData->getFpa50kHzText());
        word.bmToTxt("TestDateTime04",testData->getTestDateTimeText());
    }
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
