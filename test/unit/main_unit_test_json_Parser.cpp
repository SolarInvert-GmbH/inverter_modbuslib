// catta
#include <catta/json/Parser.hpp>

// random
#include <catta/random/json/Token.hpp>

// fromtostring
#include <catta/fromstring/json/Token.hpp>
#include <catta/tostring/json/Token.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/Test.hpp>

static_assert(catta::parser::SequenceParserConcept<catta::json::Parser>);

static std::string tostring(const char32_t* data)
{
    std::string tmp;
    for (const char32_t* i = data; *i != '\0'; i++)
    {
        if (i != data) tmp += ',';
        const auto h = [i](const auto s) { return catta::halfByteToHexadecimal(0xf & ((*i) >> s)); };
        if (*i < 0xFFFF)
        {
            tmp += h(5);
            tmp += h(4);
        }
        if (*i < 0xFF)
        {
            tmp += h(3);
            tmp += h(2);
        }
        tmp += h(1);
        tmp += h(0);
    }
    return tmp;
}

template <std::size_t N>
static std::string print(const std::array<catta::json::Token, N>& data)
{
    std::string tmp = "[";
    for (std::size_t i = 0; i < data.size(); i++)
        if (!data[i].isEmpty()) tmp += (i != 0 ? ", " : "") + catta::tostring::toString(data[i]);
    tmp += "]";
    return tmp;
};

template <std::size_t N>
static bool handleCharacter(catta::test::TestConcept auto& test, catta::json::Parser& parser, const char32_t c, std::size_t& i,
                            std::array<catta::json::Token, N>& data)
{
    const auto [token, handled] = parser.read(c);
    if (!token.type().isEmpty())
    {
        if (i >= data.size()) return test.failed("Got more token than expexted: " + catta::tostring::toString(token) + ".");
        data[i] = token;
        i++;
    }
    if (!handled)
    {
        const auto [token, handled] = parser.read(c);
        if (!token.type().isEmpty())
        {
            if (i >= data.size()) return test.failed("Got more token than expexted: " + catta::tostring::toString(token) + ".");
            data[i] = token;
            i++;
        }
        if (!handled) return test.failed("Get not handled input two times in a row.");
    }
    return true;
};

template <catta::test::Output OUTPUT>
static bool checkReadCombine(catta::test::Test<OUTPUT>& test)
{
    using Token = catta::json::Token;
    using Pair = std::pair<const char32_t*, std::array<Token, 2>>;
    static constexpr std::array<Pair, 7> closed = {Pair{U"[", std::array<Token, 2>{Token::openSquareBracket()}},
                                                   Pair{U"]", std::array<Token, 2>{Token::closeSquareBracket()}},
                                                   Pair{U"{", std::array<Token, 2>{Token::openCurlyBracket()}},
                                                   Pair{U"}", std::array<Token, 2>{Token::closeCurlyBracket()}},
                                                   Pair{U",", std::array<Token, 2>{Token::comma()}},
                                                   Pair{U":", std::array<Token, 2>{Token::colon()}},
                                                   Pair{U"\"\"", std::array<Token, 2>{Token::openString(), Token::closeString()}}};
    constexpr std::array<Pair, 11> notClosed = {Pair{U"true", std::array<Token, 2>{Token::boolTrue()}},
                                                Pair{U"false", std::array<Token, 2>{Token::boolFalse()}},
                                                Pair{U"null", std::array<Token, 2>{Token::nullObject()}},
                                                Pair{U"0", std::array<Token, 2>{Token::integerNumber(0)}},
                                                Pair{U"-1", std::array<Token, 2>{Token::integerNumber(-1)}},
                                                Pair{U"123", std::array<Token, 2>{Token::integerNumber(123)}},
                                                Pair{U"0.123", std::array<Token, 2>{Token::floatNumber(0.123)}},
                                                Pair{U"-0.123", std::array<Token, 2>{Token::floatNumber(-0.123)}},
                                                Pair{U"0.123e2", std::array<Token, 2>{Token::floatNumber(0.123e2)}},
                                                Pair{U"0.123e+2", std::array<Token, 2>{Token::floatNumber(0.123e+2)}},
                                                Pair{U"0.123e-2", std::array<Token, 2>{Token::floatNumber(0.123e-2)}}};
    const auto merge = [](const std::array<Token, 2>& a, const std::array<Token, 2>& b)
    {
        std::array<Token, 5> tmp;
        std::size_t index = 0;
        for (auto e : a)
            if (!e.type().isEmpty())
            {
                tmp[index] = e;
                index++;
            }
        for (auto e : b)
            if (!e.type().isEmpty())
            {
                tmp[index] = e;
                index++;
            }
        tmp[index] = Token::end();
        return tmp;
    };
    const auto check = [&test, merge](const Pair& first, const Pair& second, const char32_t* middle)
    {
        const char32_t* firstString = first.first;
        const char32_t* secondString = second.first;
        if (firstString == nullptr) return test.failed("Internal error: [check] first is null.");
        if (secondString == nullptr) return test.failed("Internal error: [check] second is null.");
        if (middle == nullptr) return test.failed("Internal error: [check] middle is null.");
        const auto expected = merge(first.second, second.second);
        catta::json::Parser parser;
        std::size_t i = 0;
        std::array<Token, 5> result;
        for (const char32_t* c = firstString; *c != '\0'; c++)
            if (!handleCharacter(test, parser, *c, i, result)) return false;
        for (const char32_t* c = middle; *c != '\0'; c++)
            if (!handleCharacter(test, parser, *c, i, result)) return false;
        for (const char32_t* c = secondString; *c != '\0'; c++)
            if (!handleCharacter(test, parser, *c, i, result)) return false;
        if (!handleCharacter(test, parser, '\0', i, result)) return false;
        if (expected != result)
        {
            test.failed("Expected : " + print(expected) + " as output for '" + tostring(firstString) + tostring(middle) + tostring(secondString) +
                        "',");
            test.failed("but got  : " + print(result) + ".");
            return false;
        }
        return true;
    };
    for (const auto& first : closed)
    {
        for (const auto& second : closed)
            if (!check(first, second, U"")) return false;
        for (const auto& second : notClosed)
            if (!check(first, second, U"")) return false;
    }
    for (const auto& first : notClosed)
    {
        for (const auto& second : closed)
            if (!check(first, second, U"")) return false;
        for (const auto& second : notClosed)
            if (!check(first, second, U" ")) return false;
    }
    return true;
}

