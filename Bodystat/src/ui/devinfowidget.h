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
    typedef enum{
        TASK_NONE=1000,
        TASK_SCAN=1001,
        TASK_RELOAD=1002,
    }Task;
public:
    explicit DevInfoWidget(QWidget *parent=0);
    virtual ~DevInfoWidget();
private slots:
    void onScanDevPushButtonClicked(bool);
    void onReloadDevPushButtonClicked(bool);
    void onBtDrivInfoChanged();
    void onDevNameChanged();
    void onDevFirmwareVChanged();
    void onDevSeriNumChanged();
    void onDevCalibDateChanged();
    void onBtTaskDone(const unsigned int id,
        const unsigned int err);
private:
    void initUi();
private:
    Task _task;
    Ui::DevInfoWidget *_ui;
};

#endif // DEV_INFO_WIDGET_H
