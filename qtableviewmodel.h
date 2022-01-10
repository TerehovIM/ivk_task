#ifndef QTABLEVIEWMODEL_H
#define QTABLEVIEWMODEL_H

#include "jsoninfo.h"
#include <QModelIndex>

class QTableViewModel: public QAbstractListModel
{
public:
    QTableViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    void update(QList<JsonInfo> newValues);
private:
    QList<JsonInfo> values;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // QTABLEVIEWMODEL_H
