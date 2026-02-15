#pragma once

#include <QObject>
#include "Electite.hpp"

class ElectiteViewModel : public QObject
{
    Q_OBJECT

public slots:
    void onStart();
    void onStop();

    void onConnectServer(const QString& ipAddress);
    void onDisconnectServer();

    void onSetDataBreakpoint(uint32_t address, bool read, bool write, Electite::BreakpointSize size);
    void onUnsetDataBreakpoint();

public:
    void onDataBreakReceived(uint32_t dAddress, uint32_t iAddress);

signals:
    void dataBreakReceived(uint32_t dAddress, uint32_t iAddress);

private:
    Electite electite;
};
