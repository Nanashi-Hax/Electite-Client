#include "DataBreakInfoModel.hpp"

DataBreakInfoEntry::DataBreakInfoEntry(uint32_t dataAddress, uint32_t instructionAddress)
:
_dataAddress(dataAddress), _instructionAddress(instructionAddress), _times(0) {}

uint32_t DataBreakInfoEntry::dataAddress() const
{
    return _dataAddress;
}

uint32_t DataBreakInfoEntry::instructionAddress() const
{
    return _instructionAddress;
}

uint32_t DataBreakInfoEntry::times() const
{
    return _times;
}

void DataBreakInfoEntry::addTimes()
{
    _times++;
}

DataBreakInfoModel::DataBreakInfoModel(QObject * parent)
:
QAbstractTableModel(parent), list() {}

int DataBreakInfoModel::rowCount(const QModelIndex & parent) const
{
    return list.count();
}

int DataBreakInfoModel::columnCount(const QModelIndex & parent) const
{
    return 3;
}

QVariant DataBreakInfoModel::data(const QModelIndex & index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        switch(index.column())
        {
            case 0:
            {
                uint32_t dataAddress = list.at(index.row()).dataAddress();
                return QString("0x") + QString("%1").arg(dataAddress, 8, 16, QChar('0')).toUpper();
            }
            case 1:
            {
                uint32_t instructionAddress = list.at(index.row()).instructionAddress();
                return QString("0x") + QString("%1").arg(instructionAddress, 8, 16, QChar('0')).toUpper();
            }
            case 2:
            {
                uint32_t times = list.at(index.row()).times();
                return QString("%1").arg(times);
            }
            default:
            {
                return QVariant();
            }
        }
    }
    return QVariant();
}

void DataBreakInfoModel::add(DataBreakInfoEntry entry)
{
    for(int i = 0; i < list.size(); i++)
    {
        auto& it = list[i];
        if(it.dataAddress() == entry.dataAddress() && it.instructionAddress() == entry.instructionAddress())
        {
            it.addTimes();

            QModelIndex idx = index(i, 2);
            emit dataChanged(idx, idx);

            return;
        }
    }
    int row = list.size();
    beginInsertRows(QModelIndex(), row, row);
    list.append(entry);
    endInsertRows();
}

void DataBreakInfoModel::clear()
{
    beginResetModel();
    list.clear();
    endResetModel();
}
