#ifndef SUBJ_WIDGET_H
#define SUBJ_WIDGET_H

#include"mdisubwidget.h"
#include<QScopedPointer>

namespace Ui{
    class SubjWidget;
}
class SubjInfo;

class SubjWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    typedef enum{MODE_NEW=1,
        MODE_EDIT=2,MODE_DELETE=3,}Mode;
public:
    explicit SubjWidget(
        const Mode mode=MODE_NEW,
        const SubjInfo *subjInfo=0,
        QWidget *parent=0);
    virtual ~SubjWidget();
private slots:
    void onSavePushButtonClicked(bool);
    void onDeletePushButtonClicked(bool);
    void onCancelPushButtonClicked(bool);
private:
    void initUi();
    void toUi();
    int toSubjInfo(SubjInfo &subjInfo) const;
private:
    typedef QScopedPointer<SubjInfo> PtrSubjInfo;
private:
    const Mode _mode;
    PtrSubjInfo _subjInfo;
    Ui::SubjWidget *_ui;
};

#endif //SUBJ_WIDGET_H
