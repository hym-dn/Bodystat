#ifndef SINGLETON_H
#define SINGLETON_H

#include<QSharedPointer>
#include<QMutexLocker>
#include<QMutex>

/**
 * @name Singleton
 * @brief 单件类，负责辅助实现单件设计模式。
 * @author yameng_he
 * @date 2014-05-29
 */
template<typename T>
class Singleton{
//define
public:
    typedef QSharedPointer<T> InstancePointer;
//interface
public:
    static T *instance();
//restriction
private:
    Singleton();
    Singleton(const Singleton &);
    ~Singleton();
    Singleton &operator=(const Singleton &);
//variables
private:
    static QMutex _mutex;
    static InstancePointer _instance;
};

//初始化类中静态变量.
template<typename T>
QMutex Singleton<T>::_mutex;
template<typename T>
typename Singleton<T>::InstancePointer Singleton<T>::_instance;

/**
 * @name instance
 * @brief 获取指向指定类型的全局唯一的实例对象的指针。
 * @param --
 * @return 返回指向指定类型的全局唯一的实例对象的指针。
 * @remark 单例模式采用Double-Check方式实现，使用时请注意
 *         Double-Check方式的缺陷。
 */
template<typename T>
T *Singleton<T>::instance(){
    if(_instance.isNull()){
        QMutexLocker locker(&_mutex);
        if(_instance.isNull()){
            _instance.reset(new T);
        }
    }
    return(_instance.data());
}

#endif //SINGLETON_H