template <catta::test::Output OUTPUT>
static bool checkReadString(catta::test::Test<OUTPUT>& test)
{
    using Tuple = std::tuple<const char32_t*, const char32_t*, char32_t>;
    using Token = catta::json::Token;

    constexpr std::array<Tuple, 12> table = {
        Tuple{U"\\\"", U"\\u0022", char32_t{0x00000022}}, Tuple{U"\\\\", U"\\u005C", char32_t{0x0000005C}},
        Tuple{U"\\/", U"\\u002F", char32_t{0x0000002F}},  Tuple{U"\\b", U"\\u0008", char32_t{0x00000008}},
        Tuple{U"\\f", U"\\u000C", char32_t{0x0000000C}},  Tuple{U"\\n", U"\\u000A", char32_t{0x0000000A}},
        Tuple{U"\\r", U"\\u000D", char32_t{0x0000000D}},  Tuple{U"\\t", U"\\u0009", char32_t{0x00000009}},
        Tuple{U"a", U"\\u0061", char32_t{0x00000061}},    Tuple{U"α", U"\\u03B1", char32_t{0x000003B1}},
        Tuple{U"ᵃ", U"\\u1D43", char32_t{0x00001D43}},    Tuple{U"𝐚", U"\\uD835\\uDC1A", char32_t{0x0001D41A}},
    };
    const auto check = [&test](const Tuple& first, const Tuple& second, const Tuple& third)
    {
        const auto parse = [&test](const std::array<Token, 6>& expected, const char32_t* first, const char32_t* second, const char32_t* third,
                                   const std::string& type)
        {
            if (first == nullptr) return test.failed("Internal error: [check] first string " + type + " is null.");
            if (second == nullptr) return test.failed("Internal error: [check] second string " + type + " is null.");
            if (third == nullptr) return test.failed("Internal error: [check] third string " + type + " is null.");
            catta::json::Parser parser;
            std::array<Token, 6> result;
            std::size_t i = 0;

            if (!handleCharacter(test, parser, '"', i, result)) return false;
            for (const char32_t* c = first; *c != '\0'; c++)
                if (!handleCharacter(test, parser, *c, i, result)) return false;
            for (const char32_t* c = second; *c != '\0'; c++)
                if (!handleCharacter(test, parser, *c, i, result)) return false;
            for (const char32_t* c = third; *c != '\0'; c++)
                if (!handleCharacter(test, parser, *c, i, result)) return false;
            if (!handleCharacter(test, parser, '"', i, result)) return false;
            if (!handleCharacter(test, parser, '\0', i, result)) return false;
            if (expected != result)
            {
                test.failed("Expected : " + print(expected) + " as output for '" + tostring(first) + tostring(second) + tostring(third) + "',");
                test.failed("but got  : " + print(result) + ".");
                return false;
            }
            return true;
        };
        const auto expected = std::array<Token, 6>{Token::openString(),
                                                   Token::character(std::get<2>(first)),
                                                   Token::character(std::get<2>(second)),
                                                   Token::character(std::get<2>(third)),
                                                   Token::closeString(),
                                                   Token::end()};
        return parse(expected, std::get<0>(first), std::get<0>(second), std::get<0>(third), "plain") &&
               parse(expected, std::get<1>(first), std::get<1>(second), std::get<1>(third), "\\uxxxx");
    };

    for (const auto& first : table)
        for (const auto& second : table)
            for (const auto& third : table)
                if (!check(first, second, third)) return false;
    return true;
}

