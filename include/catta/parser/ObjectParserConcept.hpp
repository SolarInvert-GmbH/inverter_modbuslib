#pragma once

// std
#include <tuple>

// catta
#include <catta/parser/InputHandled.hpp>
#include <catta/parser/State.hpp>
#include <catta/parser/TokenConcept.hpp>

namespace catta
{
namespace parser
{
/**
 * @tparam ObjectParser The class that is checked if it is an object parser.
 *
 * @brief ObjectParserConcept describes an interface for object parser.
 *
 * A object parser parses objects of a type from a sequence of inputs.
 *
 * Has to have the folling methodes:
 * read: Reads from input character and returns a tuple of the object (empty if parsing is not done), the error (empty if no parsing error) and the
 * information if the input was handeled or not.
 *
 * state: returns the state (start, running, done or failed) of the parser.
 *
 * ObjectParser has to be default initializable and copy constructible.
 *
 * If the parser is once in the error state it can not leave it.
 */
template <class ObjectParser>
concept ObjectParserConcept = requires(const ObjectParser& constObjectParser, ObjectParser& changeableObjectParser,
                                       const typename ObjectParser::Input input)
{
    ErrorConcept<typename ObjectParser::Error>;
    {
        changeableObjectParser.read(input)
        } -> std::same_as<std::tuple<typename ObjectParser::Error, InputHandled>>;
    {
        constObjectParser.state()
        } -> std::same_as<State>;
    {
        ObjectParser {}
        } -> std::same_as<ObjectParser>;
    {
        constObjectParser.data()
        } -> std::same_as<typename ObjectParser::Output>;
    std::default_initializable<ObjectParser>;
    std::copy_constructible<ObjectParser>;
};
}  // namespace parser
}  // namespace catta
