#ifndef SUBJ_SORT_FILTER_PROXY_MODEL_H
#define SUBJ_SORT_FILTER_PROXY_MODEL_H

#include<QSortFilterProxyModel>

class SubjSortFilterProxyModel
    :public QSortFilterProxyModel{
public:
    SubjSortFilterProxyModel(
        QObject *parent=Q_NULLPTR);
    virtual ~SubjSortFilterProxyModel();
public:
    void setMatchString(const QString &string);
    const QString &getMatchString() const;
protected:
    virtual bool filterAcceptsRow(int source_row,
        const QModelIndex &source_parent) const override;
private:
    QString _matchString;
};

#endif // SUBJ_SORT_FILTER_PROXY_MODEL_H
