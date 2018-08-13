#ifndef TESTDATALISTMODEL_H
#define TESTDATALISTMODEL_H

#include <QAbstractListModel>

class TestDataListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TestDataListModel(QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // TESTDATALISTMODEL_H