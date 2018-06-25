#include"ui/maindlg.h"
#include"report/word/wordengine.h"
#include<QApplication>

int main(int argc,char *argv[]){
    QApplication a(argc,argv);

    WordEngine::instance()->open(
        QCoreApplication::applicationDirPath()+
        "\\report\\reptmpl.docx",false);
    WordEngine::instance()->bmToTxt(
        "Name",QApplication::tr("绵阳中心"));
    /*
    WordEngine::instance()->saveAs(
        QCoreApplication::applicationDirPath()+
        "\\report\\121.docx");
        */
    WordEngine::instance()->print();
    WordEngine::instance()->close();

    MainDlg w;
    w.show();
    return(a.exec());
}
