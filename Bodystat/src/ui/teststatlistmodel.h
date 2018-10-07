#ifndef TEST_STAT_LIST_MODEL_H
#define TEST_STAT_LIST_MODEL_H

#include<QAbstractListModel>

class TestStatListModel
    :public QAbstractListModel{
    Q_OBJECT
public:
    explicit TestStatListModel(
        QObject *parent=0);
    virtual ~TestStatListModel();
protected:
    virtual int rowCount(
        const QModelIndex &parent=
        QModelIndex()) const override;
    virtual QVariant data(
        const QModelIndex &index,
        int role=Qt::DisplayRole) const override;
};

#endif // TEST_STAT_LIST_MODEL_H
