#include"waitdialog.h"
#include"ui_waitdialog.h"
#include"../task/taskpool.h"
#include"../task/task.h"
#include<QKeyEvent>
#include<QMovie>

WaitDialog::WaitDialog(
    PtrTask &task,QWidget *parent/*=0*/)
    :QDialog(parent)
    ,_task(task)
    ,_ui(new Ui::WaitDialog){
    Q_ASSERT(!_task.isNull());
    _ui->setupUi(this);
    initUi();
    TaskPool::instance()->add(_task);
}

WaitDialog::~WaitDialog(){
    delete _ui;
}

void WaitDialog::keyPressEvent(
    QKeyEvent *event){
    // 键盘
    switch(event->key()){
    // ESC
    case Qt::Key_Escape:
        break;
    // 其它
    default:
        QDialog::keyPressEvent(event);
    }
}

void WaitDialog::initUi(){
    // 窗口
    setWindowFlags(
        Qt::CustomizeWindowHint|
        Qt::WindowContextHelpButtonHint);
    // 控件
    QMovie *movie=new QMovie(":rc/wait.gif",
        QByteArray(),_ui->_movieLabel);
    _ui->_movieLabel->setMovie(movie);
    movie->start();
    // 信号、槽
    connect(TaskPool::instance(),
        SIGNAL(taskFinished(unsigned int,int)),
        this,SLOT(onTaskFinished(unsigned int,int)));
}

void WaitDialog::onTaskFinished(
    const unsigned int id,int res){
    if(id==_task->getId()){
        if(res<0){
            done(0);
        }else{
            done(1);
        }
    }
}
