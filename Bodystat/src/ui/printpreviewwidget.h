#ifndef PRINT_PREVIEW_WIDGET_H
#define PRINT_PREVIEW_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class PrintPreviewWidget;
}

class PrintPreviewWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit PrintPreviewWidget(QWidget *parent=0);
    ~PrintPreviewWidget();
private:
    void initUi();
private:
    Ui::PrintPreviewWidget *_ui;
};

#endif // PRINT_PREVIEW_WIDGET_H
