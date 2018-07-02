#include"dbmanager.h"
#include"../comm/singleton.h"
#include<QMutexLocker>
#include<QCoreApplication>
#include<Windows.h>
#include<QSqlError>
#include<QDebug>

DBManager::~DBManager(){
    close();
}

DBManager *DBManager::instance(){
    return(Singleton<DBManager>::instance());
}

void DBManager::close(QSqlDatabase &conn){
    if(conn.isOpen()){
        conn.close();
        QSqlDatabase::removeDatabase(
            conn.connectionName());
    }
}

int DBManager::open(){
    QMutexLocker locker(&_lock);
    close(_conn);
    const DWORD thrId=GetCurrentThreadId();
    _conn=QSqlDatabase::addDatabase(
        "QODBC",QString("%1").arg(thrId));
    const QString connText=QString("DRIVER={Microsoft "
        "Access Driver (*.mdb, *.accdb)};FIL={MS Access};"
        "DBQ=%1").arg(QCoreApplication::applicationDirPath()+
        "/Bodystat.accdb");
    _conn.setDatabaseName(connText);
    if(!_conn.open()){
        qDebug()<<_conn.lastError().text();
        return(-1);
    }else{
        return(0);
    }
}

void DBManager::close(){
    QMutexLocker locker(&_lock);
    close(_conn);
}

QSqlDatabase DBManager::getDB(){
    QMutexLocker locker(&_lock);
    if(!_conn.isOpen()){
        return(QSqlDatabase());
    }
    const QString connNam=QString("%1").
        arg(GetCurrentThreadId());
    if(QSqlDatabase::contains(connNam)){
       return(QSqlDatabase::database(connNam));
    }else{
       QSqlDatabase conn=QSqlDatabase::
        cloneDatabase(_conn,connNam);
       if(!conn.open()){
           return(QSqlDatabase());
       }
       return(conn);
    }
}

DBManager::DBManager()
    :_lock()
    ,_conn(){
}
