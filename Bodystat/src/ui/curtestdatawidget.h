#ifndef CURTESTDATAWIDGET_H
#define CURTESTDATAWIDGET_H

#include <QWidget>

namespace Ui {
class CurTestDataWidget;
}

class CurTestDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CurTestDataWidget(QWidget *parent = 0);
    ~CurTestDataWidget();

private:
    Ui::CurTestDataWidget *ui;
};

#endif // CURTESTDATAWIDGET_H
