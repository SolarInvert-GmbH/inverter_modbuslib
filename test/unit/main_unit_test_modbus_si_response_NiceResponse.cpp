// catta
#include <catta/modbus/si/response/NiceResponse.hpp>

// random
#include <catta/random/modbus/si/response/NiceResponse.hpp>

// fromtostring
#include <catta/fromstring/modbus/si/response/NiceResponse.hpp>
#include <catta/tostring/modbus/si/response/NiceResponse.hpp>

// json
#include <catta/fromjson/modbus/si/response/NiceResponse.hpp>
#include <catta/tojson/modbus/si/response/NiceResponse.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromJson.hpp>
#include <catta/test/ToFromString.hpp>
#include <catta/tostring/Hexadecimal.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT>
static bool checkCreate(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<catta::modbus::si::response::NiceResponse>();
    const auto output = [input]()
    {
        using Type = catta::modbus::si::response::NiceType;
        switch (input.type())
        {
            case Type::exception():
                return catta::modbus::si::response::NiceResponse::exception(input.exceptionValue());
            case Type::factoryValues():
                return catta::modbus::si::response::NiceResponse::factoryValues(input.factoryValuesValue());
            case Type::readError():
                return catta::modbus::si::response::NiceResponse::readError(input.readErrorValue());
            case Type::readOperatingData33():
                return catta::modbus::si::response::NiceResponse::readOperatingData33(input.readOperatingData33Value());
            case Type::readOperatingData3e():
                return catta::modbus::si::response::NiceResponse::readOperatingData3e(input.readOperatingData3eValue());
            case Type::switchOffGridRelay():
                return catta::modbus::si::response::NiceResponse::switchOffGridRelay(input.successValue());
            case Type::switchOnGridRelay():
                return catta::modbus::si::response::NiceResponse::switchOnGridRelay(input.successValue());
            case Type::forceIdle():
                return catta::modbus::si::response::NiceResponse::forceIdle(input.successValue());
            case Type::deactivateIdle():
                return catta::modbus::si::response::NiceResponse::deactivateIdle(input.successValue());
            case Type::startConstantVoltage():
                return catta::modbus::si::response::NiceResponse::startConstantVoltage(input.successValue());
            case Type::endConstantVoltage():
                return catta::modbus::si::response::NiceResponse::endConstantVoltage(input.successValue());
            case Type::setPowerFactor():
                return catta::modbus::si::response::NiceResponse::setPowerFactor(input.successValue());
            case Type::controlBatteryInvert():
                return catta::modbus::si::response::NiceResponse::controlBatteryInvert(input.successValue());
            case Type::limitBatteryInvert():
                return catta::modbus::si::response::NiceResponse::limitBatteryInvert(input.successValue());
            case Type::writeRegister():
                return catta::modbus::si::response::NiceResponse::writeRegister(input.writeRegisterValue());
            case Type::readRegister():
                return catta::modbus::si::response::NiceResponse::readRegister(input.registerValue());
            default:
                return catta::modbus::si::response::NiceResponse::empty();
        }
    }();
    if (debug) test.status(catta::tostring::toString(input));
    if (input != output)
    {
        const auto p = [](const auto v)
        {
            std::string s;
            const auto& a = v.raw();
            for (std::size_t i = 0; i < a.size(); i++)
            {
                s += catta::tostring::toString(catta::Hexadecimal(a[i]));
                if (i + 1 < a.size()) s += ",";
            }
            return s;
        };
        std::cout << "in:  " << p(input) << '\n';
        std::cout << "out: " << p(output) << '\n';
        return test.failedExpected(output, input, "output");
    }
    return true;
}

int main()
{
    using Type = catta::modbus::si::response::NiceResponse;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_create = checkCreate<Output>;
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    const auto test_tofromjson = catta::test::checkToFromJson<Output, Type, debug>;
    int error = 0;
    if (!catta::test::execute<Output>(test_create, "create", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofromjson, "tofromjson", output, 10000)) error++;
    return error;
}
