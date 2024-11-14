#pragma once

// catta
#include <catta/parser/TextPosition.hpp>

namespace catta
{
namespace parser
{
/**
 * @tparam CHARACTER Character type. Can be char or char32_t.
 * @brief Class for line and column counting. Can handle \\n, \\n\\r, \\r\\n and \\r.
 *
 * @author CattaTech - Maik Urbannek
 */
template <class CHARACTER>
requires std::same_as<char, CHARACTER> || std::same_as<char32_t, CHARACTER>
class LineColumnCounter
{
  public:
    /**
     * @param[in] startPosition Start position.
     * (Default-)Constructor.
     */
    [[nodiscard]] constexpr LineColumnCounter(TextPosition startPosition = TextPosition{}) noexcept : _position{startPosition}, _state{DEFAULT_STATE}
    {
    }
    /**
     * @param[in] c Input character.
     * Handleds input character.
     */
    constexpr void read(const CHARACTER c) noexcept
    {
        const auto next = [this](const std::uint8_t state) { _state = state; };
        switch (_state)
        {
            case N_STATE:
                switch (c)
                {
                    case CHARACTER{'\n'}:
                        _position = _position.nextRow();
                        return;
                    case CHARACTER{'\r'}:
                        return next(DEFAULT_STATE);
                    default:
                        _position = _position.nextColumn();
                        return;
                }
            case R_STATE:
                switch (c)
                {
                    case CHARACTER{'\n'}:
                        return next(DEFAULT_STATE);
                    case CHARACTER{'\r'}:
                        _position = _position.nextRow();
                        return;
                    default:
                        _position = _position.nextColumn();
                        return;
                }
            default:
                switch (c)
                {
                    case CHARACTER{'\n'}:
                        _position = _position.nextRow();
                        return next(N_STATE);
                    case CHARACTER{'\r'}:
                        _position = _position.nextRow();
                        return next(R_STATE);
                    default:
                        _position = _position.nextColumn();
                        return;
                }
        }
    }
    /**
     * @return Returns the current text position of the line column counter.
     */
    [[nodiscard]] constexpr TextPosition position() noexcept { return _position; }

  private:
    TextPosition _position;
    std::uint8_t _state;
    constexpr static std::uint8_t N_STATE = 0;
    constexpr static std::uint8_t R_STATE = 1;
    constexpr static std::uint8_t DEFAULT_STATE = 2;
};
}  // namespace parser
}  // namespace catta
