#pragma once

// std
#include <array>
#include <string_view>

namespace catta
{
namespace parser
{
/**
 * @brief Wrapper class for boolean. Represent if input was handled by parser or not.
 *
 * In some languages, it is not clear until you read the input charcter after the end of a token that it is over. For example, when we read in a
 * decimal number, it is not clear that it has ended until it has ended. If another token comes directly after the number, there must be a mechanism
 * to return both values. We return the last token (the number) and mark the input as not handled. The caller of the parser has to call again wiht
 * the same input and the second token will be returned.
 *
 * An other solution would be to return container with zero, one or two token. Cattalib uses the first solution.
 */
class InputHandled
{
  public:
    /**
     * Default constructor. Creates no.
     */
    [[nodiscard]] constexpr InputHandled() : InputHandled(false) {}
    /**
     * @return Returns the input handled constant.
     */
    [[nodiscard]] constexpr static InputHandled yes() noexcept { return InputHandled{true}; }
    /**
     * @return Returns the input not handled constant.
     */
    [[nodiscard]] constexpr static InputHandled no() noexcept { return InputHandled{}; }
    /**
     * @return Returns the object as boolean.
     */
    [[nodiscard]] constexpr operator bool() const noexcept { return _value; }
    /**
     * @param[in] other The other InputHandled.
     * @return Returns @b true if the two InputHandled objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const InputHandled& other) const = default;
    /**
     * Input handled in text form.
     */
    constexpr static std::array<std::string_view, 2> enumNames = {"INPUT_HANDLED", "INPUT_NOT_HANDLED"};

  private:
    constexpr InputHandled(const bool value) : _value(value) {}
    bool _value;
};
}  // namespace parser
}  // namespace catta
