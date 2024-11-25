#pragma once

// model
#include <catta/modbus/sunspec/model/Inverter.hpp>

// fromjson
#include <catta/frommodbus/fromModbus.hpp>

namespace catta
{
namespace frommodbus
{
template <>
class Parser<catta::modbus::sunspec::model::Inverter>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::modbus::Token;
    using Output = catta::modbus::sunspec::model::Inverter;
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
        const auto high = [next, input](std::uint16_t& v)
        {
            v = static_cast<std::uint16_t>(input.value() << 8);
            return next();
        };
        const auto low = [next, input](std::uint16_t& v)
        {
            v = static_cast<std::uint16_t>(v | input.value());
            return next();
        };
        const auto u32 = [next, input](std::uint32_t& v, const std::uint32_t i)
        {
            v = i == 3 ? static_cast<std::uint32_t>(input.value() << (8 * i))
                       : static_cast<std::uint32_t>(v | static_cast<std::uint32_t>(input.value() << (8 * i)));
            return next();
        };
        switch (_state)
        {
            case START + 0:
                return input.type().isStart() ? next() : error();
            case START + 1:
                return input == Input::function(0x03) ? next() : error();
            case START + 2:
                return input == Input::data(0x34) ? next() : error();
            case DATA + 0:
                return high(_a);
            case DATA + 1:
                return low(_a);
            case DATA + 2:
                return high(_aphA);
            case DATA + 3:
                return low(_aphA);
            case DATA + 4:
                return high(_aphB);
            case DATA + 5:
                return low(_aphB);
            case DATA + 6:
                return high(_aphC);
            case DATA + 7:
                return low(_aphC);
            case DATA + 8:
                return high(_aSf);
            case DATA + 9:
                return low(_aSf);
            case DATA + 10:
                return high(_phVphA);
            case DATA + 11:
                return low(_phVphA);
            case DATA + 12:
                return high(_phVphB);
            case DATA + 13:
                return low(_phVphB);
            case DATA + 14:
                return high(_phVphC);
            case DATA + 15:
                return low(_phVphC);
            case DATA + 16:
                return high(_vSf);
            case DATA + 17:
                return low(_vSf);
            case DATA + 18:
                return high(_w);
            case DATA + 19:
                return low(_w);
            case DATA + 20:
                return high(_wSf);
            case DATA + 21:
                return low(_wSf);
            case DATA + 22:
                return high(_hz);
            case DATA + 23:
                return low(_hz);
            case DATA + 24:
                return high(_hzSf);
            case DATA + 25:
                return low(_hzSf);
            case DATA + 26:
                return high(_pf);
            case DATA + 27:
                return low(_pf);
            case DATA + 28:
                return high(_pfSf);
            case DATA + 29:
                return low(_pfSf);
            case DATA + 30:
                return u32(_wh, 3);
            case DATA + 31:
                return u32(_wh, 2);
            case DATA + 32:
                return u32(_wh, 1);
            case DATA + 33:
                return u32(_wh, 0);
            case DATA + 34:
                return high(_whSf);
            case DATA + 35:
                return low(_whSf);
            case DATA + 36:
                return high(_dcv);
            case DATA + 37:
                return low(_dcv);
            case DATA + 38:
                return high(_dcvSf);
            case DATA + 39:
                return low(_dcvSf);
            case DATA + 40:
                return high(_tmp);
            case DATA + 41:
                return low(_tmp);
            case DATA + 42:
                return high(_tmpSf);
            case DATA + 43:
                return low(_tmpSf);
            case DATA + 44:
                return high(_st);
            case DATA + 45:
                return low(_st);
            case DATA + 46:
                return high(_stVnd);
            case DATA + 47:
                return low(_stVnd);
            case DATA + 48:
                return u32(_evtVnd, 3);
            case DATA + 49:
                return u32(_evtVnd, 2);
            case DATA + 50:
                return u32(_evtVnd, 1);
            case DATA + 51:
                return u32(_evtVnd, 0);
            case TAIL + 0:
                return input == catta::modbus::Token::end() ? jump(DONE + 0) : error();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Parser() noexcept : _state(START) {}
    [[nodiscard]] constexpr Output data() const noexcept
    {
        if (_state != DONE) return Output::empty();
        using VS16 = catta::modbus::sunspec::ValueS16;
        using VU16 = catta::modbus::sunspec::ValueU16;
        using VU32 = catta::modbus::sunspec::ValueU32;
        using SF = catta::modbus::sunspec::ScaleFactor;
        using SV4U16 = catta::modbus::sunspec::ScaledValue4U16;
        using SV3U16 = catta::modbus::sunspec::ScaledValue3U16;
        using SVU16 = catta::modbus::sunspec::ScaledValueU16;
        using SVS16 = catta::modbus::sunspec::ScaledValueS16;
        using SVU32 = catta::modbus::sunspec::ScaledValueU32;

        const auto vs16 = [](const std::uint16_t i) { return VS16::create(static_cast<std::int16_t>(i)); };
        const auto vu16 = [](const std::uint16_t i) { return VU16::create(i); };
        const auto vu32 = [](const std::uint32_t i) { return VU32::create(i); };
        const auto sf = [](const std::uint16_t i) { return SF::create(static_cast<std::int8_t>(i)); };

        const auto ampere = SV4U16::create(vu16(_a), vu16(_aphA), vu16(_aphB), vu16(_aphC), sf(_aSf));
        const auto voltage = SV3U16::create(vu16(_phVphA), vu16(_phVphB), vu16(_phVphC), sf(_vSf));
        const auto watt = SVS16::create(vs16(_w), sf(_wSf));
        const auto hertz = SVU16::create(vu16(_hz), sf(_hzSf));
        const auto powerFactor = SVS16::create(vs16(_pf), sf(_pfSf));
        const auto wattHours = SVU32::create(vu32(_wh), sf(_whSf));
        const auto dcVoltage = SVU16::create(vu16(_dcv), sf(_dcvSf));
        const auto cabinetTemperature = SVS16::create(vs16(_tmp), sf(_tmpSf));
        const auto operatingState = vu16(_st);
        const auto vendorOperatingState = vu16(_stVnd);
        const auto vendorEventBitfield = vu32(_evtVnd);

        return Output::create(ampere, voltage, watt, hertz, powerFactor, wattHours, dcVoltage, cabinetTemperature, operatingState,
                              vendorOperatingState, vendorEventBitfield);
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
    std::uint16_t _a;
    std::uint16_t _aphA;
    std::uint16_t _aphB;
    std::uint16_t _aphC;
    std::uint16_t _aSf;
    std::uint16_t _phVphA;
    std::uint16_t _phVphB;
    std::uint16_t _phVphC;
    std::uint16_t _vSf;
    std::uint16_t _w;
    std::uint16_t _wSf;
    std::uint16_t _hz;
    std::uint16_t _hzSf;
    std::uint16_t _pf;
    std::uint16_t _pfSf;
    std::uint32_t _wh;
    std::uint16_t _whSf;
    std::uint16_t _dcv;
    std::uint16_t _dcvSf;
    std::uint16_t _tmp;
    std::uint16_t _tmpSf;
    std::uint16_t _st;
    std::uint16_t _stVnd;
    std::uint32_t _evtVnd;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t DATA = START + 3;
    static constexpr std::uint8_t TAIL = DATA + 52;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t ERROR = DONE + 1;
};
}  // namespace frommodbus
}  // namespace catta
