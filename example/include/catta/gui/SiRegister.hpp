#pragma once

// fltk
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>

// si
#include <catta/modbus/si/RegisterAddress.hpp>
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

// sunspec
#include <catta/modbus/sunspec/ConnectedPhase.hpp>
#include <catta/modbus/sunspec/ScaleFactor.hpp>

// gui
#include <catta/gui/Input.hpp>

namespace catta
{
namespace gui
{
/**
 * @brief DummyInverter simulates inverter on Modbus level.
 * @author CattaTech - Maik Urbannek
 */
class SiRegister : public Fl_Group
{
  private:
    static constexpr int H = 25;
    static constexpr int W_WRITE_ACTION = 100;
    static constexpr int W_ADDRESS = 50;
    static constexpr int W_TYPE = 40;
    static constexpr int W_NAME = 380;
    static constexpr int W_READ_ACTION = 100;
    static constexpr int W_VALUE = 270;

  public:
    static constexpr int defaultHeight = H;
    static constexpr int defaultWidth = W_WRITE_ACTION + W_ADDRESS + W_TYPE + W_NAME + W_READ_ACTION + W_VALUE;
    /**
     * @param[in] X The x coordinate of the widget.
     * @param[in] Y The y coordinate of the widget.
     * @param[in] W The width of the widget.
     * @param[in] H The height of the widget.
     * @param[in] address The address of the register.
     * Constructor.
     */
    template <class T>
    SiRegister(int X, int Y, int W, int H, const catta::modbus::si::RegisterAddress address, const T initial)
        : Fl_Group(0, 0, defaultWidth, defaultHeight),
          _writeActionChoice(0, 0, W_WRITE_ACTION, H, "W"),
          _addressString(createAddressString(address.raw())),
          _addressBox(W_WRITE_ACTION, 0, W_ADDRESS, H, _addressString.data()),
          _typeBox(W_WRITE_ACTION + W_ADDRESS, 0, W_TYPE, H, address.type().abbreviation().data()),
          _nameBox(W_WRITE_ACTION + W_ADDRESS + W_TYPE, 0, W_NAME, H, address.isEmpty() ? "EMPTY" : address.enumNames[address].data()),
          _readActionChoice(W_WRITE_ACTION + W_ADDRESS + W_TYPE + W_NAME, 0, W_READ_ACTION, H),
          _value(W_WRITE_ACTION + W_ADDRESS + W_TYPE + W_NAME + W_READ_ACTION, 0, W_VALUE, H, initial),
          _address(address)

