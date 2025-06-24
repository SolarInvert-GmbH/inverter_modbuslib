// catta
#include <catta/modbus/si/response/Response.hpp>

// random
#include <catta/random/modbus/si/response/Response.hpp>

// fromtostring
#include <catta/fromstring/modbus/si/response/Response.hpp>
#include <catta/tostring/modbus/si/response/Response.hpp>

// json
#include <catta/fromjson/modbus/si/response/Response.hpp>
#include <catta/tojson/modbus/si/response/Response.hpp>

// modbus
#include <catta/frommodbus/modbus/si/response/Response.hpp>
#include <catta/tomodbus/modbus/si/response/Response.hpp>

// test
#include <catta/test/ConsoleOutput.hpp>
#include <catta/test/CopyMove.hpp>
#include <catta/test/Test.hpp>
#include <catta/test/ToFromJson.hpp>
#include <catta/test/ToFromModbus.hpp>
#include <catta/test/ToFromString.hpp>

static constexpr bool debug = false;

template <catta::test::Output OUTPUT>
static bool checkCreate(catta::test::Test<OUTPUT>& test)
{
    const auto input = test.random().template create<catta::modbus::si::response::Response>();
    const auto output = [input]()
    {
        using Type = catta::modbus::si::response::Type;
        switch (input.type())
        {
            case Type::exception():
                return catta::modbus::si::response::Response::exception(input.exceptionValue());
            case Type::factoryValues():
                return catta::modbus::si::response::Response::factoryValues(input.factoryValuesValue());
            case Type::readError():
                return catta::modbus::si::response::Response::readError(input.readErrorValue());
            case Type::readOperatingData33():
                return catta::modbus::si::response::Response::readOperatingData33(input.readOperatingData33Value());
            case Type::readOperatingData3e():
                return catta::modbus::si::response::Response::readOperatingData3e(input.readOperatingData3eValue());
            case Type::switchOffGridRelay():
                return catta::modbus::si::response::Response::switchOffGridRelay(input.successValue());
            case Type::switchOnGridRelay():
                return catta::modbus::si::response::Response::switchOnGridRelay(input.successValue());
            case Type::forceIdle():
                return catta::modbus::si::response::Response::forceIdle(input.successValue());
            case Type::deactivateIdle():
                return catta::modbus::si::response::Response::deactivateIdle(input.successValue());
            case Type::startConstantVoltage():
                return catta::modbus::si::response::Response::startConstantVoltage(input.successValue());
            case Type::endConstantVoltage():
                return catta::modbus::si::response::Response::endConstantVoltage(input.successValue());
            case Type::setPowerFactor():
                return catta::modbus::si::response::Response::setPowerFactor(input.successValue());
            case Type::controlBatteryInvert():
                return catta::modbus::si::response::Response::controlBatteryInvert(input.successValue());
            case Type::limitBatteryInvert():
                return catta::modbus::si::response::Response::limitBatteryInvert(input.successValue());
            case Type::writeRegister():
                return catta::modbus::si::response::Response::writeRegister(input.writeRegisterValue());
            case Type::value16():
                return catta::modbus::si::response::Response::value16(input.value16Value());
            case Type::value32():
                return catta::modbus::si::response::Response::value32(input.value32Value());
            case Type::value64():
                return catta::modbus::si::response::Response::value64(input.value64Value());
            case Type::string16():
                return catta::modbus::si::response::Response::string16(input.string16Value());
            case Type::string32():
                return catta::modbus::si::response::Response::string32(input.string32Value());
            default:
                return catta::modbus::si::response::Response::empty();
        }
    }();
    if (debug) test.status(catta::tostring::toString(input));
    if (input != output) return test.failedExpected(output, input, "output");
    return true;
}

int main()
{
    using Type = catta::modbus::si::response::Response;
    using Output = catta::test::ConsoleOutput;
    Output output(catta::tostring::GetName<Type>::name.data());
    const auto test_create = checkCreate<Output>;
    const auto test_tofromstring = catta::test::checkToFromString<Output, Type, debug>;
    const auto test_copymove = catta::test::checkCopyMove<Output, Type, catta::test::NO_CHECK>;
    const auto test_tofromjson = catta::test::checkToFromJson<Output, Type, debug>;
    const auto test_tofrommodbus = catta::test::checkToFromModbus<Output, Type, debug>;
    int error = 0;
    if (!catta::test::execute<Output>(test_create, "create", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofromstring, "tofromstring", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_copymove, "copymove", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofromjson, "tofromjson", output, 10000)) error++;
    if (!catta::test::execute<Output>(test_tofrommodbus, "tofrommodbus", output, 10000)) error++;
    return error;
}
