// catta
#include <catta/parser/CharacterConcept.hpp>
#include <catta/parser/DefaultToken.hpp>
#include <catta/parser/TokenConcept.hpp>

// random
#include <catta/random/parser/DefaultToken.hpp>

// fromtostring
#include <catta/fromstring/parser/DefaultToken.hpp>
#include <catta/fromstring/state/DefaultError.hpp>
#include <catta/tostring/parser/DefaultToken.hpp>
#include <catta/tostring/state/DefaultError.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

static_assert(catta::parser::TokenConcept<catta::parser::DefaultToken<char, catta::state::DefaultError>>);

template <catta::test::Output OUTPUT, catta::parser::CharacterConcept Character>
static bool checkCreate(catta::test::Test<OUTPUT>& test)
{
    typedef catta::parser::DefaultToken<Character, catta::state::DefaultError> Token;
    const auto input = test.random().template create<Token>();
    const auto output = [input]()
    {
        switch (input.type())
        {
            case catta::parser::DefaultTokenType::end():
                return Token::end();
            case catta::parser::DefaultTokenType::error():
                return Token::error(input.errorValue());
            case catta::parser::DefaultTokenType::value():
                return Token::character(input.characterValue());
            default:
                return Token::empty();
        }
    }();
    if (input != output) return test.failedExpected(input, output, "output");
    return true;
}

template <catta::parser::CharacterConcept Character>
static int test_all()
{
    using Type = catta::parser::DefaultToken<Character, catta::state::DefaultError>;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    const auto test_create = checkCreate<Output, Character>;
    int error = 0;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_create, "create", output, 10000)) error++;
    return error;
}

int main()
{
    int error = 0;
    error += test_all<char>();
    error += test_all<std::uint8_t>();
    error += test_all<char8_t>();
    error += test_all<char32_t>();
    return error;
}
