#pragma once

// json
#include <catta/json/Parser.hpp>

// parser
#include <catta/parser/Utf8Parser.hpp>

// fromjson
#include <catta/fromjson/fromJson.hpp>

namespace catta
{
namespace fromstring
{
namespace json
{
template <catta::fromjson::Parsable T>
class FromString
{
  public:
    using Output = T;
    using Input = char;
    using Error = catta::state::DefaultError;
    [[nodiscard]] constexpr std::tuple<Error, catta::parser::InputHandled> read(const Input& input) noexcept
    {
        using Tuple = std::tuple<Error, catta::parser::InputHandled>;
        catta::parser::InputHandled globalHandled = catta::parser::InputHandled::no();
        const auto error = [this]()
        {
            _state = catta::parser::State::failed();
            return Tuple{Error::error(), catta::parser::InputHandled::yes()};
        };
        const auto result = [this, &globalHandled](const catta::parser::State state)
        {
            _state = state;
            return Tuple{Error(), globalHandled};
        };
        const auto done = [result]() { return result(catta::parser::State::done()); };
        const auto running = [result]() { return result(catta::parser::State::running()); };

        const auto handleJson = [this, error, done, running]()
        {
            auto [e, handled] = _tParser.read(_jsonToken);
            if (handled) _jsonToken = catta::json::Token::empty();
            if (_tParser.state().isFailed()) return error();
            if (_tParser.state().isDone()) return done();
            return running();
        };

        const auto handleChar32 = [this, handleJson, running]()
        {
            if (_jsonToken.isEmpty())
            {
                const auto [token, handled] = _jsonParser.read(_c32Token);
                if (handled) _c32Token = 0xffffffff;
                _jsonToken = token;
            }
            if (!_jsonToken.isEmpty()) return handleJson();
            return running();
        };

        const auto handleChar = [this, input, handleChar32, error, running, &globalHandled]()
        {
            if (_c32Token == 0xffffffff)
            {
                const auto [token, handled] = _utf8Parser.read(static_cast<char8_t>(input));

                if (handled) globalHandled = catta::parser::InputHandled::yes();
                using Type = catta::parser::DefaultTokenType;
                switch (token.type())
                {
                    case Type::value():
                        _c32Token = token.characterValue();
                        break;
                    case Type::end():
                        _c32Token = '\0';
                        break;
                    case Type::error():
                        return error();
                    default:
                        return running();
                }
            }
            return handleChar32();
        };

        return handleChar();
    }
    [[nodiscard]] constexpr Output data() const noexcept { return _tParser.data(); }
    [[nodiscard]] constexpr FromString() noexcept
        : _state(catta::parser::State::start()), _jsonToken(catta::json::Token::empty()), _c32Token(0xffffffff)
    {
    }
    [[nodiscard]] constexpr catta::parser::State state() const noexcept { return _state; }

  private:
    catta::fromjson::Parser<T> _tParser;
    catta::parser::Utf8Parser _utf8Parser;
    catta::json::Parser _jsonParser;

    catta::parser::State _state;
    catta::json::Token _jsonToken;
    char32_t _c32Token;
};
}  // namespace json
}  // namespace fromstring
}  // namespace catta
