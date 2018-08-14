#ifndef MAIN_DLG_H
#define MAIN_DLG_H

#include<QDialog>

namespace Ui{
    class MainDlg;
}
class QWidget;
class QMenu;

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
        SUB_WIDGET_ID_ASN_DWLD=5,
        SUB_WIDGET_ID_DWL_DATA=6,
        SUB_WIDGET_ID_DEV_INFO=7,
    }SubWidgetID;
private slots:
    void onSubWidgetClose();
    void onNewSubjToolButtonClicked(bool);
    void onSelSubjToolButtonClicked(bool);
    void onDelSubjToolButtonClicked(bool);
    void onEdtSubjToolButtonClicked(bool);
    void onRecSubjToolButtonPressed();
    void onRecSubjActionTriggered(bool);
    void onAssignDownloadToolButtonClicked(bool);
    void onDownloadDataToolButtonClicked(bool);
    void onDevInfoToolButtonClicked(bool);
    void onBtTaskStart(const unsigned int id);
    void onBtTaskDone(const unsigned int id,
        const unsigned int err);
private:
    void customUi();
    void initUi();
    void creat(const SubWidgetID widgetId);
    void destry();
private:
    Ui::MainDlg *_ui;
    QWidget *_subWidget;
    QMenu *_recSubjMenu;
};

#endif // MAIN_DLG_H
