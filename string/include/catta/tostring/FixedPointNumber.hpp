#pragma once

// catta
#include <catta/FixedPointNumber.hpp>

// tostring
#include <catta/tostring/Decimal.hpp>

namespace catta
{
namespace tostring
{

template <std::uint8_t DECIMAL_PLACES>
class Serializer<catta::FixedPointNumber<DECIMAL_PLACES>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::FixedPointNumber<DECIMAL_PLACES>;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = [this]()
        {
            _state = ERROR_STATE;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const Tuple result = Tuple{Error::empty(), catta::parser::InputHandled::no()};
        const auto stay = [result]() { return result; };
        const auto jump = [stay, this](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto tail = [this]()
        {
            _state = DONE;
            _data = '\0';
            return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
        };
        const auto character = [this, jump](const char c, const std::uint8_t state)
        {
            _data = c;
            return jump(state);
        };
        const auto runing = [this, jump, tail, character]()
        {
            const auto number = catta::Decimal<std::int64_t>(static_cast<std::int64_t>(_top));
            [[maybe_unused]] const auto ignore = _serializer.read(number);
            _data = _serializer.data();
            return _data != '\0' ? jump(TOP) : _bottom == 0 ? tail() : character('.', BOTTOM);
        };

        const auto bottom = [this, stay, jump]()
        {
            _factor /= 10;
            _data = static_cast<char>('0' + (_bottom / _factor) % 10);
            return _factor > 1 ? stay() : jump(TAIL);
        };
        const auto start = [this, input, character, runing]()
        {
            const int64_t i = static_cast<int64_t>(input);
            _factor = FACTOR;
            if (i < 0)
            {
                _top = (-i) / FACTOR;
                _bottom = (-i) % FACTOR;
                return character('-', TOP);
            }
            else
            {
                _top = i / FACTOR;
                _bottom = i % FACTOR;
                return runing();
            }
        };
        switch (_state)
        {
            case START:
                return start();
            case TOP:
                return runing();
            case BOTTOM:
                return bottom();
            case TAIL:
                return tail();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _data('\0'), _serializer{}, _top(0), _bottom(0), _factor(0), _state(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START:
                return catta::parser::State::start();
            case TOP:
            case BOTTOM:
            case TAIL:
                return catta::parser::State::running();
            case DONE:
                return catta::parser::State::done();
            default:
                return catta::parser::State::failed();
        }
    }

  private:
    char _data;
    Serializer<catta::Decimal<int64_t>> _serializer;
    int64_t _top;
    int64_t _bottom;
    int64_t _factor;
    std::uint8_t _state;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t TOP = 1;
    static constexpr std::uint8_t BOTTOM = 2;
    static constexpr std::uint8_t TAIL = 3;
    static constexpr std::uint8_t DONE = 4;
    static constexpr std::uint8_t ERROR_STATE = 5;
    static constexpr std::int64_t FACTOR = []()
    {
        std::int64_t n = 1;
        for (std::uint8_t i = 0; i < DECIMAL_PLACES; i++) n *= 10;
        return n;
    }();
};

template <std::uint8_t DECIMAL_PLACES>
class GetName<catta::FixedPointNumber<DECIMAL_PLACES>>
{
  private:
    using D = catta::Decimal<std::uint8_t>;
    constexpr static D d = catta::Decimal<std::uint8_t>(DECIMAL_PLACES);
    constexpr static std::size_t numberLength = catta::tostring::getLength<D>(d);
    constexpr static std::array<char, numberLength + 1> numberName = catta::tostring::toStaticString<D, numberLength>(d);
    constexpr static std::size_t length = 25 + numberLength;
    constexpr static std::array<char, length + 1> raw = []()
    {
        std::array<char, length + 1> r = {};
        std::size_t i = 0;
        const auto character = [&r, &i](const char c)
        {
            r[i] = c;
            i++;
        };
        const auto string = [character](const char* s)
        {
            for (const char* p = s; *p != '\0'; p++) character(*p);
        };
        string("catta::FixedPointNumber<");
        string(numberName.data());
        string(">");
        return r;
    }();

  public:
    static constexpr std::string_view name = raw.data();
};

}  // namespace tostring
}  // namespace catta
