#include "qtableviewmodel.h"

QTableViewModel::QTableViewModel(QObject *parent):QAbstractListModel(parent)
{

}

int QTableViewModel::rowCount(const QModelIndex &) const
{
    return values.count();
}

int QTableViewModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant QTableViewModel::data( const QModelIndex &index, int role ) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() >= values.count())
        return QVariant();
    if(role == Qt::DisplayRole && !values.isEmpty())
    {
        switch (index.column()) {
            case 0:
            {
                return this->values.at(index.row()).getId();
                break;
            }
            case 1:
            {
                return this->values.at(index.row()).getName();
                break;
            }
            case 2:
            {
                return this->values.at(index.row()).getStatus();
                break;
            }
            case 3:
            {
                return this->values.at(index.row()).getPrice();
                break;
            }
            default:
            {
                return QVariant();
            }
        }
    }
    else
        return QVariant();
}

void QTableViewModel::update(QList<JsonInfo> newValues)
{
    if(!this->values.isEmpty())
    {
        this->beginRemoveRows(QModelIndex(), 1, values.count());
        this->endRemoveRows();
        values.clear();
    }

    this->values = newValues;
    int idx = this->values.count();
    this->beginInsertRows(QModelIndex(), 1, idx);
    endInsertRows();
 }
