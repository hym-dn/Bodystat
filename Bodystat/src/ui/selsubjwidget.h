#ifndef SEL_SUBJ_WIDGET_H
#define SEL_SUBJ_WIDGET_H

#include<QItemSelection>
#include"mdisubwidget.h"

namespace Ui{
    class SelSubjWidget;
}
class Subject;

class SelSubjWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit SelSubjWidget(QWidget *parent=0);
    ~SelSubjWidget();
protected:
    virtual void closeEvent(QCloseEvent *event);
private slots:
    void onFilterLineEditTextChanged(const QString &text);
    void onSubjListViewSelectionChanged(
        const QItemSelection &,const QItemSelection &);
    void onSubjListViewDoubleClicked(const QModelIndex &index);
    void onSelSubjPushButtonClicked(bool);
private:
    void initUi();
    void clearSubj();
    void showSubj(const Subject &subj);
private:
    Ui::SelSubjWidget *_ui;
};

#endif // SEL_SUBJ_WIDGET_H
