#ifndef SUBJ_WIDGET_H
#define SUBJ_WIDGET_H

#include"mdisubwidget.h"

namespace Ui{
    class SubjWidget;
}
class Subject;

class SubjWidget
    :public MdiSubWidget{
    Q_OBJECT
public:
    typedef enum{
        MODE_NEW=1,
        MODE_EDIT=2,
    }Mode;
public:
    explicit SubjWidget(
        const Mode mode=MODE_NEW,
        QWidget *parent=0);
    virtual ~SubjWidget();
private:
    void initUi();
    void toUi();
    int toSubject(Subject &subj) const;
private:
    const Mode _mode;
    Subject *_subject;
    Ui::SubjWidget *_ui;
};

#endif //SUBJ_WIDGET_H
