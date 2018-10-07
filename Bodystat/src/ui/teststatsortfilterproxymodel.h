#ifndef TEST_STAT_SORT_FILTER_PROXY_MODEL_H
#define TEST_STAT_SORT_FILTER_PROXY_MODEL_H

#include<QSortFilterProxyModel>

class TestStatSortFilterProxyModel
    :public QSortFilterProxyModel{
    Q_OBJECT
public:
    TestStatSortFilterProxyModel(
        QObject *parent=Q_NULLPTR);
    virtual ~TestStatSortFilterProxyModel();
public:
    void setMatchString(const QString &string);
    const QString &getMatchString() const;
protected:
    virtual bool filterAcceptsRow(int source_row,
        const QModelIndex &source_parent) const override;
private:
    QString _matchString;
};

#endif // TEST_STAT_SORT_FILTER_PROXY_MODEL_H
