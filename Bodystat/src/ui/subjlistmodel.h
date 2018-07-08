#ifndef SUBJ_LIST_MODEL_H
#define SUBJ_LIST_MODEL_H

#include <QAbstractListModel>

class SubjListModel
    :public QAbstractListModel{
    Q_OBJECT
public:
    explicit SubjListModel(
        QObject *parent=0);
    virtual ~SubjListModel();
protected:
    virtual int rowCount(
        const QModelIndex &parent=
        QModelIndex()) const override;
    virtual QVariant data(
        const QModelIndex &index,
        int role=Qt::DisplayRole) const override;
};

#endif // SUBJ_LIST_MODEL_H
