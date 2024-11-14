#pragma once

// std
#include <compare>
#include <cstdint>

namespace catta
{
namespace parser
{
/**
 * @brief Represent the position in a text (row and column).
 *
 * @author CattaTech - Maik Urbannek
 */
class TextPosition
{
  public:
    /**
     * Default constructor. Returns row and column one.
     */
    [[nodiscard]] constexpr TextPosition() noexcept : TextPosition(1, 1) {}
    /**
     * Constructor.
     * @param[in] row Line of the text. Has to be at least one (is set to one otherwise).
     * @param[in] column Column of the text. Has to be at least one (is set to one otherwise).
     */
    [[nodiscard]] constexpr explicit TextPosition(const std::size_t row, const std::size_t column) noexcept
        : _row{row == 0 ? 1 : row}, _column{column == 0 ? 1 : column}
    {
    }
    /**
     * @return Returns the text position that is at the beginning of the next row.
     */
    [[nodiscard]] constexpr TextPosition nextRow() const noexcept { return TextPosition{_row + 1, 1}; }
    /**
     * @return Returns the text position that is one character further.
     */
    [[nodiscard]] constexpr TextPosition nextColumn() const noexcept { return TextPosition{_row, _column + 1}; }
    /**
     * @param[in] other The other TextPosion.
     * @return Returns @b true if the two TextPosion objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const TextPosition& other) const = default;
    /**
     * @param other Other text position to compare.
     * @return Returns the tree-way comparision (implements <,<=,>=,== and !=).
     */
    [[nodiscard]] constexpr auto operator<=>(const TextPosition& other) const = default;
    /**
     * @return Returns the row of the text position.
     */
    [[nodiscard]] constexpr std::size_t row() const noexcept { return _row; }
    /**
     * @return Returns the column of the text position.
     */
    [[nodiscard]] constexpr std::size_t column() const noexcept { return _column; }

  private:
    std::size_t _row;
    std::size_t _column;
};
}  // namespace parser
}  // namespace catta
