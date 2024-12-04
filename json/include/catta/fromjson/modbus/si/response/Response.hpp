#pragma once

// request
#include <catta/modbus/si/response/Response.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>
#include <catta/fromjson/modbus/si/WriteRegister.hpp>
#include <catta/fromjson/modbus/si/response/Exception.hpp>
#include <catta/fromjson/modbus/si/response/FactoryValues.hpp>
#include <catta/fromjson/modbus/si/response/ReadError.hpp>
#include <catta/fromjson/modbus/si/response/ReadOperatingData33.hpp>
#include <catta/fromjson/modbus/si/response/ReadOperatingData3e.hpp>
#include <catta/fromjson/modbus/si/response/Type.hpp>
#include <catta/fromjson/modbus/sunspec/String.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU16.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU32.hpp>
#include <catta/fromjson/modbus/sunspec/ValueU64.hpp>

namespace catta
{
namespace fromjson
{
template <>
class Parser<catta::modbus::si::response::Response>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::json::Token;
    using Output = catta::modbus::si::response::Response;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR;
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
            h(_writeRegisterParser);
            h(_exceptionParser);
            h(_factoryValuesParser);
            h(_readErrorParser);
            h(_readOperatingData33Parser);
            h(_readOperatingData3eParser);
            h(_valueU16Parser);
            h(_valueU32Parser);
            h(_valueU64Parser);
            h(_stringParser);
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
        using Type = catta::modbus::si::response::Type;
        switch (_typeParser.data())
        {
            case Type::exception():
                return catta::modbus::si::response::Response::exception(_exceptionParser.data());
            case Type::factoryValues():
                return catta::modbus::si::response::Response::factoryValues(_factoryValuesParser.data());
            case Type::readError():
                return catta::modbus::si::response::Response::readError(_readErrorParser.data());
            case Type::readOperatingData33():
                return catta::modbus::si::response::Response::readOperatingData33(_readOperatingData33Parser.data());
            case Type::readOperatingData3e():
                return catta::modbus::si::response::Response::readOperatingData3e(_readOperatingData3eParser.data());
            case Type::switchOffInverter():
                return catta::modbus::si::response::Response::switchOffInverter();
            case Type::switchOnInverter():
                return catta::modbus::si::response::Response::switchOnInverter();
            case Type::forceIdle():
                return catta::modbus::si::response::Response::forceIdle();
            case Type::deactivateIdle():
                return catta::modbus::si::response::Response::deactivateIdle();
            case Type::startConstantVoltage():
                return catta::modbus::si::response::Response::startConstantVoltage();
            case Type::endConstantVoltage():
                return catta::modbus::si::response::Response::endConstantVoltage();
            case Type::setPowerFactor():
                return catta::modbus::si::response::Response::setPowerFactor();
            case Type::controlBatteryInvert():
                return catta::modbus::si::response::Response::controlBatteryInvert();
            case Type::limitBatteryInvert():
                return catta::modbus::si::response::Response::limitBatteryInvert();
            case Type::writeRegister():
                return catta::modbus::si::response::Response::writeRegister(_writeRegisterParser.data());
            case Type::value16():
                return catta::modbus::si::response::Response::value16(_valueU16Parser.data().value());
            case Type::value32():
                return catta::modbus::si::response::Response::value32(_valueU32Parser.data().value());
            case Type::value64():
                return catta::modbus::si::response::Response::value64(_valueU64Parser.data().value());
            case Type::string():
                return catta::modbus::si::response::Response::string(_stringParser.data());
            default:
                return catta::modbus::si::response::Response::empty();
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
    Parser<catta::modbus::si::response::Type> _typeParser;
    Parser<catta::modbus::si::response::Exception> _exceptionParser;
    Parser<catta::modbus::si::response::FactoryValues> _factoryValuesParser;
    Parser<catta::modbus::si::response::ReadError> _readErrorParser;
    Parser<catta::modbus::si::response::ReadOperatingData33> _readOperatingData33Parser;
    Parser<catta::modbus::si::response::ReadOperatingData3e> _readOperatingData3eParser;
    Parser<catta::modbus::sunspec::ValueU16> _valueU16Parser;
    Parser<catta::modbus::sunspec::ValueU32> _valueU32Parser;
    Parser<catta::modbus::sunspec::ValueU64> _valueU64Parser;
    Parser<catta::modbus::sunspec::String> _stringParser;
    Parser<catta::modbus::si::WriteRegister> _writeRegisterParser;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t HUB = START + 1;
    static constexpr std::uint8_t TAIL = HUB + 17;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace fromjson
}  // namespace catta
