#pragma once

// catta
#include <catta/parser/DefaultToken.hpp>
#include <catta/parser/SequenceParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

namespace catta
{
namespace parser
{
/**
 * @brief Parses utf8 char8_t to unicode char32_t. Implements catta::parser::SequenceParserConcept.
 * @see catta::parser::Utf8Serializer
 *
 * @author CattaTech - Maik Urbannek
 */
class Utf8Parser
{
  public:
    /**
     * Output Token type. char32_t
     */
    typedef catta::parser::DefaultToken<char32_t, catta::state::DefaultError> Token;
    /**
     * Input type. char8_t
     */
    typedef char8_t Input;
    /**
     * @param[in] input Utf8 character.
     * @return Returns output token. Input wil always be handled.
     */
    [[nodiscard]] constexpr std::tuple<Token, catta::parser::InputHandled> read(const Input input) noexcept
    {
        typedef catta::parser::InputHandled Handled;
        typedef std::tuple<Token, Handled> Tuple;
        const auto next = [this](const std::uint32_t data, const std::uint8_t state, const Token& token)
        {
            _state = state;
            _data = data;
            return Tuple{token, Handled::yes()};
        };
        const auto code = [](const char8_t i, const std::uint8_t ones, const std::uint8_t shift)
        { return char32_t(static_cast<std::uint8_t>(std::uint8_t((1 << (ones + 1)) - 1) & i) << shift); };
        const auto end = [this]()
        {
            _state = STATE_END;
            return Tuple{Token::end(), Handled::yes()};
        };
        const auto error = [this]()
        {
            _state = STATE_ERROR;
            return Tuple{Token::error(catta::state::DefaultError::error()), Handled::yes()};
        };
        switch (_state)
        {
            case STATE_START:
            case STATE_BASE:
                if (input == '\0') return end();
                if (isMasktype0(input)) return next(0, STATE_BASE, Token::character(char32_t(input)));
                if (isMasktype2(input)) return next(code(input, 5, 6), STATE_1_0, Token::empty());
                if (isMasktype3(input)) return next(code(input, 4, 12), STATE_2_0, Token::empty());
                if (isMasktype4(input)) return next(code(input, 3, 18), STATE_3_0, Token::empty());
                return error();
            case STATE_1_0:
            case STATE_2_1:
            case STATE_3_2:
                if (isMasktype1(input)) return next(0, STATE_BASE, Token::character(code(input, 6, 0) | _data));
                return error();
            case STATE_2_0:
            case STATE_3_1:
                if (isMasktype1(input)) return next(code(input, 6, 6) | _data, _state + 1, Token::empty());
                return error();
            case STATE_3_0:
                if (isMasktype1(input)) return next(code(input, 6, 12) | _data, _state + 1, Token::empty());
                return error();
            default:
                return error();
        }
    }
    /**
     * @return Returns the state of the parser.
     */
    [[nodiscard]] constexpr State state() const noexcept
    {
        switch (_state)
        {
            case STATE_START:
                return State::start();
            case STATE_BASE:
            case STATE_1_0:
            case STATE_2_0:
            case STATE_2_1:
            case STATE_3_0:
            case STATE_3_1:
            case STATE_3_2:
                return State::running();
            case STATE_END:
                return State::done();
            default:
                return State::failed();
        }
    }
    /**
     * Default constructor.
     */
    constexpr Utf8Parser() noexcept : _data(0), _state(STATE_START) {}

  private:
    std::uint32_t _data;
    std::uint8_t _state;
    static constexpr std::uint8_t STATE_START = 0;
    static constexpr std::uint8_t STATE_BASE = 1;
    static constexpr std::uint8_t STATE_1_0 = 2;
    static constexpr std::uint8_t STATE_2_0 = 3;
    static constexpr std::uint8_t STATE_2_1 = 4;
    static constexpr std::uint8_t STATE_3_0 = 5;
    static constexpr std::uint8_t STATE_3_1 = 6;
    static constexpr std::uint8_t STATE_3_2 = 7;
    static constexpr std::uint8_t STATE_END = 8;
    static constexpr std::uint8_t STATE_ERROR = 9;
    constexpr static bool isMasktype0(const char8_t c) { return std::uint8_t(0x80 & std::uint8_t(c)) == 0x00; }
    constexpr static bool isMasktype1(const char8_t c) { return std::uint8_t(0xc0 & std::uint8_t(c)) == 0x80; }
    constexpr static bool isMasktype2(const char8_t c) { return std::uint8_t(0xe0 & std::uint8_t(c)) == 0xc0; }
    constexpr static bool isMasktype3(const char8_t c) { return std::uint8_t(0xf0 & std::uint8_t(c)) == 0xe0; }
    constexpr static bool isMasktype4(const char8_t c) { return std::uint8_t(0xf8 & std::uint8_t(c)) == 0xf0; }
};
}  // namespace parser
}  // namespace catta
