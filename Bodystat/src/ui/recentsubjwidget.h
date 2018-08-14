#ifndef RECENT_SUBJ_WIDGET_H
#define RECENT_SUBJ_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class RecentSubjWidget;
}

class RecentSubjWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit RecentSubjWidget(QWidget *parent=0);
    virtual ~RecentSubjWidget();
private:
    Ui::RecentSubjWidget *_ui;
};

#endif // RECENT_SUBJ_WIDGET_H
