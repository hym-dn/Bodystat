#ifndef BODY_STAT_H
#define BODY_STAT_H

#include"dev.h"
#include<QMutex>
#include<QDate>

class BodyStat
    :public Dev{
    Q_OBJECT
public:
    BodyStat(QObject *parent=0);
    virtual ~BodyStat();
public:
    void reset();
    void setName(const QString &name);
    const QString &getName() const;
    void setBda(const QString &bda);
    const QString &getBda() const;
    void setPort(const QString &port);
    const QString &getPort() const;
    void setModel(const unsigned int model);
    unsigned int getModel() const;
    QString getModelText() const;
    void setIsOpen(const bool isOpen);
    bool getIsOpen() const;
    void setIsConnect(const bool isConnect);
    bool getIsConnect() const;
    void setFirmwareV(
        const unsigned char majorV,
        const unsigned char minorV,
        const unsigned char psoc2V,
        const unsigned char eepromV);
    QString getFirmwareVText() const;
    void setSeriNum(const unsigned long seriNum);
    unsigned long getSeriNum() const;
    void setCalibDate(const QDate &calibDate);
    const QDate &getCalibDate() const;
private:
    mutable QMutex _lock;
    QString _name;
    QString _bda;
    QString _port;
    bool _isOpen;
    bool _isConnect;
    unsigned int _model;
    unsigned char _majorV;
    unsigned char _minorV;
    unsigned char _psoc2V;
    unsigned char _eepromV;
    unsigned long _seriNum;
    QDate _calibDate;
};

#endif // BODY_STAT_H
