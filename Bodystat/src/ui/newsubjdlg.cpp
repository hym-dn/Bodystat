#include"newsubjdlg.h"
#include"ui_newsubjdlg.h"

NewSubjDlg::NewSubjDlg(QWidget *parent/*=0*/)
    :QDialog(parent)
    ,_ui(new Ui::NewSubjDlg){
    _ui->setupUi(this);
    connect(_ui->_newSubjWidget,SIGNAL(s_close()),
        this,SLOT(onNewSubjWidgetClosed()));
}

NewSubjDlg::~NewSubjDlg(){
    delete _ui;
}

void NewSubjDlg::onNewSubjWidgetClosed(){
    done(0);
}
