#ifndef ASSIGN_DOWNLOAD_WIDGET_H
#define ASSIGN_DOWNLOAD_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class AssignDownloadWidget;
}

class AssignDownloadWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit AssignDownloadWidget(
        QWidget *parent=0);
    virtual ~AssignDownloadWidget();
private slots:
    void onFilterLineEditTextChanged(const QString &text);
    void onNewSubjPushButtonClicked(bool);
    void onAssignTestPushButtonClicked(bool);
private:
    void initUi();
private:
    Ui::AssignDownloadWidget *_ui;
};

#endif // ASSIGN_DOWNLOAD_WIDGET_H
