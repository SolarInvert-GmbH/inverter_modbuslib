#pragma once

// catta
#include <catta/parser/InputHandled.hpp>
#include <catta/parser/State.hpp>
#include <catta/parser/TokenConcept.hpp>

// std
#include <concepts>
#include <tuple>

namespace catta
{
namespace parser
{
/**
 * @tparam SequenceParser The class that is checked if it is an sequence parser.
 *
 * @brief SequenceParser describes an interface for sequence parser.
 *
 * A sequence parser parses a sequence of objects (a stream) from a sequence of input. So data with varible size can be parsed and handeled
 * without allocating and deallocating memory.
 *
 * Has to have the folling methodes:
 * read: Reads from input and returns a tuple of the token (can be empty, have a value, be an error or end) and the information if the input was
 * handeled or not. state: returns the state (start, running, done or failed) of the parser.
 *
 * ObjectParser has to be default initializable and copy constructible.
 *
 * If the parser is once in the error state it can not leave it.
 */
template <class SequenceParser>
concept SequenceParserConcept = requires(const SequenceParser& constSequenceParser, SequenceParser& changeableSequenceParser,
                                         const typename SequenceParser::Input input)
{
    catta::parser::TokenConcept<typename SequenceParser::Token>;
    {
        changeableSequenceParser.read(input)
        } -> std::same_as<std::tuple<typename SequenceParser::Token, catta::parser::InputHandled>>;
    {
        constSequenceParser.state()
        } -> std::same_as<catta::parser::State>;
    std::default_initializable<SequenceParser>;
    std::copy_constructible<SequenceParser>;
};
}  // namespace parser
}  // namespace catta
