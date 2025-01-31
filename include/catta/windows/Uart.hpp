#pragma once

// catta
#include <catta/hardware/uart/Baudrate.hpp>
#include <catta/hardware/uart/DataBits.hpp>
#include <catta/hardware/uart/Parity.hpp>
#include <catta/hardware/uart/StopBits.hpp>
#include <catta/windows/UartError.hpp>

// std
#include <iostream>
#include <optional>

namespace catta
{
namespace windows
{
/**
 * @brief Class to handle uart communication for windows like systems.
 * @author CattaTech - Maik Urbannek
 */
class Uart
{
  public:
    /**
     * Destructor. Frees uart handle.
     */
    ~Uart() noexcept { remove(); }
    /**
     * Move constructor.
     * @param[in,out] other Other uart handle. Moves handle in this uart. Other uart is empty afterwards.
     */
    [[nodiscard]] Uart(Uart &&other) noexcept : _fd(other._fd), _error(other._error)
    {
        other._fd = nullptr;
        other._error = Error::empty();
    }
    /**
     * Move assigment. If this uart handle was not empty befor the uart is freed.
     * @param[in,out] other Other uart handle. Moves handle in this uart. Other uart is empty afterwards.
     */
    void operator=(Uart &&other) noexcept
    {
        remove();
        _fd = other._fd;
        _error = other._error;
        other._fd = nullptr;
        other._error = Error::empty();
    }
    /**
     * @param[in] device Address of the device. E.g. 'COM1'.
     * @param[in] baudrate The baudrate for uart communication. Can not be empty.
     * @param[in] parity The parity for uart communication. Can be empty for no parity.
     * @param[in] dataBits The data bits size for uart communication.  Can not be empty.
     * @param[in] stopBits The stop bits size for uart communication.  Can not be empty.
     * @return Returns uart handle if device is free, otherwise the empty device.
     */
    [[nodiscard]] static Uart create(const std::string_view device, const catta::hardware::uart::Baudrate baudrate,
                                     const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                     const catta::hardware::uart::StopBits stopBits) noexcept;
    /**
     * @param[in] c The character to send via uart handle.
     * @return Returns @b true if the character was send, otherwise @b false. If @b false is returned, the character has to bes sent again.
     */
    [[nodiscard]] bool write(const char c) noexcept;
    /**
     * @return Returns a character if received via uart, otherwise empty.
     */
    [[nodiscard]] std::optional<char> read() noexcept;
    /**
     * @return Returns @b true if uart handle is invalid/empty, otherwise @b false.
     */
    [[nodiscard]] bool isEmpty() const noexcept { return _fd == nullptr && _error.isEmpty(); }
    /**
     * @return Returns an invalid/empty handle.
     */
    [[nodiscard]] static Uart empty() noexcept { return Uart{nullptr, Error::empty()}; }
    Uart(const Uart &) = delete;
    Uart operator=(const Uart &) = delete;
    /**
     * Enum class of possible uart errors.
     */
    using Error = catta::windows::UartError;
    /**
     * @return Returns the uart error
     */
    [[nodiscard]] Error error() const noexcept { return _error; }

  private:
    Uart(void *fd, const Error error) noexcept : _fd(fd), _error(error) {}
    Uart(const Error error) noexcept : Uart(nullptr, error) {}
    void *_fd;
    catta::windows::UartError _error;
    void remove() noexcept;
    auto handleIo(const auto result, const auto value, const auto noValue, const Error errorValue) noexcept;
};
}  // namespace windows
}  // namespace catta

#include <windows.h>

