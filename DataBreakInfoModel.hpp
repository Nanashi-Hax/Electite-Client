#pragma once

#include <QAbstractTableModel>

class DataBreakInfoEntry
{
public:
    DataBreakInfoEntry(uint32_t dataAddress, uint32_t instructionAddress);

    uint32_t dataAddress() const;
    uint32_t instructionAddress() const;
    uint32_t times() const;
    void addTimes();

private:
    uint32_t _dataAddress;
    uint32_t _instructionAddress;
    uint32_t _times;
};

class DataBreakInfoModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DataBreakInfoModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

    void add(DataBreakInfoEntry entry);
    void clear();

private:
    QList<DataBreakInfoEntry> list;
};
