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
    explicit DownloadDataWidget(
        QWidget *parent=0);
    ~DownloadDataWidget();
private:
    void initUi();
private:
    Ui::DownloadDataWidget *_ui;
};

#endif // DOWNLOAD_DATA_WIDGET_H