catta::windows::Uart catta::windows::Uart::create(const std::string_view device, const catta::hardware::uart::Baudrate baudrate,
                                                  const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                                  const catta::hardware::uart::StopBits stopBits) noexcept
{
    static constexpr DWORD INVALID_CBR = 0xffffffff;
    const DWORD windowsBaudrate = [baudrate]() -> DWORD
    {
        switch (baudrate)
        {
            case catta::hardware::uart::Baudrate::baudrate110():
                return CBR_110;
            case catta::hardware::uart::Baudrate::baudrate300():
                return CBR_300;
            case catta::hardware::uart::Baudrate::baudrate600():
                return CBR_600;
            case catta::hardware::uart::Baudrate::baudrate1200():
                return CBR_1200;
            case catta::hardware::uart::Baudrate::baudrate2400():
                return CBR_2400;
            case catta::hardware::uart::Baudrate::baudrate4800():
                return CBR_4800;
            case catta::hardware::uart::Baudrate::baudrate9600():
                return CBR_9600;
            case catta::hardware::uart::Baudrate::baudrate19200():
                return CBR_19200;
            case catta::hardware::uart::Baudrate::baudrate38400():
                return CBR_38400;
            case catta::hardware::uart::Baudrate::baudrate57600():
                return CBR_57600;
            case catta::hardware::uart::Baudrate::baudrate115200():
                return CBR_115200;
                [[unlikely]] default : return INVALID_CBR;
        }
    }();

    if (baudrate.isEmpty() || windowsBaudrate == INVALID_CBR) return Uart{Error::invalidBaudrate()};
    if (dataBits.isEmpty()) return Uart{Error::invalidDataBits()};
    if (stopBits.isEmpty()) return Uart{Error::invalidStopBits()};

    void *fd = CreateFileA(device.data(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);

    if (fd == INVALID_HANDLE_VALUE) return Uart{Error::couldNotOpenDevice()};

    auto error = [fd](const Error error)
    {
        CloseHandle(fd);
        return Uart{error};
    };

    DCB portSettings = {};
    portSettings.DCBlength = sizeof(portSettings);

    if (!GetCommState(fd, &portSettings)) return error(Error::couldNotGetCommState());

    portSettings.BaudRate = windowsBaudrate;
    portSettings.ByteSize = dataBits.isFive() ? 5 : dataBits.isSix() ? 6 : dataBits.isSeven() ? 7 : 8;
    portSettings.Parity = parity.isOdd() ? ODDPARITY : parity.isEven() ? EVENPARITY : NOPARITY;
    portSettings.StopBits = (stopBits.isOne() ? ONESTOPBIT : TWOSTOPBITS);

    if (!SetCommState(fd, &portSettings)) return error(Error::couldNotSetCommState());

    COMMTIMEOUTS Cptimeouts = {.ReadIntervalTimeout = MAXDWORD,
                               .ReadTotalTimeoutMultiplier = 0,
                               .ReadTotalTimeoutConstant = 0,
                               .WriteTotalTimeoutMultiplier = 0,
                               .WriteTotalTimeoutConstant = 0};

    if (!SetCommTimeouts(fd, &Cptimeouts)) return error(Error::couldNotSetCommTimeouts());

    return Uart{fd, Error::empty()};
}

auto catta::windows::Uart::handleIo(const auto result, const auto value, const auto noValue, const Error errorValue) noexcept
{
    if (!result)
    {
        const auto e = GetLastError();
        if (e != ERROR_IO_PENDING)
        {
            CloseHandle(_fd);
            _fd = nullptr;
            _error = errorValue;
        }
        return noValue();
    }
    return value();
}

bool catta::windows::Uart::write(const char c) noexcept
{
    if (_fd == nullptr) [[unlikely]]
        return false;
    DWORD n = 0;
    const auto result = WriteFile(_fd, &c, 1, &n, nullptr);
    const auto value = [&n]() { return n == 1; };
    const auto noValue = []() { return false; };

    return handleIo(result, value, noValue, Error::writeFailed());
}

std::optional<char> catta::windows::Uart::read() noexcept
{
    if (_fd == nullptr) [[unlikely]]
        return false;
    char c = '\0';
    DWORD n = 0;
    const auto result = ReadFile(_fd, &c, 1, &n, nullptr);
    const auto value = [&c, &n]() { return n == 1 ? std::optional<char>{c} : std::optional<char>(); };
    const auto noValue = []() { return std::optional<char>{}; };
    return handleIo(result, value, noValue, Error::readFailed());
}

void catta::windows::Uart::remove() noexcept
{
    if (_fd != nullptr) CloseHandle(_fd);
    _fd = nullptr;
}
