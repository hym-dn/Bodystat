#include"startdialog.h"
#include"ui_startdialog.h"
#include"../task/starttask.h"
#include"../task/taskpool.h"
#include<QKeyEvent>
#include<QMovie>

StartDialog::StartDialog(QWidget *parent/*=0*/)
    :QDialog(parent)
    ,_ui(new Ui::StartDialog){
    _ui->setupUi(this);
    initUi();
    TaskPool::PtrTask task(new StartTask);
    Q_ASSERT(!task.isNull());
    TaskPool::instance()->add(task);
}

StartDialog::~StartDialog(){
    delete _ui;
}

void StartDialog::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Escape:
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}

void StartDialog::onTaskDone(
    const unsigned int id,const int err){
    if(id==StartTask::ID){
        done(err);
    }
}

void StartDialog::initUi(){
    setWindowFlags(Qt::FramelessWindowHint);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    _ui->_logoLabel->setPixmap(QPixmap::fromImage(
        QImage(":rc/logo.png")));
    QMovie *movie=new QMovie(":rc/sprogress.gif",
        QByteArray(),_ui->_progressLabel);
    _ui->_progressLabel->setMovie(movie);
    movie->start();
    connect(TaskPool::instance(),SIGNAL(taskDone(
        const unsigned int,const int)),this,SLOT(
        onTaskDone(const unsigned int,const int)));
}
