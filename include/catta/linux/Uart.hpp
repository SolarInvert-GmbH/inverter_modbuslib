#pragma once

// catta
#include <catta/hardware/uart/Baudrate.hpp>
#include <catta/hardware/uart/DataBits.hpp>
#include <catta/hardware/uart/Parity.hpp>
#include <catta/hardware/uart/StopBits.hpp>
#include <catta/linux/UartError.hpp>

// std
#include <iostream>
#include <optional>

namespace catta
{
namespace linux
{
/**
 * @brief Class to handle uart communication for linux like systems.
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
    [[nodiscard]] Uart(Uart &&other) noexcept : _fd(other._fd) { other._fd = EMPTY; }
    /**
     * Move assigment. If this uart handle was not empty befor the uart is freed.
     * @param[in,out] other Other uart handle. Moves handle in this uart. Other uart is empty afterwards.
     */
    void operator=(Uart &&other) noexcept
    {
        remove();
        _fd = other._fd;
        other._fd = EMPTY;
    }
    /**
     * @param[in] device Address of the device. E.g. '/dev/ttyUSB0'.
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
    [[nodiscard]] bool isEmpty() const noexcept { return _fd == EMPTY; }
    /**
     * @return Returns an invalid/empty handle.
     */
    [[nodiscard]] static Uart empty() noexcept { return Uart{EMPTY}; }
    Uart(const Uart &) = delete;
    Uart operator=(const Uart &) = delete;
    /**
     * Enum class of possible uart errors.
     */
    typedef catta::linux::UartError Error;
    /**
     * @return Returns the uart error
     */
    [[nodiscard]] Error error() const noexcept { return _fd < EMPTY ? Error{static_cast<std::uint8_t>(-_fd - 2)} : Error::empty(); }

  private:
    Uart(const int fd) noexcept : _fd(fd) {}
    Uart(const Error error) noexcept : Uart(getErrorFd(error)) {}
    static int getErrorFd(const Error error) noexcept { return -error - 2; }
    int _fd;
    constexpr static int EMPTY = -1;
    void remove() noexcept;
    auto handleIo(const auto result, const auto value, const auto noValue, const Error errorValue) noexcept;
};
}  // namespace linux
}  // namespace catta

#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <termios.h>
#include <unistd.h>

