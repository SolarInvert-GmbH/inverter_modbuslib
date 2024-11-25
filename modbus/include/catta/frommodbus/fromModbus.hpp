#pragma once

// parser
#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

// modbus
#include <catta/modbus/Token.hpp>

// std
#include <concepts>

namespace catta
{
namespace frommodbus
{
/**
 * @brief The catta::frommodbus::Parser<T> class creates objects from type T by parsing modbus token streams.
 * @tparam T The class which is parsed from modbus token stream.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Parser;

/**
 * @brief Parsable is satisfied if there is class catta::frommodbus::Parser<T> with a read and a data methode.
 *
 * Can be used to implment additional parsers for varios types.
 * @see If T is catta::frommodbus::Parsable and catta::tomodbus::Serializable satisfied, they should use the same modbus token stream representation,
 * so you can parse the modbus token streams that where created.
 * @tparam T The class which is parsed from modbus token stream.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Parsable = catta::parser::ObjectParserConcept<catta::frommodbus::Parser<T>> &&
    std::same_as<typename catta::frommodbus::Parser<T>::Input, catta::modbus::Token> &&
    std::same_as<typename catta::frommodbus::Parser<T>::Output, T>;

}  // namespace frommodbus
}  // namespace catta
