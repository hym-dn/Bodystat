#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include<QAxObject>
#include<QAxWidget>
#include<QMutex>

template<typename T>
class Singleton;

/**
 * @brief word操作引擎
 */
class WordEngine{
public:
    ~WordEngine();
public:
    static WordEngine *instance();
private:
    friend class Singleton<WordEngine>;
private:
    WordEngine();
private:
    WordEngine(const WordEngine &);
    WordEngine &operator=(const WordEngine &);
private:
    int open(
        const QString &tmplFile,
        const bool isVisible);
private:
    QMutex _lock; // 锁
    bool _isOpen; // 打开标志
    QAxWidget *_word; // word 应用程序
    QAxObject *_docSet; // 文档集
    QAxObject *_curDoc; // 当前操作文档
};

#endif // WORD_ENGINE_H
