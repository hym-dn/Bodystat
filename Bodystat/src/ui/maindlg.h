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
        SUB_WIDGET_ID_NEW_SUBJ=1,
        SUB_WIDGET_ID_SEL_SUBJ=2,
        SUB_WIDGET_ID_DEL_SUBJ=3,
        SUB_WIDGET_ID_EDT_SUBJ=4,
        SUB_WIDGET_ID_DEV_INFO=7,
    }SubWidgetID;
private slots:
    void onSubWidgetClose();
    void onNewSubjToolButtonClicked(bool);
    void onSelSubjToolButtonClicked(bool);
    void onDelSubjToolButtonClicked(bool);
    void onEdtSubjToolButtonClicked(bool);
    void onDevInfoToolButtonClicked(bool);
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
