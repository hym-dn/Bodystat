#include"dbmanager.h"
#include"../comm/singleton.h"
#include<QMutexLocker>
#include<QCoreApplication>
#include<Windows.h>

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
    conn.setDatabaseName(QString("DRIVER={Microsoft "
        "Access Driver (*.mdb)};FIL={MS Access};DBQ=%1")
        .arg(QCoreApplication::applicationDirPath()+
        "Bodystat.accdb"));
    if(!conn.open()){
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
