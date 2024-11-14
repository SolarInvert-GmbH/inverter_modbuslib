// catta
#include <catta/json/Token.hpp>

// random
#include <catta/random/json/Token.hpp>

// fromtostring
#include <catta/fromstring/json/Token.hpp>
#include <catta/tostring/json/Token.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT>
static bool checkCreate(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<catta::json::TokenType>();
    const auto output = [input]()
    {
        using Type = catta::json::TokenType;
        using Token = catta::json::Token;
        switch (input.type())
        {
            case Type::openCurlyBracket():
                return Token::end();
            case Type::closeCurlyBracket():
                return Token::closeCurlyBracket();
            case Type::openSquareBracket():
                return Token::openSquareBracket();
            case Type::closeSquareBracket():
                return Token::closeSquareBracket();
            case Type::colon():
                return Token::colon();
            case Type::comma():
                return Token::comma();
            case Type::nullObject():
                return Token::nullObject();
            case Type::boolTrue():
                return Token::boolTrue();
            case Type::boolFalse():
                return Token::boolFalse();
            case Type::integerNumber():
                return Token::integerNumber(input.integerValue());
            case Type::floatNumber():
                return Token::floatNumber(input.floatValue());
            case Type::openString():
                return Token::openString();
            case Type::character():
                return Token::character(input.unicodeCharacterValue());
            case Type::closeString():
                return Token::closeString();
            case Type::end():
                return Token::end();
            case Type::error():
                return Token::error(input.errorValue());

            default:
                return Token::empty();
        }
    }();
    if (input != output) return test.failedExpected(input, output, "output");
    return true;
}

int main()
{
    using Output = catta::test::ConsoleOutput;
    using Type = catta::json::Token;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    return error;
}
