#ifndef DOWNLOAD_DATA_WIDGET_H
#define DOWNLOAD_DATA_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class DownloadDataWidget;
}

class DownloadDataWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    typedef enum{
        TASK_NONE=1000,
        TASK_DOWNLOAD=1001,
    }Task;
public:
    explicit DownloadDataWidget(
        QWidget *parent=0);
    ~DownloadDataWidget();
signals:
    void showAssignDownloadWidget(bool);
protected:
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void onBtTaskDone(const unsigned int id,
        const unsigned int err);
    void onOpenTestDialogPushButton(bool);
private:
    void initUi();
private:
    Task _task;
    Ui::DownloadDataWidget *_ui;
};

#endif // DOWNLOAD_DATA_WIDGET_H
