#include"wordengine.h"
#include"../../comm/singleton.h"
#include<Ole2.h>
#include<QDebug>
#include<QMutexLocker>

// 析构
WordEngine::~WordEngine(){
    // 关闭word
    close();
    // 卸载COM库
    OleUninitialize();
}

WordEngine *WordEngine::instance(){
    return(Singleton<WordEngine>::instance());
}

bool WordEngine::isOpen() const{
    QMutexLocker locker(&_lock);
    return(_isOpen);
}

// 打开word
// tmplFile - word模板文件
// isVisible - word是否可见
// 如果函数执行成功返回0，否则返回非0
int WordEngine::open(
    const QString &tmplFile,const bool isVisible){
    // 上锁
    QMutexLocker locker(&_lock);
    // 已经打开
    if(_isOpen){
        return(1); // 返回错误
    }
    // 尚未打开
    else{
        // 创建word应用程序
        _word=new QAxWidget("Word.Application",0,
            Qt::MSWindowsOwnDC);
        if(0==_word){
            return(-1);
        }
        // 设置word是否可见
        _word->setProperty("Visible",isVisible);
        // 获取文档集
        _docSet=_word->querySubObject("Documents");
        if(0==_docSet){
            // 关闭word
            _word->dynamicCall("Quit()");
            // 删除word
            delete _word;
            _word=0;
            // 返回错误
            return(-2);
        }
        // 以模板文件创建文档
        _docSet->dynamicCall("Add(QString)",tmplFile);
        // 获取当前激活文档
        _curDoc=_word->querySubObject("ActiveDocument");
        if(0==_curDoc){
            // 关闭word
            _word->dynamicCall("Quit()");
            // 删除word
            delete _word;
            _word=0;
            // 删除文件集
            // delete _docSet;
            _docSet=0;
            // 返回错误
            return(-3);
        }
        // 设置打开标志
        _isOpen=true;
        // 成功返回
        return(0);
    }
}

// 关闭word
void WordEngine::close(){
    // 上锁
    QMutexLocker locker(&_lock);
    // 已经打开
    if(_isOpen){
        // 设置word属性
        _word->setProperty("DisplayAlerts",true);
        // 关闭当前文档
        _curDoc->dynamicCall("Close(bool)",true);
        // 退出word
        _word->dynamicCall("Quit()");
        // 删除word
        delete _word;
        _word=0;
        // 删除文档集
        //delete _docSet;
        _docSet=0;
        // 删除当前文档
        //delete _curDoc;
        _curDoc=0;
        // 重置标记变量
        _isOpen=false;
    }
}

// 将书签转换为文本
// bm - 输入的书签
// txt - 输入的文本
// 如果函数执行成功返回值大于等于0，否则返回值不等于0
int WordEngine::bmToTxt(
    const QString &bm,const QString &txt){
    // 输入参数非法
    if(bm.isEmpty()){
        return(-1);
    }
    if(txt.isEmpty()){
        return(-2);
    }
    // 上锁
    QMutexLocker locker(&_lock);
    // word尚未打开
    if(!_isOpen){
        return(-3);
    }
    // 获取书签
    QAxObject *bookmark=_curDoc->
        querySubObject("Bookmarks(QString)",bm);
    // 获取成功
    if(bookmark){
        // 书写文本
        bookmark->dynamicCall("Select(void)");
        bookmark->querySubObject("Range")->
            setProperty("Text",txt);
        // 删除标签
        delete bookmark;
        // 成功返回
        return(0);
    }
    // 获取失败
    else{
        return(-4);
    }
}

int WordEngine::saveAs(const QString &file){
    if(file.isEmpty()){
        return(-1);
    }
    QMutexLocker locker(&_lock);
    if(!_isOpen){
        return(-2);
    }
    _curDoc->dynamicCall(
        "SaveAs (const QString&)",file);
    return(0);
}

int WordEngine::print(){
    QMutexLocker locker(&_lock);
    if(!_isOpen){
        return(-1);
    }
    _curDoc->dynamicCall("PrintOut()");
    return(0);
}

// 构造
WordEngine::WordEngine()
    :_lock()
    ,_isOpen(false)
    ,_word(0)
    ,_docSet(0)
    ,_curDoc(0){
    // 初始化COM库
    const HRESULT res=OleInitialize(0);
    // 初始化失败或者已经初始化
    // S_OK 初始化成功
    // S_FALSE 已经初始化
    if(S_OK!=res&&S_FALSE!=res){
        // 输出提示信息
        qDebug()<<QString("Could not initialize "
            "OLE (error %x)").arg((unsigned int)res);
    }
}
