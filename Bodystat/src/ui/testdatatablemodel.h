#ifndef TEST_DATA_TABLE_MODEL_H
#define TEST_DATA_TABLE_MODEL_H

#include<QAbstractTableModel>

class TestDataTableModel
    :public QAbstractTableModel{
    Q_OBJECT
public:
    explicit TestDataTableModel(
        QObject *parent=0);
    virtual ~TestDataTableModel();
public:
    void update();
private:
    enum{COLUMN_COUNT=12,};
private:
    QVariant headerData(int section,
        Qt::Orientation orientation,
        int role=Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &
        parent=QModelIndex()) const override;
    int columnCount(const QModelIndex &
        parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
        int role=Qt::DisplayRole) const override;
};

#endif // TEST_DATA_TABLE_MODEL_H
