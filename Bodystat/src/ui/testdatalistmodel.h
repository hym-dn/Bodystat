#ifndef TEST_DATA_LISTMODEL_H
#define TEST_DATA_LISTMODEL_H

#include<QAbstractListModel>

class TestDataListModel
    :public QAbstractListModel{
    Q_OBJECT
public:
    explicit TestDataListModel(QObject *parent=0);
    virtual ~TestDataListModel();
public:
    void update();
protected:
    virtual int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index,int role=Qt::DisplayRole) const override;
};

#endif // TEST_DATA_LISTMODEL_H
