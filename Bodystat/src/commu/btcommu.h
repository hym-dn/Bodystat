#ifndef BT_COMMU_H
#define BT_COMMU_H

#include"commu.h"
#include<QMutex>

class BTCommu
    :public Commu{
    Q_OBJECT
public:
    BTCommu(QObject *parent=0);
    virtual ~BTCommu();
signals:
    void stackInfoChanged();
public:
    int isValid() const;
    int readStackInfo();
    const QString &getStackInfo() const;
private:
    mutable QMutex _lock;
    QString _stackInfo;
};

#endif // BT_COMMU_H
