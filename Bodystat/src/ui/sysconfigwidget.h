#ifndef SYS_CONFIG_WIDGET_H
#define SYS_CONFIG_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class SysConfigWidget;
}

class SysConfigWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit SysConfigWidget(QWidget *parent=0);
    ~SysConfigWidget();
private slots:
    void onSavePushButtonClicked(bool);
private:
    void initUi();
private:
    Ui::SysConfigWidget *_ui;
};

#endif // SYS_CONFIG_WIDGET_H
