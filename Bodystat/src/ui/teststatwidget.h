﻿#ifndef TEST_STAT_WIDGET_H
#define TEST_STAT_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class TestStatWidget;
}

class TestStatWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit TestStatWidget(QWidget *parent=0);
    ~TestStatWidget();
private:
    Ui::TestStatWidget *_ui;
};

#endif // TEST_STAT_WIDGET_H
