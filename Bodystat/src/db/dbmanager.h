#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include<QSqlDatabase>
#include<QMutex>

template<typename T>
class Singleton;

class DBManager{
public:
    ~DBManager();
public:
    static DBManager *instance();
    static void close(QSqlDatabase &db);
public:
    int open();
    void close();
    QSqlDatabase getDB();
private:
    friend class Singleton<DBManager>;
private:
    DBManager(const DBManager &);
    DBManager &operator=(const DBManager &);
private:
    DBManager();
private:
    QMutex _lock;
    QSqlDatabase _conn;
};

#endif // DB_MANAGER_H
