#pragma once

// catta
#include <catta/state/ActiveCloseErrorState.hpp>

// tostring
#include <catta/tostring/toString.hpp>

// std
#include <algorithm>

namespace catta
{
namespace tostring
{
template <class ERROR_TYPE>
class GetName<catta::state::ActiveCloseErrorState<ERROR_TYPE>>
{
  private:
    static constexpr std::size_t length = 37 + GetName<ERROR_TYPE>::name.size();
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
        string("catta::state::ActiveCloseErrorState<");
        string(GetName<ERROR_TYPE>::name.data());
        character('>');
        return r;
    }();

  public:
    static constexpr std::string_view name = raw.data();
};

template <class ERROR_TYPE>
class Serializer<catta::state::ActiveCloseErrorState<ERROR_TYPE>>
{
  public:
    using Error = catta::state::DefaultError;
    using Input = catta::state::ActiveCloseErrorState<ERROR_TYPE>;
    using Output = char;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        typedef std::tuple<Error, catta::parser::InputHandled> Tuple;
        const auto error = [this]()
        {
            _data = '\0';
            _state = FAILED;
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };

        const auto done = [this]()
        {
            _data = '\0';
            _state = DONE;
            return Tuple{Error::empty(), catta::parser::InputHandled::yes()};
        };
        const auto stay = []() { return Tuple{Error::empty(), catta::parser::InputHandled::no()}; };
        const auto jump = [this, stay](const std::uint8_t state)
        {
            _state = state;
            return stay();
        };
        const auto handle = [done, jump, this, input]()
        {
            [[maybe_unused]] const auto ignore = _serializer.read(input.errorValue());
            const char data = _serializer.data();
            _data = data;
            return data != '\0' ? jump(ERROR) : done();
        };
        const auto character = [jump, this](const char c, std::uint8_t state)
        {
            _data = c;
            return jump(state);
        };

        switch (_state)
        {
            case START + 0:
                return input.isError()    ? handle()
                       : input.isActive() ? character('A', ACTIVE + 0)
                       : input.isClosed() ? character('C', CLOSED + 0)
                                          : character('E', EMPTY + 0);
            case ERROR + 0:
                return handle();
            case ACTIVE + 0:
                return character('C', ACTIVE + 1);
            case ACTIVE + 1:
                return character('T', ACTIVE + 2);
            case ACTIVE + 2:
                return character('I', ACTIVE + 3);
            case ACTIVE + 3:
                return character('V', ACTIVE + 4);
            case ACTIVE + 4:
                return character('E', TAIL + 0);
            case CLOSED + 0:
                return character('L', CLOSED + 1);
            case CLOSED + 1:
                return character('O', CLOSED + 2);
            case CLOSED + 2:
                return character('S', CLOSED + 3);
            case CLOSED + 3:
                return character('E', CLOSED + 4);
            case CLOSED + 4:
                return character('D', TAIL + 0);
            case EMPTY + 0:
                return character('M', EMPTY + 1);
            case EMPTY + 1:
                return character('P', EMPTY + 2);
            case EMPTY + 2:
                return character('T', EMPTY + 3);
            case EMPTY + 3:
                return character('Y', TAIL + 0);
            case TAIL + 0:
                return done();
            default:
                return error();
        }
    }
    [[nodiscard]] constexpr Serializer() : _state(START), _data('\0') {}
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept
    {
        if (_state == 0) return catta::parser::State::start();
        if (_state < DONE) return catta::parser::State::running();
        if (_state == DONE) return catta::parser::State::done();
        return catta::parser::State::failed();
    }

  private:
    std::uint8_t _state;
    char _data;
    Serializer<ERROR_TYPE> _serializer;
    static constexpr std::uint8_t START = 0;
    static constexpr std::uint8_t ERROR = START + 1;
    static constexpr std::uint8_t ACTIVE = ERROR + 1;
    static constexpr std::uint8_t CLOSED = ACTIVE + 5;
    static constexpr std::uint8_t EMPTY = CLOSED + 5;
    static constexpr std::uint8_t TAIL = EMPTY + 4;
    static constexpr std::uint8_t DONE = TAIL + 1;
    static constexpr std::uint8_t FAILED = DONE + 1;
};

}  // namespace tostring
}  // namespace catta