catta::linux::Uart catta::linux::Uart::create(const std::string_view device, const catta::hardware::uart::Baudrate baudrate,
                                              const catta::hardware::uart::Parity parity, const catta::hardware::uart::DataBits dataBits,
                                              const catta::hardware::uart::StopBits stopBits) noexcept
{
    const auto oldBautrate = [baudrate]() -> speed_t
    {
        switch (baudrate)
        {
            case catta::hardware::uart::Baudrate::baudrate50():
                return B50;
            case catta::hardware::uart::Baudrate::baudrate75():
                return B75;
            case catta::hardware::uart::Baudrate::baudrate110():
                return B110;
            case catta::hardware::uart::Baudrate::baudrate134():
                return B134;
            case catta::hardware::uart::Baudrate::baudrate150():
                return B150;
            case catta::hardware::uart::Baudrate::baudrate200():
                return B200;
            case catta::hardware::uart::Baudrate::baudrate300():
                return B300;
            case catta::hardware::uart::Baudrate::baudrate600():
                return B600;
            case catta::hardware::uart::Baudrate::baudrate1200():
                return B1200;
            case catta::hardware::uart::Baudrate::baudrate1800():
                return B1800;
            case catta::hardware::uart::Baudrate::baudrate2400():
                return B2400;
            case catta::hardware::uart::Baudrate::baudrate4800():
                return B4800;
            case catta::hardware::uart::Baudrate::baudrate9600():
                return B9600;
            case catta::hardware::uart::Baudrate::baudrate19200():
                return B19200;
            case catta::hardware::uart::Baudrate::baudrate38400():
                return B38400;
            case catta::hardware::uart::Baudrate::baudrate57600():
                return B57600;
            case catta::hardware::uart::Baudrate::baudrate115200():
                return B115200;
            case catta::hardware::uart::Baudrate::baudrate230400():
                return B230400;
            case catta::hardware::uart::Baudrate::baudrate460800():
                return B460800;
            case catta::hardware::uart::Baudrate::baudrate500000():
                return B500000;
            case catta::hardware::uart::Baudrate::baudrate576000():
                return B576000;
            case catta::hardware::uart::Baudrate::baudrate921600():
                return B921600;
            case catta::hardware::uart::Baudrate::baudrate1000000():
                return B1000000;
            case catta::hardware::uart::Baudrate::baudrate1152000():
                return B1152000;
            case catta::hardware::uart::Baudrate::baudrate1500000():
                return B1500000;
            case catta::hardware::uart::Baudrate::baudrate2000000():
                return B2000000;
            case catta::hardware::uart::Baudrate::baudrate2500000():
                return B2500000;
            case catta::hardware::uart::Baudrate::baudrate3000000():
                return B3000000;
            case catta::hardware::uart::Baudrate::baudrate3500000():
                return B3500000;
            case catta::hardware::uart::Baudrate::baudrate4000000():
                return B4000000;
                [[unlikely]] default : return B0;
        }
    }();
    static constexpr tcflag_t CSINVALID = static_cast<tcflag_t>(-1);
    const tcflag_t cs = [dataBits]()
    {
        switch (dataBits)
        {
            case catta::hardware::uart::DataBits::five():
                return tcflag_t(CS5);
            case catta::hardware::uart::DataBits::six():
                return tcflag_t(CS6);
            case catta::hardware::uart::DataBits::seven():
                return tcflag_t(CS7);
            case catta::hardware::uart::DataBits::eight():
                return tcflag_t(CS8);
            default:
                return CSINVALID;
        }
    }();
    const tcflag_t p = parity.isEven() ? PARENB : parity.isOdd() ? PARODD : 0;
    // TODO create extra errors
    if (oldBautrate == 0 || cs == CSINVALID || stopBits.isEmpty()) [[unlikely]]
        return Uart{Error::invalidBaudrate()};

    struct termios tio = {.c_iflag = 0, .c_oflag = 0, .c_cflag = 0, .c_lflag = 0, .c_line = 0, .c_cc = {}, .c_ispeed = 0, .c_ospeed = 0};

    if (cfsetospeed(&tio, oldBautrate) < 0 || cfsetispeed(&tio, oldBautrate) < 0) [[unlikely]]
        return Uart{Error::couldNotSetBaudrate()};

    tio.c_cflag &= static_cast<tcflag_t>(~CSIZE);
    tio.c_cflag |= cs;
    tio.c_cflag &= static_cast<tcflag_t>(~CRTSCTS);
    tio.c_iflag &= static_cast<tcflag_t>(~(IXON | IXOFF | IXANY));
    if (stopBits.isOne()) tio.c_cflag &= static_cast<tcflag_t>(~CSTOPB);
    if (stopBits.isTwo()) tio.c_cflag |= static_cast<tcflag_t>(CSTOPB);
    tio.c_cflag |= static_cast<tcflag_t>(CLOCAL | CREAD | p);
    tio.c_oflag = 0;
    tio.c_lflag = 0;
    tio.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO | ISIG | ECHOE | IGNCR));  // no buffer
    tio.c_lflag &= static_cast<tcflag_t>(~(OPOST));                                 // no buffer
    tio.c_cc[VTIME] = 0;
    tio.c_cc[VMIN] = 0;

    const int fd = open(device.data(), O_RDWR | O_NONBLOCK);
    // setvbuf(stdout, (char *)NULL, _IONBF, 0);

    if (fd < 0) [[unlikely]]
        return Uart{Error::couldNotOpenDevice()};
    auto error = [fd](const Error error)
    {
        close(fd);
        return Uart{error};
    };
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) [[unlikely]]
        return error(Error::deviceIsBusy());
    tcflush(fd, TCIOFLUSH);
    if (tcsetattr(fd, TCSANOW, &tio) < 0) [[unlikely]]
        return error(Error::couldNotBind());
    return Uart{fd};
}

auto catta::linux::Uart::handleIo(const auto result, const auto value, const auto noValue, const Error errorValue) noexcept
{
    const auto stop = [this, noValue](const int fd)
    {
        ::flock(_fd, LOCK_UN);
        ::close(_fd);
        _fd = fd;
        return noValue();
    };
    //   const auto end = [stop]() { return stop(getErrorFd(Error::closed())); };
    const auto error = [stop, errorValue]() { return stop(getErrorFd(errorValue)); };
    switch (result)
    {
        [[unlikely]] case 0 : return noValue();  // return end();
        [[likely]] case -1 : return (errno == EAGAIN) || (errno == EINTR) ? noValue() : error();
        [[likely]] case 1 : return value();
        [[unlikely]] default : return error();
    }
}

bool catta::linux::Uart::write(const char c) noexcept
{
    if (_fd <= EMPTY) [[unlikely]]
        return false;
    const auto value = []() { return true; };
    const auto noValue = []() { return false; };
    return handleIo(::write(_fd, &c, 1), value, noValue, Error::writeFailed());
}

std::optional<char> catta::linux::Uart::read() noexcept
{
    if (_fd <= EMPTY) [[unlikely]]
        return false;
    char c = '\0';
    const auto result = ::read(_fd, &c, 1);
    const auto value = [c]() { return std::optional<char>{c}; };
    const auto noValue = []() { return std::optional<char>{}; };
    return handleIo(result, value, noValue, Error::readFailed());
}

void catta::linux::Uart::remove() noexcept
{
    if (_fd > EMPTY)
    {
        ::flock(_fd, LOCK_UN);
        ::close(_fd);
    }
}
