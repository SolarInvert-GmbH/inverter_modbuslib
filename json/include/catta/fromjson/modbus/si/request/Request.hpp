#pragma once

// request
#include <catta/modbus/si/request/Request.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/ReadRegister.hpp>
#include <catta/fromjson/modbus/si/WriteRegister.hpp>
#include <catta/fromjson/modbus/si/request/ConstantVoltage.hpp>
#include <catta/fromjson/modbus/si/request/ControlBatteryInvert.hpp>
#include <catta/fromjson/modbus/si/request/LimitBatteryInvert.hpp>
#include <catta/fromjson/modbus/si/request/PowerFactor.hpp>
#include <catta/fromjson/modbus/si/request/Type.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::request::Request>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::request::Request;
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
        const auto isInEndState = [](auto parser)
        {
            [[maybe_unused]] auto ignore = parser.read(catta::json::Token::end());
            return parser.state().isDone();
        };
        const auto handle = [stay, jump, error, input, isInEndState](auto& parser)
        {
            const auto close = catta::json::Token::closeCurlyBracket();
            const auto again = catta::json::Token::comma();
            const auto token = (input == close || input == again) && isInEndState(parser) ? catta::json::Token::end() : input;
            [[maybe_unused]] auto ignore = parser.read(token);
            if (parser.state().isFailed()) return error();
            if (parser.state().isDone()) return jump(input == close ? TAIL + 0 : HUB + 0);
            return stay();
        };
        const auto valueSet = [this, input, jump, error]()
        {
            _valueSet = true;
            switch (input.type())
            {
                case catta::json::TokenType::closeCurlyBracket():
                    return jump(TAIL + 0);
                case catta::json::TokenType::comma():
                    return jump(HUB + 0);
                default:
                    return error();
            }
        };
        const auto handleSplitt = [this, isInEndState, input, valueSet, jump, error]()
        {
            bool possible = false;
            bool done = false;
            const auto h = [&possible, &done, isInEndState, input](auto& parser)
            {
                if (parser.state().isFailed()) return;
                const auto close = catta::json::Token::closeCurlyBracket();
                const auto again = catta::json::Token::comma();
                const auto token = (input == close || input == again) && isInEndState(parser) ? catta::json::Token::end() : input;
                [[maybe_unused]] auto ignore = parser.read(token);
                if (!parser.state().isFailed()) possible = true;
                if (parser.state().isDone()) done = true;
            };
            h(_powerFactorParser);
            h(_limitBatteryInvertParser);
            h(_constantVoltageParser);
            h(_controlBatteryInvertParser);
            h(_writeRegisterParser);
            h(_readRegisterParser);
            if (done) return valueSet();
            return possible ? jump(HUB + 15) : error();
        };
        switch (_state)
        {
            case START + 0:
                return input == catta::json::Token::openCurlyBracket() ? next() : error();
            case HUB + 0:
                return input == catta::json::Token::openString() ? next() : error();
            case HUB + 1:
                return input == catta::json::Token::character('t')   ? jump(HUB + 2)
                       : input == catta::json::Token::character('v') ? jump(HUB + 8)
                                                                     : error();
            case HUB + 2:
                return input == catta::json::Token::character('y') ? jump(HUB + 3) : error();
            case HUB + 3:
                return input == catta::json::Token::character('p') ? jump(HUB + 4) : error();
            case HUB + 4:
                return input == catta::json::Token::character('e') ? jump(HUB + 5) : error();
            case HUB + 5:
                return input == catta::json::Token::closeString() ? jump(HUB + 6) : error();
            case HUB + 6:
                return !_typeParser.state().isStart() ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 7:
                return handle(_typeParser);
            case HUB + 8:
                return input == catta::json::Token::character('a') ? jump(HUB + 9) : error();
            case HUB + 9:
                return input == catta::json::Token::character('l') ? jump(HUB + 10) : error();
            case HUB + 10:
                return input == catta::json::Token::character('u') ? jump(HUB + 11) : error();
            case HUB + 11:
                return input == catta::json::Token::character('e') ? jump(HUB + 12) : error();
            case HUB + 12:
                return input == catta::json::Token::closeString() ? jump(HUB + 13) : error();
            case HUB + 13:
                return _valueSet ? error() : input == catta::json::Token::colon() ? next() : error();
            case HUB + 14:
                return input == catta::json::Token::nullObject() ? jump(HUB + 16) : handleSplitt();
            case HUB + 15:
                return handleSplitt();
            case HUB + 16:
                return valueSet();
            case TAIL + 0:
                return input == catta::json::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START), _valueSet(false) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        if (_state != DONE || !_valueSet) return Output::empty();
        using Type = catta::modbus::si::request::Type;
        switch (_typeParser.data())
        {
            case Type::readRegister():
                return catta::modbus::si::request::Request::readRegister(_readRegisterParser.data());
            case Type::writeRegister():
                return catta::modbus::si::request::Request::writeRegister(_writeRegisterParser.data());
            case Type::factoryValues():
                return catta::modbus::si::request::Request::factoryValues();
            case Type::readOperatingData33():
                return catta::modbus::si::request::Request::readOperatingData33();
            case Type::readOperatingData3e():
                return catta::modbus::si::request::Request::readOperatingData3e();
            case Type::switchOffGridRelay():
                return catta::modbus::si::request::Request::switchOffGridRelay();
            case Type::switchOnGridRelay():
                return catta::modbus::si::request::Request::switchOnGridRelay();
            case Type::forceIdle():
                return catta::modbus::si::request::Request::forceIdle();
            case Type::deactivateIdle():
                return catta::modbus::si::request::Request::deactivateIdle();
            case Type::startConstantVoltage():
                return catta::modbus::si::request::Request::startConstantVoltage(_constantVoltageParser.data());
            case Type::endConstantVoltage():
                return catta::modbus::si::request::Request::endConstantVoltage();
            case Type::setPowerFactor():
                return catta::modbus::si::request::Request::setPowerFactor(_powerFactorParser.data());
            case Type::controlBatteryInvert():
                return catta::modbus::si::request::Request::controlBatteryInvert(_controlBatteryInvertParser.data());
            case Type::limitBatteryInvert():
                return catta::modbus::si::request::Request::limitBatteryInvert(_limitBatteryInvertParser.data());
            case Type::readError():
                return catta::modbus::si::request::Request::readError();
            default:
                return catta::modbus::si::request::Request::empty();
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
    bool _valueSet;
    Parser<catta::modbus::si::request::Type> _typeParser;
    Parser<catta::modbus::si::request::PowerFactor> _powerFactorParser;
    Parser<catta::modbus::si::request::LimitBatteryInvert> _limitBatteryInvertParser;
    Parser<catta::modbus::si::request::ConstantVoltage> _constantVoltageParser;
    Parser<catta::modbus::si::request::ControlBatteryInvert> _controlBatteryInvertParser;
    Parser<catta::modbus::si::WriteRegister> _writeRegisterParser;
    Parser<catta::modbus::si::ReadRegister> _readRegisterParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 17;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR_STATE = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
