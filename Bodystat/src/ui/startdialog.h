#ifndef START_DIALOG_H
#define START_DIALOG_H

#include<QDialog>

namespace Ui{
    class StartDialog;
}

class StartDialog
    :public QDialog{
    Q_OBJECT
public:
    explicit StartDialog(QWidget *parent=0);
    virtual ~StartDialog();
protected:
    virtual void keyPressEvent(QKeyEvent *event);
private slots:
    void onTaskDone(
        const unsigned int id,const int err);
private:
    void initUi();
private:
    Ui::StartDialog *_ui;
};

#endif // START_DIALOG_H
