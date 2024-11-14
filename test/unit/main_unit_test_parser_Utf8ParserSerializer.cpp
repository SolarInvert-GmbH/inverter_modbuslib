// catta
#include <catta/parser/Utf8Parser.hpp>
#include <catta/parser/Utf8Serializer.hpp>

// random
#include <catta/random/Random.hpp>

// fromtostring
#include <catta/tostring/state/DefaultError.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/ParseSerialize.hpp>
#include <catta/test/Test.hpp>

static_assert(catta::parser::SequenceParserConcept<catta::parser::Utf8Parser>);
static_assert(catta::parser::SequenceParserConcept<catta::parser::Utf8Serializer>);

template <catta::test::Output OUTPUT>
static bool checkParseSerialze(catta::test::Test<OUTPUT>& test)
{
    catta::parser::Utf8Parser parser;
    catta::parser::Utf8Serializer serializer;
    for (std::size_t i = 0; i < 100; i++)
        if (!catta::test::checkParseSerialize(test, parser, serializer)) return false;
    if (!catta::test::checkSequencerEnd(test, parser, '\0', "Parser")) return false;
    if (!catta::test::checkSequencerEnd(test, serializer, '\0', "Serializer")) return false;
    return true;
}

template <catta::test::Output OUTPUT>
static bool checkErrorCases(catta::test::Test<OUTPUT>& test)
{
    const std::array<std::u32string, 3> serializerError = {U"\xD800", U"\xDFFF", U"\x110000"};
    const std::array<std::u8string, 7> parserError = {u8"\xbf",     u8"\xdf\x7f",     u8"\xef\x7f",        u8"\xef\xbf\x7f",
                                                      u8"\xf7\x7f", u8"\xf7\xbf\x7f", u8"\xf7\xbf\xbf\x7f"};
    for (const auto& error : parserError)
        if (!checkErrorCases(test, error, catta::state::DefaultError::error(), catta::parser::Utf8Parser(), "Parser")) return false;
    for (const auto& error : serializerError)
        if (!checkErrorCases(test, error, catta::state::DefaultError::error(), catta::parser::Utf8Serializer(), "Serializer")) return false;
    return true;
}
int main()
{
    using Output = catta::test::ConsoleOutput;
    Output output("catta::json::Utf8Parser+catta::json::Utf8Serializer");
    const auto test_parse_serialze = checkParseSerialze<Output>;
    const auto test_error_cases = checkErrorCases<Output>;
    int error = 0;
    if (!catta::test::execute<Output>(test_parse_serialze, "parse_serialze", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_error_cases, "error_cases", output)) error++;
    return error;
}
