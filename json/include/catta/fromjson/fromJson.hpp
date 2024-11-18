#pragma once

// parser
#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/state/DefaultError.hpp>

// json
#include <catta/json/Token.hpp>

// std
#include <concepts>

namespace catta
{
namespace fromjson
{
/**
 * @brief The catta::fromjson::Parser<T> class creates objects from type T by parsing json token streams.
 * @tparam T The class which is parsed from json token stream.
 * @author CattaTech - Maik Urbannek
 */
template <class T>
class Parser;

/**
 * @brief Parsable is satisfied if there is class catta::fromjson::Parser<T> with a read and a data methode.
 *
 * Can be used to implment additional parsers for varios types.
 * @see If T is catta::fromjson::Parsable and catta::tojson::Serializable satisfied, they should use the same json token stream representation, so you
 * can parse the json token streams that where created.
 * @tparam T The class which is parsed from json token stream.
 * @author CattaTech - Maik Urbannek
 */
template <typename T>
concept Parsable = catta::parser::ObjectParserConcept<catta::fromjson::Parser<T>> &&
    std::same_as<typename catta::fromjson::Parser<T>::Input, catta::json::Token> && std::same_as<typename catta::fromjson::Parser<T>::Output, T>;

}  // namespace fromjson
}  // namespace catta
