#ifndef WORD_ENGINE_H
#define WORD_ENGINE_H

#include<QAxObject>
//#include<QAxWidget>

class WordEngine{
public:
    WordEngine();
    ~WordEngine();
public:
    bool getOpened() const;
    int open(const QString &tmplFile,
        const bool isVisible=false);
    void close();
    int bmToTxt(const QString &bm,
        const QString &txt);
    int saveAs(const QString &file);
    int toPDF(const QString &file);
private:
    WordEngine(const WordEngine &);
    WordEngine &operator=(const WordEngine &);
private:
    bool _opened;
    QAxObject *_word;
    QAxObject *_docSet;
    QAxObject *_curDoc;
};

#endif // WORD_ENGINE_H
