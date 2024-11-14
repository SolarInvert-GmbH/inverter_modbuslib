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
 * @brief Parses unicode char32_t to utf8 char8_t. Implements catta::parser::SequenceParserConcept.
 * @see catta::parser::Utf8Parser
 *
 * @author CattaTech - Maik Urbannek
 */
class Utf8Serializer
{
  public:
    /**
     * Output Token type. char8_t
     */
    typedef catta::parser::DefaultToken<char8_t, catta::state::DefaultError> Token;
    /**
     * Input type. char32_t
     */
    typedef char32_t Input;
    /**
     * @param[in] input Utf8 character.
     * @return Returns output token. If input is not handled, read() has to be called again with the same input. The input will be handled at least
     * every fourth call.
     */
    constexpr std::tuple<Token, catta::parser::InputHandled> read(const Input input)
    {
        typedef catta::parser::InputHandled Handled;
        typedef std::tuple<Token, Handled> Tuple;
        const auto handled = [this](const char8_t character)
        {
            _state = STATE_BASE;
            return Tuple{Token::character(character), Handled::yes()};
        };
        const auto next = [this](const std::uint8_t state, const char8_t character)
        {
            _state = state;
            return Tuple{Token::character(character), Handled::no()};
        };
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
        const auto character = [input](const std::uint8_t shift, const std::uint8_t maskLength)
        {
            const std::uint8_t maks0 = static_cast<std::uint8_t>(0b11111111 << (8 - maskLength));
            const std::uint8_t maks1 = static_cast<std::uint8_t>(~(1 << (8 - maskLength)));
            return static_cast<char8_t>(static_cast<std::uint8_t>(((input >> shift) | maks0) & maks1));
        };
        switch (_state)
        {
            case STATE_START:
            case STATE_BASE:
                if (input == '\0') return end();
                if ((input >= 0xD800 && input <= 0xDFFF) || input >= 0x110000) return error();
                if (input < (1 << 7)) return handled(static_cast<char8_t>(input));
                if (input < (1 << 11))
                {
                    _data = {char8_t{}, char8_t{}, character(0, 2)};
                    return next(STATE_1_MISSING, character(6, 3));
                }
                if (input < (1 << 16))
                {
                    _data = {char8_t{}, character(6, 2), character(0, 2)};
                    return next(STATE_2_MISSING, character(12, 4));
                }
                _data = {character(12, 2), character(6, 2), character(0, 2)};
                return next(STATE_3_MISSING, character(18, 5));
            case STATE_3_MISSING:
                return next(STATE_2_MISSING, _data[0]);
            case STATE_2_MISSING:
                return next(STATE_1_MISSING, _data[1]);
            case STATE_1_MISSING:
                return handled(_data[2]);
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
            case STATE_3_MISSING:
            case STATE_2_MISSING:
            case STATE_1_MISSING:
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
    constexpr Utf8Serializer() : _data{}, _state(STATE_START) {}

  private:
    std::array<char8_t, 3> _data;
    std::uint8_t _state;
    static constexpr std::uint8_t STATE_START = 0;
    static constexpr std::uint8_t STATE_BASE = 1;
    static constexpr std::uint8_t STATE_3_MISSING = 2;
    static constexpr std::uint8_t STATE_2_MISSING = 3;
    static constexpr std::uint8_t STATE_1_MISSING = 4;
    static constexpr std::uint8_t STATE_END = 5;
    static constexpr std::uint8_t STATE_ERROR = 6;
};
}  // namespace parser
}  // namespace catta
