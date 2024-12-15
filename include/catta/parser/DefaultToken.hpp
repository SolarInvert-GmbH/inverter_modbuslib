#pragma once

// std
#include <cstdint>
#include <variant>

// catta
#include <catta/parser/DefaultTokenType.hpp>
#include <catta/parser/ErrorConcept.hpp>
#include <catta/state/DefaultError.hpp>

namespace catta
{
namespace parser
{
/**
 * @tparam CHARACTER The used output type.
 * @tparam ERROR_TYPE The error type to describe the possible parsing errors.
 *
 * @brief Default token is the simplest implementation of the token concept.
 * @author CattaTech - Maik Urbannek
 */
template <class CHARACTER, ErrorConcept ERROR_TYPE>
class DefaultToken
{
  public:
    /**
     * The character type.
     */
    using Character = CHARACTER;
    /**
     * The error type.
     */
    using Error = ERROR_TYPE;
    /**
     * Default constructor. Creates empty character token.
     */
    [[nodiscard]] constexpr DefaultToken() noexcept : DefaultToken{DefaultTokenType{}, Raw{}} {}
    /**
     * @return Returns the empty character token.
     */
    [[nodiscard]] constexpr static DefaultToken empty() noexcept { return DefaultToken{}; }
    /**
     * @param[in] message The error enum (the thing that went wrong). Has to be not empty.
     * @return Returns error token if message is not empty, otherwise an empty token.
     */
    [[nodiscard]] constexpr static DefaultToken error(const Error message) noexcept
    {
        return message.isEmpty() ? empty() : DefaultToken{DefaultTokenType::error(), message};
    }
    /**
     * @return Returns end token.
     */
    [[nodiscard]] constexpr static DefaultToken end() noexcept { return DefaultToken{DefaultTokenType::end(), Raw{}}; }
    /**
     * @param[in] character The character in token.
     * @return Returns character token with given character.
     */
    [[nodiscard]] constexpr static DefaultToken character(const Character& character) noexcept
    {
        return DefaultToken{DefaultTokenType::value(), character};
    }
    /**
     * @return Returns the type of the token.
     */
    [[nodiscard]] constexpr DefaultTokenType type() const noexcept { return _type; }
    /**
     * @return Returns the the character of the character token. The token has to have the value type (type().isValue() has to be @b true), otherwise
     * the '\0' is returned.
     */
    [[nodiscard]] constexpr Character characterValue() const noexcept
    {
        try
        {
            return std::get<Character>(_data);
        }
        catch (std::bad_variant_access const&)
        {
            return Character{};
        }
    }
    /**
     * @return Returns the the error of the character token. The token has to have the error type (type().isError() has to be @b true), otherwise the
     * Error::empty() is returned.
     */
    [[nodiscard]] constexpr Error errorValue() const noexcept
    {
        try
        {
            return std::get<Error>(_data);
        }
        catch (std::bad_variant_access const&)
        {
            return Error{};
        }
    }
    /**
     * @param[in] other The other DefaultToken.
     * @return Returns @b true if the two DefaultToken objects are the same, otherwise @b false.
     */
    [[nodiscard]] constexpr bool operator==(const DefaultToken& other) const = default;

  private:
    typedef std::variant<Character, Error> Raw;
    constexpr DefaultToken(const DefaultTokenType type, const Raw data) : _type(type), _data(data) {}
    DefaultTokenType _type;
    Raw _data;
};
}  // namespace parser
}  // namespace catta
