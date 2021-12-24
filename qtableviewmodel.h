#ifndef QTABLEVIEWMODEL_H
#define QTABLEVIEWMODEL_H

#include "jsoninfo.h"
#include <QModelIndex>

class QTableViewModel: public QAbstractListModel
{
public:
    QTableViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void populate(QList<JsonInfo> *newValues);

    QHash<int, QByteArray> roleNames() const;
    void add();
private:
    QList<JsonInfo> *m_data;
};

#endif // QTABLEVIEWMODEL_H
