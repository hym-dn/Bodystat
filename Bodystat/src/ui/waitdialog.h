#ifndef WAIT_DIALOG_H
#define WAIT_DIALOG_H

#include<QDialog>
#include<QSharedPointer>

class Task;
namespace Ui{
    class WaitDialog;
}

class WaitDialog
    :public QDialog{
    Q_OBJECT
public:
    typedef QSharedPointer<Task> PtrTask;
public:
    explicit WaitDialog(
        PtrTask &task,
        QWidget *parent=0);
    ~WaitDialog();
protected:
    virtual void keyPressEvent(
        QKeyEvent *event);
private slots:
    void onTaskDone(
        const unsigned int id,int res);
private:
    void initUi();
private:
    PtrTask _task;
    Ui::WaitDialog *_ui;
};

#endif // WAIT_DIALOG_H
