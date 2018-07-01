#ifndef MDI_SUB_WIDGET_H
#define MDI_SUB_WIDGET_H

#include<QWidget>

class MdiSubWidget
    :public QWidget{
    Q_OBJECT
public:
    explicit MdiSubWidget(
        QWidget *parent=0);
    virtual ~MdiSubWidget();
signals:
    void s_close();
protected:
    virtual void closeEvent(QCloseEvent *event);
};

#endif // MDI_SUB_WIDGET_H
