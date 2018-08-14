#ifndef CUR_TEST_DATA_WIDGET_H
#define CUR_TEST_DATA_WIDGET_H

#include<QWidget>

namespace Ui{
    class CurTestDataWidget;
}

class CurTestDataWidget
    :public QWidget{
    Q_OBJECT
public:
    explicit CurTestDataWidget(QWidget *parent=0);
    virtual ~CurTestDataWidget();
private slots:
    void onCurTestDataChanged();
private:
    void initUi();
    void updateUi();
private:
    Ui::CurTestDataWidget *_ui;
};

#endif // CUR_TEST_DATA_WIDGET_H