template <catta::test::Output OUTPUT>
static bool checkReadError(catta::test::Test<OUTPUT>& test)
{
    using Error = catta::json::ParsingError;
    using Pair = std::pair<const char32_t*, Error>;
    constexpr std::array<Pair, 60> table = {Pair{U"\0", Error::jsonEnded()},
                                            Pair{U"t0", Error::unexpectedLiteral()},
                                            Pair{U"tr0", Error::unexpectedLiteral()},
                                            Pair{U"tru0", Error::unexpectedLiteral()},
                                            Pair{U"true0", Error::unexpectedLiteral()},
                                            Pair{U"f0", Error::unexpectedLiteral()},
                                            Pair{U"fa0", Error::unexpectedLiteral()},
                                            Pair{U"fal0", Error::unexpectedLiteral()},
                                            Pair{U"fals0", Error::unexpectedLiteral()},
                                            Pair{U"false0", Error::unexpectedLiteral()},
                                            Pair{U"n0", Error::unexpectedLiteral()},
                                            Pair{U"nu0", Error::unexpectedLiteral()},
                                            Pair{U"nul0", Error::unexpectedLiteral()},
                                            Pair{U"null0", Error::unexpectedLiteral()},
                                            Pair{U"hund", Error::unexpectedLiteral()},
                                            Pair{U"00", Error::badFormedNumber()},
                                            Pair{U"01", Error::badFormedNumber()},
                                            Pair{U"0i", Error::badFormedNumber()},
                                            Pair{U"--", Error::badFormedNumber()},
                                            Pair{U"-i", Error::badFormedNumber()},
                                            Pair{U"-.", Error::badFormedNumber()},
                                            Pair{U"-e", Error::badFormedNumber()},
                                            Pair{U"-+", Error::badFormedNumber()},
                                            Pair{U"-", Error::badFormedNumber()},
                                            Pair{U"1i", Error::badFormedNumber()},
                                            Pair{U"1+", Error::badFormedNumber()},
                                            Pair{U"1-", Error::badFormedNumber()},
                                            Pair{U"0.i", Error::badFormedNumber()},
                                            Pair{U"0..", Error::badFormedNumber()},
                                            Pair{U"0.e", Error::badFormedNumber()},
                                            Pair{U"0.+", Error::badFormedNumber()},
                                            Pair{U"0.-", Error::badFormedNumber()},
                                            Pair{U"0.", Error::badFormedNumber()},
                                            Pair{U"0.0ee", Error::badFormedNumber()},
                                            Pair{U"0.0ei", Error::badFormedNumber()},
                                            Pair{U"0.0e.", Error::badFormedNumber()},
                                            Pair{U"0.0e", Error::badFormedNumber()},
                                            Pair{U"0.0e+", Error::badFormedNumber()},
                                            Pair{U"0.0e++", Error::badFormedNumber()},
                                            Pair{U"0.0e+-", Error::badFormedNumber()},
                                            Pair{U"0.0e+e", Error::badFormedNumber()},
                                            Pair{U"0.0e+i", Error::badFormedNumber()},
                                            Pair{U"0.0e+0i", Error::badFormedNumber()},
                                            Pair{U"0.0e+0e", Error::badFormedNumber()},
                                            Pair{U"0.0e+0+", Error::badFormedNumber()},
                                            Pair{U"0.0e+0-", Error::badFormedNumber()},
                                            Pair{U"\"", Error::stringNotClosed()},
                                            Pair{U"\"\n\"", Error::acsiiControlNotAllowed()},
                                            Pair{U"\"\\a\"", Error::unknownEscapeSequence()},
                                            Pair{U"\"\\ug000\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\u0g00\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\u00g0\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\u000g\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uDC00\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uD800\\\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uD800\\u\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uD800\\uD\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uD800\\uD8\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uD800\\uD80\"", Error::badEscapeUnicodeSequence()},
                                            Pair{U"\"\\uD800\\uD800\"", Error::badEscapeUnicodeSequence()}};
    for (const auto& e : table)
    {
        const char32_t* json = e.first;
        const Error expected = e.second;
        catta::json::Parser parser;
        catta::json::Token token;
        for (const char32_t* c = json; token.type() != catta::json::TokenType::error();)
        {
            const auto [returnToken, handled] = parser.read(*c);
            token = returnToken;
            if (handled) c++;
        }
        const Error error = token.errorValue();
        if (expected != error) return test.failedExpected(expected, token.errorValue(), "error for '" + tostring(json) + "'");
    }
    return true;
}

int main()
{
    using Output = catta::test::ConsoleOutput;
    Output output("catta::json::TokenParser");
    const auto test_read_combine = checkReadCombine<Output>;
    const auto test_read_string = checkReadString<Output>;
    const auto test_read_error = checkReadError<Output>;
    int error = 0;
    if (!catta::test::execute<Output>(test_read_combine, "read_combine", output)) error++;
    if (!catta::test::execute<Output>(test_read_string, "read_string", output)) error++;
    if (!catta::test::execute<Output>(test_read_error, "read_error", output)) error++;
    return error;
}
