#include "maindlg.h"
#include "ui_maindlg.h"

MainDlg::MainDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDlg)
{
    ui->setupUi(this);
}

MainDlg::~MainDlg()
{
    delete ui;
}
