#pragma once

// parser
#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

// json
#include <catta/json/Token.hpp>

namespace catta
{
namespace tojson
{
/**
 * @brief The catta::tojson::Serializer<T> class creates json token streams from objects from type T by serializing the objects.
 * @tparam T The class which is serialized to json token stream.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Serializer;

/**
 * @brief Serializable is satisfied if there is class catta::tojson::Serializer<T> with a read and a data methode.
 *
 * Can be used to implment additional serializer for varios types.
 * @see If T has catta::fromjson::Parsable and catta::tojson::Serializable satisfied, they should use the same json representation, so you can parse
 * the json stream that where created.
 * @tparam T The class which is serialized to json token stream.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Serializable = catta::parser::ObjectParserConcept<catta::tojson::Serializer<T>> &&
    std::same_as<typename catta::tojson::Serializer<T>::Input, T> && std::same_as<typename catta::tojson::Serializer<T>::Output, catta::json::Token>;

}  // namespace tojson
}  // namespace catta
