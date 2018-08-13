#include "curtestdatawidget.h"
#include "ui_curtestdatawidget.h"

CurTestDataWidget::CurTestDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurTestDataWidget)
{
    ui->setupUi(this);
}

CurTestDataWidget::~CurTestDataWidget()
{
    delete ui;
}
