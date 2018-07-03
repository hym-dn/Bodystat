#ifndef CUR_SUBJ_WIDGET_H
#define CUR_SUBJ_WIDGET_H

#include<QWidget>

namespace Ui{
    class CurSubjWidget;
}

class CurSubjWidget
    :public QWidget{
    Q_OBJECT
public:
    explicit CurSubjWidget(QWidget *parent=0);
    ~CurSubjWidget();
private:
    Ui::CurSubjWidget *_ui;
};

#endif // CUR_SUBJ_WIDGET_H
