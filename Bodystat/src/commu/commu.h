#ifndef COMMU_H
#define COMMU_H

#include<QObject>

class Commu
    :public QObject{
    Q_OBJECT
public:
    explicit Commu(QObject *parent=0);
    virtual ~Commu()=0;
private:
    Commu(const Commu&);
    Commu &operator=(const Commu&);
};

#endif // COMMU_H
