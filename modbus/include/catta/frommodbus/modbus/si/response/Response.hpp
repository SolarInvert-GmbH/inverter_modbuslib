#pragma once

// request
#include <catta/modbus/si/response/Response.hpp>

// frommodbus
#include <catta/frommodbus/fromModbus.hpp>
#include <catta/frommodbus/modbus/si/WriteRegister.hpp>
#include <catta/frommodbus/modbus/si/response/FactoryValues.hpp>
#include <catta/frommodbus/modbus/si/response/ReadError.hpp>
#include <catta/frommodbus/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/frommodbus/modbus/si/response/ReadOperatingData3e.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::si::response::Response>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::si::response::Response;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error(), catta::parser::InputHandled::yes()}; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto next = [stay, this]()
        {
            _state++;
            return stay();
        };
        const auto function = [input, error, this, jump]()
        {
            _function = input.value();
            if (input.type().isException()) return jump(EXCEPTION + 0);
            if (!input.type().isFunction()) return error();
            const auto startParserAndJump = [input, jump](auto& parser, const std::uint8_t state)
            {
                [[maybe_unused]] auto ignore0 = parser.read(Input::start());
                [[maybe_unused]] auto ignore1 = parser.read(input);
                return jump(state);
            };

            switch (_function)
            {
                case 0x03:
                    return jump(READ_REGISTER + 0);
                case 0x31:
                    return startParserAndJump(_factoryValuesParser, FACTORY_VALUES + 0);
                case 0x40:
                    return startParserAndJump(_readErrorParser, READ_ERROR + 0);
                case 0x33:
                    return startParserAndJump(_readOperatingData33Parser, READ_OPERATING_DATA_33 + 0);
                case 0x3e:
                    return startParserAndJump(_readOperatingData3eParser, READ_OPERATING_DATA_3E + 0);
                case 0x10:
                    return startParserAndJump(_writeRegisterParser, WRITE_REGISTER + 0);
                case 0x34:
                case 0x35:
                case 0x36:
                case 0x37:
                case 0x38:
                case 0x39:
                case 0x3b:
                case 0x3f:
                case 0x44:
                    return jump(SUCCESS + 0);
                default:
                    return error();
            }
        };

        const auto handle = [stay, jump, error, input](auto& parser)
        {
            [[maybe_unused]] auto ignore = parser.read(input);
            if (parser.state().isFailed()) return error();
            if (parser.state().isDone()) return jump(DONE + 0);
            return stay();
        };
        const auto getCount = [this, input, error, jump](const std::uint8_t state)
        {
            const std::uint8_t v = input.value();
            if (!input.type().isData() || (v != 2 && v != 4 && v != 8 && v != 32)) return error();
            _count = v;
            return jump(state);
        };
        const auto getCode = [this, input, error, jump](const std::uint8_t state)
        {
            const std::uint8_t v = input.value();
            if (!input.type().isData() || (v != 1 && v != 2 && v != 3 && v != 4)) return error();
            _count = v - 1;
            return jump(state);
        };
        const auto getSuccess = [this, input, error, jump](const std::uint8_t state)
        {
            const std::uint8_t v = input.value();
            if (!input.type().isData() || (v != 0 && v != 1)) return error();
            _data[0] = v;
            return jump(state);
        };
        const auto high = [input, error, jump, this]()
        {
            if (!input.type().isData()) return error();
            _data[_index] = static_cast<std::uint16_t>(input.value() << 8);
            return jump(READ_REGISTER + 2);
        };
        const auto low = [input, error, jump, this]()
        {
            if (!input.type().isData()) return error();
            _data[_index] = static_cast<std::uint16_t>(_data[_index] | input.value());
            _index++;
            return _index >= _count / 2 ? jump(TAIL + 0) : jump(READ_REGISTER + 1);
        };
        switch (_state)
        {
            case START + 0:
                return input.type().isStart() ? next() : error();
            case START + 1:
                return function();
            case WRITE_REGISTER + 0:
                return handle(_writeRegisterParser);
            case FACTORY_VALUES:
                return handle(_factoryValuesParser);
            case READ_ERROR:
                return handle(_readErrorParser);
            case READ_OPERATING_DATA_33:
                return handle(_readOperatingData33Parser);
            case READ_OPERATING_DATA_3E:
                return handle(_readOperatingData3eParser);
            case READ_REGISTER + 0:
                return getCount(READ_REGISTER + 1);
            case READ_REGISTER + 1:
                return high();
            case READ_REGISTER + 2:
                return low();
            case SUCCESS + 0:
                return input == Input::data(0x01) ? next() : error();
            case SUCCESS + 1:
                return input == Input::data(0x00) || input == Input::data(0x01) ? getSuccess(TAIL + 0) : error();
            case EXCEPTION + 0:
                return input == catta::modbus::Token::data(0x01) ? jump(EXCEPTION + 1) : error();
            case EXCEPTION + 1:
                return getCode(TAIL + 0);
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _function(0), _count(0), _index(0) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        const auto v32 = [this]() { return (static_cast<std::uint32_t>(_data[0]) << 16) | _data[1]; };
        const auto v64 = [this]()
        {
            return (static_cast<std::uint64_t>(_data[0]) << 48) | (static_cast<std::uint64_t>(_data[1]) << 32) |
                   (static_cast<std::uint64_t>(_data[2]) << 16) | _data[3];
        };
        const auto string = [this]()
        {
            catta::modbus::sunspec::String::Raw r = {};
            for (std::size_t i = 0; i < catta::modbus::sunspec::String::size / 2; i++)
            {
                r[i * 2 + 0] = static_cast<char>(_data[i] >> 8);
                r[i * 2 + 1] = static_cast<char>(_data[i] >> 0);
            }
            return catta::modbus::sunspec::String::create(r.data());
        };
        if (_state != DONE) return Output::empty();
        switch (_function)
        {
            case 0x03:
                switch (_count)
                {
                    case 2:
                        return Output::value16(_data[0]);
                    case 4:
                        return Output::value32(v32());
                    case 8:
                        return Output::value64(v64());
                    case 32:
                        return Output::string(string());
                    default:
                        return Output::empty();
                }
            case 0x10:
                return Output::writeRegister(_writeRegisterParser.data());
            case 0x31:
                return Output::factoryValues(_factoryValuesParser.data());
            case 0x33:
                return Output::readOperatingData33(_readOperatingData33Parser.data());
            case 0x34:
                return Output::switchOffGridRelay(_data[0]);
            case 0x35:
                return Output::switchOnGridRelay(_data[0]);
            case 0x36:
                return Output::forceIdle(_data[0]);
            case 0x37:
                return Output::deactivateIdle(_data[0]);
            case 0x38:
                return Output::startConstantVoltage(_data[0]);
            case 0x39:
                return Output::endConstantVoltage(_data[0]);
            case 0x3b:
                return Output::setPowerFactor(_data[0]);
            case 0x3e:
                return Output::readOperatingData3e(_readOperatingData3eParser.data());
            case 0x3f:
                return Output::controlBatteryInvert(_data[0]);
            case 0x40:
                return Output::readError(_readErrorParser.data());
            case 0x44:
                return Output::limitBatteryInvert(_data[0]);
            default:
                return _function & 0x80
                           ? Output::exception(catta::modbus::si::response::Exception::create(
                                 catta::modbus::si::response::ExceptionValue(_count), catta::modbus::si::request::Type::fromModbus(0x7f & _function)))
                           : Output::empty();
        }
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == START) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    std::uint8_t _function;
    std::uint8_t _count;
    std::uint8_t _index;
    std::array<std::uint16_t, 16> _data;
    Parser<catta::modbus::si::response::FactoryValues> _factoryValuesParser;
    Parser<catta::modbus::si::response::ReadError> _readErrorParser;
    Parser<catta::modbus::si::response::ReadOperatingData33> _readOperatingData33Parser;
    Parser<catta::modbus::si::response::ReadOperatingData3e> _readOperatingData3eParser;
    Parser<catta::modbus::si::WriteRegister> _writeRegisterParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t FACTORY_VALUES = START + 2;
    static constexpr std::uint8_t READ_ERROR = FACTORY_VALUES + 1;
    static constexpr std::uint8_t READ_OPERATING_DATA_33 = READ_ERROR + 1;
    static constexpr std::uint8_t READ_OPERATING_DATA_3E = READ_OPERATING_DATA_33 + 1;
    static constexpr std::uint8_t WRITE_REGISTER = READ_OPERATING_DATA_3E + 1;
    static constexpr std::uint8_t READ_REGISTER = WRITE_REGISTER + 1;
    static constexpr std::uint8_t SUCCESS = READ_REGISTER + 3;
    static constexpr std::uint8_t EXCEPTION = SUCCESS + 2;
    static constexpr std::uint8_t TAIL = EXCEPTION + 2;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
