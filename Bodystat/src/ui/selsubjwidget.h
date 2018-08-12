#ifndef SEL_SUBJ_WIDGET_H
#define SEL_SUBJ_WIDGET_H

#include<QItemSelection>
#include"mdisubwidget.h"

namespace Ui{
    class SelSubjWidget;
}
class SubjInfo;

class SelSubjWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    explicit SelSubjWidget(QWidget *parent=0);
    ~SelSubjWidget();
private slots:
    void onFilterLineEditTextChanged(const QString &text);
    void onSubjListViewSelectionChanged(
        const QItemSelection &,const QItemSelection &);
    void onSubjListViewDoubleClicked(const QModelIndex &index);
    void onSelSubjPushButtonClicked(bool);
private:
    void initUi();
    void clearSubjInfo();
    void showSubjInfo(const SubjInfo &subjInfo);
    void updateCurSubjInfo(const SubjInfo &subjInfo);
private:
    Ui::SelSubjWidget *_ui;
};

#endif // SEL_SUBJ_WIDGET_H
