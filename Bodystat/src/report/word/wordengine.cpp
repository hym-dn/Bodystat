#include"wordengine.h"
#include"../../comm/singleton.h"
#include<Ole2.h>
#include<QDebug>

WordEngine::WordEngine()
    :_opened(false)
    ,_word(0)
    ,_docSet(0)
    ,_curDoc(0){
    const HRESULT res=OleInitialize(0);
    if(S_OK!=res&&S_FALSE!=res){
        qDebug()<<QString("Could not initialize "
            "OLE (error %x)").arg((unsigned int)res);
    }
}

WordEngine::~WordEngine(){
    close();
    OleUninitialize();
}

bool WordEngine::getOpened() const{
    return(_opened);
}

int WordEngine::open(const QString &tmplFile,
    const bool isVisible/*=false*/){
    if(_opened){
        return(-1);
    }
    //_word=new QAxWidget("Word.Application",
       // 0,Qt::MSWindowsOwnDC);
    _word=new QAxObject("Word.Application");
    if(0==_word){
        return(-2);
    }
    _word->setProperty("Visible",isVisible);
    _docSet=_word->querySubObject("Documents");
    if(0==_docSet){
        _word->dynamicCall("Quit()");
        delete _word;
        _word=0;
        return(-2);
    }
    _docSet->dynamicCall("Add(QString)",tmplFile);
    _curDoc=_word->querySubObject("ActiveDocument");
    if(0==_curDoc){
        _word->dynamicCall("Quit()");
        delete _word;
        _word=0;
        // delete _docSet;
        _docSet=0;
        return(-3);
    }
    _opened=true;
    return(0);
}

void WordEngine::close(){
    if(_opened){
        _word->setProperty("DisplayAlerts",true);
        _curDoc->dynamicCall("Close(bool)",true);
        _word->dynamicCall("Quit()");
        delete _word;
        _word=0;
        //delete _docSet;
        _docSet=0;
        //delete _curDoc;
        _curDoc=0;
        _opened=false;
    }
}

int WordEngine::bmToTxt(const QString &bm,
    const QString &txt){
    if(bm.isEmpty()){
        return(-1);
    }
    if(txt.isEmpty()){
        return(-2);
    }
    if(!_opened){
        return(-3);
    }
    QAxObject *bookmark=_curDoc->
        querySubObject("Bookmarks(QString)",bm);
    if(bookmark){
        bookmark->dynamicCall("Select(void)");
        bookmark->querySubObject("Range")->
            setProperty("Text",txt);
        delete bookmark;
        return(0);
    }else{
        return(-4);
    }
}

int WordEngine::bmToImg(const QString &bm,
    const QString &img){
    if(bm.isEmpty()){
        return(-1);
    }
    if(img.isEmpty()){
        return(-2);
    }
    if(!_opened){
        return(-3);
    }
    QAxObject *bookmark=_curDoc->
        querySubObject("Bookmarks(QString)",bm);
    if(bookmark){
        bookmark->dynamicCall("Select(void)");
        QList<QVariant> list;
        list<<QVariant(img);
        list<<QVariant(false);
        list<<QVariant(true);
        list<<bookmark->querySubObject("Range")->asVariant();
        _curDoc->querySubObject("InlineShapes")->dynamicCall(
            "AddPicture(const QString&,QVariant,QVariant,QVariant)",
             list);
        delete bookmark;
        return(0);
    }else{
        return(-4);
    }
}

int WordEngine::saveAs(const QString &file){
    if(file.isEmpty()){
        return(-1);
    }
    if(!_opened){
        return(-2);
    }
    _curDoc->dynamicCall(
        "SaveAs (const QString&)",file);
    return(0);
}

int WordEngine::toPDF(const QString &file){
    if(file.isEmpty()){
        return(-1);
    }
    if(!_opened){
        return(-2);
    }
    _curDoc->querySubObject("ExportAsFixedFormat("
        "QString,WdExportFormat)",file,"wdExportFormatPDF");
    return(0);
}
