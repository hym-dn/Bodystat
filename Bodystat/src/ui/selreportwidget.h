#ifndef SEL_REPORT_WIDGET_H
#define SEL_REPORT_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class SelReportWidget;
}

class SelReportWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit SelReportWidget(QWidget *parent=0);
    virtual ~SelReportWidget();
signals:
    void printPreview();
private slots:
    void onOkPushButtonClicked(bool);
private:
    void initUi();
private:
    Ui::SelReportWidget *_ui;
};

#endif // SEL_REPORT_WIDGET_H
