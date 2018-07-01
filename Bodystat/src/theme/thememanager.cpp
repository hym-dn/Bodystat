#include"thememanager.h"
#include"../comm/singleton.h"
#include<QFile>
#include<QTextStream>

ThemeManager::~ThemeManager(){
}

ThemeManager *ThemeManager::instance(){
    return(Singleton<ThemeManager>::instance());
}

QString ThemeManager::styleSheet(
    const QString &path) const{
    if(path.isEmpty()){
        return("");
    }
    QFile file(path);
    if(!file.open(QFile::ReadOnly)){
        return("");
    }
    QTextStream reader(&file);
    reader.setCodec("UTF-8");
    const QString content(reader.readAll());
    file.close();
    return(content);
}

ThemeManager::ThemeManager(){
}
