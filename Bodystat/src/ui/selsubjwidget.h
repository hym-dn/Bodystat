#ifndef SEL_SUBJ_WIDGET_H
#define SEL_SUBJ_WIDGET_H

#include<QWidget>

namespace Ui{
    class SelSubjWidget;
}

class SelSubjWidget
    :public QWidget{
    Q_OBJECT
public:
    explicit SelSubjWidget(
        QWidget *parent=0);
    ~SelSubjWidget();
private:
    Ui::SelSubjWidget *_ui;
};

#endif // SEL_SUBJ_WIDGET_H
