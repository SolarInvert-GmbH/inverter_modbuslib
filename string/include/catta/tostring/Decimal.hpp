#pragma once

// catta
#include <catta/ConstString.hpp>
#include <catta/Decimal.hpp>

// tostring
#include <catta/tostring/toString.hpp>

namespace catta
{
namespace tostring
{

template <std::integral I>
class Serializer<Decimal<I>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = Decimal<I>;
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
        const auto neagtiv = [this, input, result]()
        {
            _data = '-';
            _tmp = input.getMaxPowerOfTen();
            _state = RUNNING;
            return result;
        };
        const auto zero = [this, result]()
        {
            _data = '0';
            _state = TAIL;
            return result;
        };
        const auto runing = [this, input, result]()
        {
            const U i = static_cast<U>(I(input) < 0 ? -I(input) : I(input));
            _data = static_cast<char>('0' + (i / _tmp) % 10);
            _tmp = static_cast<U>(_tmp / 10);
            _state = _tmp == 0 ? TAIL : RUNNING;
            return result;
        };
        const auto positive = [this, input, runing]()
        {
            _tmp = input.getMaxPowerOfTen();
            return runing();
        };
        const auto tail = [this]()
        {
            _state = DONE;
            _data = '\0';
            return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
        };
        switch (_state)
        {
            case START:
                return I(input) < 0 ? neagtiv() : I(input) == 0 ? zero() : positive();
            case RUNNING:
                return runing();
            case TAIL:
                return tail();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() noexcept : _data('\0'), _tmp(0), _state(0) {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        switch (_state)
        {
            case START:
                return catta::parser::State::start();
            case RUNNING:
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
    using U = catta::Unsigned<I>::type;
    U _tmp;
    std::uint8_t _state;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t RUNNING = 1;
    static constexpr std::uint8_t TAIL = 2;
    static constexpr std::uint8_t DONE = 3;
    static constexpr std::uint8_t ERROR_STATE = 4;
};

template <std::integral I>
class GetName<catta::Decimal<I>>
{
  private:
    using D = catta::Decimal<std::uint8_t>;
    constexpr static D d = D(sizeof(I) * 8);
    constexpr static std::size_t numberLength = catta::tostring::getLength<D>(d);
    constexpr static std::array<char, numberLength + 1> numberName = catta::tostring::toStaticString<D, numberLength>(d);
    constexpr static std::size_t unsingedSize = std::is_unsigned<I>::value ? 1 : 0;
    constexpr static std::size_t length = 21 + numberLength + unsingedSize;
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
        string("catta::Decimal<");
        if (std::is_unsigned<I>::value) character('u');
        string("int");
        string(numberName.data());
        string("_t>");
        return r;
    }();

  public:
    static constexpr std::string_view name = raw.data();
};

}  // namespace tostring
}  // namespace catta
