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
    QVariant data(const QModelIndex &index, int role) const;
    void populate(QList<JsonInfo> *newValues);
private:
    QList<JsonInfo> *values;
};

#endif // QTABLEVIEWMODEL_H
