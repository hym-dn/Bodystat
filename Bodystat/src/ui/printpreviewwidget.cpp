#include"printpreviewwidget.h"
#include"ui_printpreviewwidget.h"
#include<QAxWidget>

PrintPreviewWidget::PrintPreviewWidget(QWidget *parent/*=0*/)
    :MdiSubWidget(parent)
    ,_ui(new Ui::PrintPreviewWidget){
    _ui->setupUi(this);
    initUi();
}

PrintPreviewWidget::~PrintPreviewWidget(){
    delete _ui;
}

void PrintPreviewWidget::initUi(){
    QAxWidget *widget=new QAxWidget(this);
    widget->setControl("Microsoft Web Browser");
    _ui->_mainVerticalLayout->addWidget(widget);
    widget->dynamicCall("Navigate(const QString&)",
        QCoreApplication::applicationDirPath()+
        "/temp/report.pdf");
}
