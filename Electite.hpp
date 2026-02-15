#pragma once

#include <Network.hpp>
#include <IO.hpp>

#include <cstdint>
#include <stop_token>
#include <thread>
#include <functional>

class Electite
{   
public:
    using DataBreakInfoCallbackFunction = std::function<void(uint32_t, uint32_t)>;

    enum class BreakpointSize : uint32_t
    {
        Invalid = 0,
        Bit8 = 1,
        Bit16 = 2,
        Bit32 = 4,
        Bit64 = 8
    };

    Electite();
    ~Electite();

    void start();
    void stop();

    void processLoop(std::stop_token token);

    void connectServer(const std::string& ipAddress);
    void disconnectServer();

    void setDataBreakpoint(uint32_t address, bool read, bool write, Electite::BreakpointSize size);
    void unsetDataBreakpoint();

    void setDataBreakInfoCallback(DataBreakInfoCallbackFunction function);

private:
    void processData(Library::IO::Stream& stream);

    std::unique_ptr<std::jthread> processThread;

    std::unique_ptr<Library::Network::TcpSocket> socket;
    std::mutex socketMutex;

    std::unique_ptr<Library::IO::Transporter> transporter;

    DataBreakInfoCallbackFunction dataBreakInfoCallback;

    static constexpr const uint16_t ELECTITE_PORT = 60000;

    enum class Command : uint32_t;
    enum class Data : uint32_t;
};
