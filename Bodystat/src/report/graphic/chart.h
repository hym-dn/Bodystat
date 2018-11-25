#ifndef CHART_H
#define CHART_H

#include<QPixmap>
#include<QVector>

class Chart{
public:
    typedef QVector<double> Points;
public:
    Chart(Points points,const int width=260,
        const int height=35);
    Chart(const Chart &chart);
    ~Chart();
public:
    inline void setPrec(const unsigned int prec){_prec=prec;}
    int save(const QString &path);
public:
    Chart &operator=(const Chart &chart);
private:
    void drawPoint();
    void drawLine();
    void drawText();
protected:
    QPixmap _pixmap;
    Points _points;
    double _min;
    double _max;
    unsigned int _prec;
};

#endif // CHART_H
