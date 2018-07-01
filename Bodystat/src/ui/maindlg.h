#ifndef MAIN_DLG_H
#define MAIN_DLG_H

#include<QDialog>

namespace Ui{
    class MainDlg;
}
class QWidget;

class MainDlg
    :public QDialog{
    Q_OBJECT
public:
    explicit MainDlg(QWidget *parent=0);
    ~MainDlg();
private:
    typedef enum{
        SUB_WIDGET_ID_SUBJ=1,
    }SubWidgetID;
private slots:
    void onSubWidgetClose();
    void onNewSubjToolButtonClicked(bool);
private:
    void customUi();
    void initUi();
    void creat(const SubWidgetID widgetId);
    void destry();
private:
    Ui::MainDlg *_ui;
    QWidget *_subWidget;
};

#endif // MAIN_DLG_H
