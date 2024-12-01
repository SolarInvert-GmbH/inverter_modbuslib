#pragma once

// parser
#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

// modbus
#include <catta/modbus/Token.hpp>

namespace catta
{
namespace tomodbus
{
/**
 * @brief The catta::tomodbus::Serializer<T> class creates modbus token streams from objects from type T by serializing the objects.
 * @tparam T The class which is serialized to modbus token stream.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Serializer;

/**
 * @brief Serializable is satisfied if there is class catta::tomodbus::Serializer<T> with a read and a data methode.
 *
 * Can be used to implment additional serializer for varios types.
 * @see If T has catta::frommodbus::Parsable and catta::tomodbus::Serializable satisfied, they should use the same modbus representation, so you can
 * parse the modbus stream that where created.
 * @tparam T The class which is serialized to modbus token stream.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Serializable =
    catta::parser::ObjectParserConcept<catta::tomodbus::Serializer<T>> && std::same_as<typename catta::tomodbus::Serializer<T>::Input, T> &&
    std::same_as<typename catta::tomodbus::Serializer<T>::Output, catta::modbus::Token>;

}  // namespace tomodbus
}  // namespace catta
