#ifndef NEW_SUBJ_DLG_H
#define NEW_SUBJ_DLG_H

#include<QDialog>

namespace Ui{
    class NewSubjDlg;
}

class NewSubjDlg
    :public QDialog{
    Q_OBJECT
public:
    explicit NewSubjDlg(QWidget *parent=0);
    ~NewSubjDlg();
private slots:
    void onNewSubjWidgetClosed();
private:
    Ui::NewSubjDlg *_ui;
};

#endif // NEW_SUBJ_DLG_H
