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
        QSqlDatabase::removeDatabase(
            conn.connectionName());
        conn.close();
    }
}

int DBManager::open(){
    const DWORD thrId=GetCurrentThreadId();
    QSqlDatabase conn=QSqlDatabase::addDatabase(
        "QODBC",QString("%1").arg(thrId));
    const QString connText=QString("DRIVER={Microsoft "
        "Access Driver (*.mdb, *.accdb)};FIL={MS Access};"
        "DBQ=%1").arg(QCoreApplication::applicationDirPath()+
        "/Bodystat.accdb");
    conn.setDatabaseName(connText);
    if(!conn.open()){
        qDebug()<<conn.lastError().text();
        return(-1);
    }
    QMutexLocker locker(&_lock);
    close(_conn);
    _conn=conn;
    return(0);
}

void DBManager::close(){
    QMutexLocker locker(&_lock);
    close(_conn);
}

QSqlDatabase DBManager::clone(){
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
