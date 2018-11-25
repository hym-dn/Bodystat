#include"chart.h"
#include<QPainter>
#include<qalgorithms.h>
#include<QApplication>

Chart::Chart(Points points,const int width/*=260*/,
    const int height/*=35*/)
    :_pixmap(width,height)
    ,_points(points)
    ,_min(0.0)
    ,_max(0.0)
    ,_prec(1){
    if(!points.isEmpty()){
        qSort(points);
        _min=points[0];
        _max=points[points.size()-1];
    }
}

Chart::Chart(const Chart &chart)
    :_pixmap(chart._pixmap)
    ,_points(chart._points)
    ,_min(chart._min)
    ,_max(chart._max)
    ,_prec(chart._prec){
}

Chart::~Chart(){
}

int Chart::save(const QString &path){
    if(path.isEmpty()){
        return(-1);
    }
    _pixmap.fill(/*QColor(200,191,231)*/);
    drawPoint();
    drawLine();
    drawText();
    if(!_pixmap.save(path)){
        return(-2);
    }
    return(0);
}

Chart &Chart::operator=(const Chart &chart){
    if(this==&chart){
        return(*this);
    }
    _pixmap=chart._pixmap;
    _points=chart._points;
    _min=chart._min;
    _max=chart._max;
    _prec=chart._prec;
    return(*this);
}

void Chart::drawPoint(){
    if(_points.size()<=1){
        return;
    }
    const double width=static_cast<
        double>(_pixmap.width())/4.0;
    const double x=width/2.0;
    const double vstep=static_cast<double>(
        _pixmap.height()-6)/(_max-_min);
    QPainter painter(&_pixmap);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QColor(83,157,215));
    painter.setBrush(QBrush(QColor(83,157,215)));
    for(int i=0;i<_points.size();++i){
        painter.drawEllipse(x+i*width-3,_pixmap.height()-
            3-(_points[i]-_min)*vstep-3,6,6);
    }
    painter.restore();
}

void Chart::drawLine(){
    if(_points.size()<=1){
        return;
    }
    const double width=static_cast<
        double>(_pixmap.width())/4.0;
    const double x=width/2.0;
    const double vstep=static_cast<double>(
        _pixmap.height()-6)/(_max-_min);
    QPainter painter(&_pixmap);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(QBrush(QColor(83,157,215)),4));
    painter.setBrush(QBrush(QColor(83,157,215)));
    for(int i=1;i<_points.size();++i){
        painter.drawLine(x+(i-1)*width,_pixmap.height()-
            3-(_points[i-1]-_min)*vstep,x+i*width,_pixmap.
            height()-3-(_points[i]-_min)*vstep);
    }
    painter.restore();
}

void Chart::drawText(){
    const double textWidth=static_cast<
        double>(_pixmap.width())/4.0;
    QPainter painter(&_pixmap);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setFont(QFont("Calibri",10));
    painter.setPen(QColor(0,0,0));
    for(int i=0;i<_points.size();++i){
        painter.drawText(i*textWidth,0,
            textWidth,_pixmap.height(),
            Qt::AlignCenter,QString("%1").
            arg(_points[i],0,'f',_prec));
    }
    painter.restore();
}