    {
        auto menu = [](const char* text)
        {
            return Fl_Menu_Item{.text = text,
                                .shortcut_ = 0,
                                .callback_ = nullptr,
                                .user_data_ = nullptr,
                                .flags = 0,
                                .labeltype_ = 0,
                                .labelfont_ = 0,
                                .labelsize_ = 0,
                                .labelcolor_ = 0};
        };

        static const Fl_Menu_Item writeMenu[] = {menu("write"),      menu("do nothing"), menu("execption1"), menu("execption2"),
                                                 menu("execption3"), menu("execption4"), menu(nullptr)};

        static const Fl_Menu_Item readMenu[] = {menu("read"),       menu("do nothing"), menu("execption1"), menu("execption2"),
                                                menu("execption3"), menu("execption4"), menu(nullptr)};
        this->end();
        this->resizable(this);
        this->resize(X, Y, W, H);
        this->_writeActionChoice.menu(writeMenu);
        if (!address.isWritable()) this->_writeActionChoice.hide();
        this->_readActionChoice.menu(readMenu);
        this->_readActionChoice.callback(SiRegister::readcb, this);
        this->_writeActionChoice.box(FL_UP_BOX);
        this->_nameBox.box(FL_UP_BOX);
        this->_addressBox.box(FL_UP_BOX);
        this->_typeBox.box(FL_UP_BOX);
        this->_readActionChoice.box(FL_UP_BOX);
    }
    /**
     * @param[in] request The request to handle.
     * @return Returns the response for the input request. Can be empty.
     */
    catta::modbus::si::response::Response handleRequest(const catta::modbus::si::request::Request& request)
    {
        using Response = catta::modbus::si::response::Response;
        using Type = catta::modbus::si::request::Type;
        switch (request.type())
        {
            case Type::readRegister():
                if (!this->_address.isReadable() || this->_address != request.readRegisterValue().registerAddress()) return Response::empty();
                switch (_readActionChoice.value())
                {
                    case 0:  // read
                    {
                        using Type = catta::modbus::si::RegisterType;
                        switch (this->_address.type())
                        {
                            case Type::uint16():
                                return Response::value16(this->_value.value<catta::modbus::sunspec::ValueU16>().value());
                            case Type::sint16():
                                return Response::value16(static_cast<std::uint16_t>(this->_value.value<catta::modbus::sunspec::ValueS16>().value()));
                            case Type::scaleFactor():
                                return Response::value16(
                                    static_cast<std::uint16_t>(this->_value.value<catta::modbus::sunspec::ScaleFactor>().factorExponent()));
                            case Type::connectedPhase():
                                return Response::value16(this->_value.value<catta::modbus::sunspec::ConnectedPhase>());
                            case Type::uint32():
                                return Response::value32(this->_value.value<catta::modbus::sunspec::ValueU32>().value());
                            case Type::uint64():
                                return Response::value64(this->_value.value<catta::modbus::sunspec::ValueU64>().value());
                            case Type::string16():
                                return Response::string16(this->_value.value<catta::modbus::sunspec::String16>());
                            case Type::string32():
                                return Response::string32(this->_value.value<catta::modbus::sunspec::String32>());
                            default:
                                return Response::empty();
                        }
                    }
                    case 1:  // nothing
                        return Response::empty();
                    default:  // execption1…4
                    {
                        const auto value =
                            catta::modbus::si::response::ExceptionValue(static_cast<std::uint8_t>(this->_readActionChoice.value() - 2));
                        const auto function = request.type();
                        const auto exception = catta::modbus::si::response::Exception::create(value, function);
                        return Response::exception(exception);
                    }
                }
            case Type::writeRegister():
                if (!this->_address.isWritable() || this->_address != request.writeRegisterValue().registerAddress()) return Response::empty();
                switch (_writeActionChoice.value())
                {
                    case 0:  // write
                    {
                        using Type = catta::modbus::si::RegisterType;
                        switch (this->_address.type())
                        {
                            case Type::uint16():
                                this->_value.value(catta::modbus::sunspec::ValueU16::create(request.writeRegisterValue().raw()));
                                break;
                            case Type::sint16():
                                this->_value.value(
                                    catta::modbus::sunspec::ValueS16::create(static_cast<std::int16_t>(request.writeRegisterValue().raw())));
                                break;
                            case Type::connectedPhase():
                                this->_value.value(
                                    catta::modbus::sunspec::ConnectedPhase(static_cast<std::uint8_t>(request.writeRegisterValue().raw())));
                                break;
                            default:
                                break;
                        }
                        return Response::writeRegister(request.writeRegisterValue().registerAddress());
                    }
                    case 1:  // nothing
                        return Response::empty();
                    default:  // execption1…4
                    {
                        const auto value =
                            catta::modbus::si::response::ExceptionValue(static_cast<std::uint8_t>(this->_writeActionChoice.value() - 2));
                        const auto function = request.type();
                        const auto exception = catta::modbus::si::response::Exception::create(value, function);
                        return Response::exception(exception);
                    }
                }

            default:
                return Response::empty();
        }
    }

  private:
    Fl_Choice _writeActionChoice;
    std::array<char, 6> _addressString;
    Fl_Box _addressBox;
    Fl_Box _typeBox;
    Fl_Box _nameBox;
    Fl_Choice _readActionChoice;
    catta::gui::Input _value;
    catta::modbus::si::RegisterAddress _address;

    static constexpr std::array<char, 6> createAddressString(std::uint16_t n)
    {
        const auto d = [n](const std::uint16_t f) { return static_cast<char>('0' + (n / f) % 10); };
        return std::array<char, 6>{d(10000), d(1000), d(100), d(10), d(1), '\0'};
    }
    static void readcb(Fl_Widget*, void* object)
    {
        SiRegister* siRegister = static_cast<SiRegister*>(object);
        if (siRegister)
        {
            if (siRegister->_readActionChoice.value() == 0)
                siRegister->_value.activate();
            else
                siRegister->_value.deactivate();
        }
    }
};
}  // namespace gui
}  // namespace catta
