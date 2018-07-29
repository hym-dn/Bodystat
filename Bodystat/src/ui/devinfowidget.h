#ifndef DEV_INFO_WIDGET_H
#define DEV_INFO_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class DevInfoWidget;
}

class DevInfoWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit DevInfoWidget(QWidget *parent=0);
    virtual ~DevInfoWidget();
private slots:
    void onScanDevPushButtonClicked(bool);
    void onBtStackInfoChanged();
private:
    void initUi();
private:
    Ui::DevInfoWidget *_ui;
};

#endif // DEV_INFO_WIDGET_H
