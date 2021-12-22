#include "qtableviewmodel.h"

QTableViewModel::QTableViewModel(QObject *parent):QAbstractListModel(parent)
{
    values = new QList<JsonInfo>;
}

int QTableViewModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

int QTableViewModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant QTableViewModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole:
            {
                switch (index.column()) {
                    case 0: {
                        value = this->values->at(index.row()).getId();
                        break;
                    }
                    case 1: {
                        value = this->values->at(index.row()).getName();
                        break;
                    }
                    case 2: {
                        value = this->values->at(index.row()).getStatus();
                        break;
                    }
                    case 3: {
                        value = this->values->at(index.row()).getPrice();
                        break;
                    }
                }
            }
            break;

            case Qt::UserRole:
            {
                value = this->values->at(index.row()).getId();
            }
            break;

            default:
                break;
        }

    return value;
}

void QTableViewModel::populate(QList<JsonInfo> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
 }
