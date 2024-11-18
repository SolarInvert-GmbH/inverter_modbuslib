#pragma once

// json
#include <catta/json/Serializer.hpp>

// parser
#include <catta/parser/Utf8Serializer.hpp>

// tojson
#include <catta/tojson/toJson.hpp>

namespace catta
{
namespace tostring
{
namespace json
{
template <catta::tojson::Serializable T>
class ToString
{
  public:
    using Output = char;
    using Input = T;
    using Error = catta::state::DefaultError;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        const auto error = []() { return Tuple{Error::error(), catta::parser::InputHandled::yes()}; };
        const auto done = [this]()
        {
            _data = '\0';
            return Tuple{Error(), catta::parser::InputHandled::yes()};
        };
        const auto value = [this](const char c)
        {
            _data = c;
            return Tuple{Error(), catta::parser::InputHandled::no()};
        };

        const auto handleChar32 = [this, error, value]()
        {
            const auto [token, handled] = _utf8Serializer.read(_unicode);
            if (handled) _unicode = '\0';
            return token.type().isValue() ? value(static_cast<char>(token.characterValue())) : error();
        };
        const auto handleJson = [this, error, handleChar32]()
        {
            if (_unicode == '\0')
            {
                const auto [token, handled] = _jsonSerializer.read(_jsonToken);
                if (handled) _jsonToken = catta::json::Token::empty();
                if (token.type().isValue())
                    _unicode = token.characterValue();
                else
                    return error();
            }
            return handleChar32();
        };

        const auto handleT = [this, input, error, done, handleJson]()
        {
            if (_jsonToken.isEmpty())
            {
                [[maybe_unused]] auto ignore = _tSerializer.read(input);
                if (_tSerializer.state().isFailed()) return error();
                if (_tSerializer.state().isDone()) return done();
                _jsonToken = _tSerializer.data();
            }
            return handleJson();
        };

        return handleT();
    }
    [[nodiscard]] constexpr Output data() const noexcept { return _data; }
    [[nodiscard]] constexpr ToString() noexcept : _data('\0'), _jsonToken(catta::json::Token::empty()), _unicode('\0') {}
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _tSerializer.state(); }

  private:
    catta::tojson::Serializer<T> _tSerializer;
    catta::parser::Utf8Serializer _utf8Serializer;
    catta::json::Serializer _jsonSerializer;

    char _data;
    catta::json::Token _jsonToken;
    char32_t _unicode;

    static constexpr std::uint8_t STATE_START = 0;
    static constexpr std::uint8_t STATE_READY = STATE_START + 1;
    static constexpr std::uint8_t STATE_NULL = STATE_READY + 1;
    static constexpr std::uint8_t STATE_TRUE = STATE_NULL + 3;
    static constexpr std::uint8_t STATE_FALSE = STATE_TRUE + 3;
    static constexpr std::uint8_t STATE_INTEGER = STATE_TRUE + 3;
};
}  // namespace json
}  // namespace tostring
}  // namespace catta
