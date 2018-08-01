#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include"Dev.h"
#include<QMutex>
#include<QThread>

class BodyStat;

class Bluetooth
    :public Dev{
    Q_OBJECT
public:
    enum{
        TASK_ID_SCAN_DEV=1001, // 连接设备
        TASK_ID_RELOAD_DEV=1002, // 重载设备
        TASK_ID_UNAUTH_DEV=1003, // 取消配对设备
    };
    enum{
        TASK_ERR_NONE=2000,// 无错误
        TASK_ERR_DIRV_INVAL=2001, // 驱动无效
        TASK_ERR_DEV_INVAL=2002, // 设备无效
        TASK_ERR_GET_DIRV_INFO_FAILED=2003, // 获取驱动信息失败
        TASK_ERR_UNAU_FALIED=2004, // 取消配对失败
        TASK_ERR_FIND_DEV_FAILED=2005, // 搜索设备失败
        TASK_ERR_NO_DEV=2006, // 无设备
        TASK_ERR_AUTH_FAILED=2007, // 配对失败
        TASK_ERR_GET_DEV_INFO_FAILED=2008, // 获取设备信息失败
        TASK_ERR_OPEN_PORT_FAILED=2009, // 打开端口失败
        TASK_ERR_CONN_DEV_FAILED=2010, // 连接设备失败
        TASK_ERR_GET_MODEL_VERSION_FAILED=2011, // 获取模型版本失败
        TASK_ERR_GET_SERIAL_NUMBER_FAILED=2012, // 获取序列号失败
        TASK_ERR_GET_CALIB_TIME_FAILED=2013, // 获取校准时间失败
    };
public:
    Bluetooth(QObject *parent=0);
    virtual ~Bluetooth();
signals:
    void task(const unsigned int id,BodyStat *bodyStat);
    void taskStart(const unsigned int id);
    void taskDone(const unsigned int id,const unsigned int err);
    void drivInfoChanged();
public:
    static QString getTaskText(const unsigned int id);
public:
    void reset();
    const QString &getDrivInfo() const;
    void scanDev(BodyStat *bodyStat);
    void reloadDev(BodyStat *bodyStat);
    void unauthDev(BodyStat *bodyStat);
private slots:
    void onTask(const unsigned int id,BodyStat *bodyStat);
private:
    void setDrivInfo(const QString &drivInfo);
private:
    QThread _thread;
    mutable QMutex _lock;
    QString _drivInfo;
};

#endif // BLUETOOTH_H
