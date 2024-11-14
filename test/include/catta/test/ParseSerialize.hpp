#pragma once

// parser

#include <catta/parser/ObjectParserConcept.hpp>
#include <catta/parser/SequenceParserConcept.hpp>

// test
#include <catta/test/Test.hpp>

namespace catta
{
namespace test
{
template <catta::parser::SequenceParserConcept PARSER, catta::parser::SequenceParserConcept SERIALIZER>
requires std::same_as<typename PARSER::Input, typename SERIALIZER::Token::Character> &&
    std::same_as<typename SERIALIZER::Input, typename PARSER::Token::Character> && catta::random::Randomable<typename SERIALIZER::Input>
bool checkParseSerialize(TestConcept auto& test, PARSER& parser, SERIALIZER& serializer)
{
    typedef typename SERIALIZER::Input Input;
    const auto input = test.random().template create<Input>();
    bool sRun = true;
    std::optional<typename PARSER::Token::Character> result = {};
    do
    {
        const auto [sToken, handled] = serializer.read(input);
        if (sToken.type().isError()) return test.failed("serializer.read() failed.");
        if (sToken.type().isEnd()) return test.failed("serializer.read() created end token.");
        if (sToken.type().isValue())
        {
            bool pRun = true;
            do
            {
                const auto [pToken, handled] = parser.read(sToken.characterValue());
                if (pToken.type().isError()) return test.failed("parser.read() failed.");
                if (pToken.type().isEnd()) return test.failed("parser.read() created end token.");
                if (pToken.type().isValue())
                {
                    if (result) return test.failed("parser parsed two outputs.");
                    result = pToken.characterValue();
                }
                pRun = !handled;
            } while (pRun);
        }
        sRun = !handled;
        if (result && !handled) return test.failed("Parser produced output, but serializer did not handled input.");
    } while (sRun);
    if (!result) return test.failed("Did not parser produced output.");
    if (input != result.value()) return test.failedExpectedSafe(input, result.value(), "as output");
    return true;
}
template <catta::parser::SequenceParserConcept PARSER>
bool checkSequencerEnd(TestConcept auto& test, PARSER& parser, const typename PARSER::Input input, const std::string& name)
{
    bool run = true;
    bool end = false;
    do
    {
        const auto [token, handled] = parser.read(input);
        if (token.type().isEmpty())
        {
        }
        else if (token.type().isEnd())
        {
            if (end) return test.failed(name + " found more than one end token.");
            end = true;
        }
        run = !handled;
        if (end && !handled) return test.failed(name + " produced end, but has not handled input.");
    } while (run);
    if (!end) return test.failed(name + " handled input, but did not produce end.");
    return true;
}

template <catta::parser::ObjectParserConcept PARSER, catta::parser::SequenceParserConcept SERIALIZER>
requires std::same_as<typename PARSER::Input, typename SERIALIZER::Token::Character> &&
    std::same_as<typename SERIALIZER::Input, typename PARSER::Output> && catta::random::Randomable<typename SERIALIZER::Input>
bool checkParseSerialize(TestConcept auto& test, PARSER& parser, SERIALIZER& serializer)
{
    typedef typename SERIALIZER::Input Input;
    const auto input = test.random().template create<Input>();

    bool sRun = true;
    std::optional<typename PARSER::Output> result = {};
    do
    {
        const auto [sToken, handled] = serializer.read(input);
        if (sToken.type().isError()) return test.failed("serializer.read() failed.");
        if (sToken.type().isEnd()) return test.failed("serializer.read() created end token.");
        if (sToken.type().isValue())
        {
            bool pRun = true;
            do
            {
                const auto [error, handled] = parser.read(sToken.characterValue());
                if (!error.isEmpty()) return test.failed("parser.read() failed.");
                if (parser.state().isDone())
                {
                    if (result) return test.failed("parser parsed two outputs.");
                    result = parser.data();
                }
                pRun = !handled;
            } while (pRun);
        }
        sRun = !handled;
        if (result && !handled) return test.failed("Parser produced output, but serializer did not handled input.");
    } while (sRun);
    if (!result) return test.failed("Did not parser produced output.");
    if (input != result.value()) return test.failedExpectedSafe(input, result.value(), "as output");
    return true;
}

bool checkErrorCases(catta::test::TestConcept auto& test, const auto input, const catta::parser::ErrorConcept auto expected,
                     catta::parser::SequenceParserConcept auto parser, const std::string& name)
{
    std::string sequnce;
    for (const auto& c : input)
    {
        sequnce += (sequnce.empty() ? std::string() : std::string(",")) + "0x" + catta::tostring::toString(catta::Hexadecimal(c));
        bool b = true;
        while (b)
        {
            const auto [token, handled] = parser.read(c);
            if (token.type().isError())
            {
                if (token.errorValue() != expected) return test.failedExpected(expected, token.errorValue(), name + " error");
                return true;
            }
            b = !handled;
        }
    }
    return false;
}
}  // namespace test
}  // namespace catta
