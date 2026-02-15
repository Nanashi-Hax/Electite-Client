#include "ElectiteViewModel.hpp"
#include <QDebug>

void ElectiteViewModel::onStart()
{
    electite.start();
    electite.setDataBreakInfoCallback([this](uint32_t d, uint32_t i){ onDataBreakReceived(d, i); });
}

void ElectiteViewModel::onStop()
{
    electite.stop();
}

void ElectiteViewModel::onConnectServer(const QString& ipAddress)
{
    electite.connectServer(ipAddress.toStdString());
}

void ElectiteViewModel::onDisconnectServer()
{
    electite.disconnectServer();
}

void ElectiteViewModel::onSetDataBreakpoint(uint32_t address, bool read, bool write, Electite::BreakpointSize size)
{
    electite.setDataBreakpoint(address, read, write, size);
}

void ElectiteViewModel::onUnsetDataBreakpoint()
{
    electite.unsetDataBreakpoint();
}

void ElectiteViewModel::onDataBreakReceived(uint32_t dAddress, uint32_t iAddress)
{
    emit dataBreakReceived(dAddress, iAddress);
}
