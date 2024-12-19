// catta
#include <catta/modbus/si/request/Request.hpp>

// random
#include <catta/random/modbus/si/request/Request.hpp>

// fromtostring
#include <catta/fromstring/modbus/si/request/Request.hpp>
#include <catta/tostring/modbus/si/request/Request.hpp>

// json
#include <catta/fromjson/modbus/si/request/Request.hpp>
#include <catta/tojson/modbus/si/request/Request.hpp>

// modbus
#include <catta/frommodbus/modbus/si/request/Request.hpp>
#include <catta/tomodbus/modbus/si/request/Request.hpp>

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
    const auto input = test.random().template create<catta::modbus::si::request::Request>();
    const auto output = [input]()
    {
        using Type = catta::modbus::si::request::Type;
        switch (input.type())
        {
            case Type::readRegister():
                return catta::modbus::si::request::Request::readRegister(input.readRegisterValue());
            case Type::writeRegister():
                return catta::modbus::si::request::Request::writeRegister(input.writeRegisterValue());
            case Type::factoryValues():
                return catta::modbus::si::request::Request::factoryValues();
            case Type::readOperatingData33():
                return catta::modbus::si::request::Request::readOperatingData33();
            case Type::readOperatingData3e():
                return catta::modbus::si::request::Request::readOperatingData3e();
            case Type::switchOffGridRelay():
                return catta::modbus::si::request::Request::switchOffGridRelay();
            case Type::switchOnGridRelay():
                return catta::modbus::si::request::Request::switchOnGridRelay();
            case Type::forceIdle():
                return catta::modbus::si::request::Request::forceIdle();
            case Type::deactivateIdle():
                return catta::modbus::si::request::Request::deactivateIdle();
            case Type::startConstantVoltage():
                return catta::modbus::si::request::Request::startConstantVoltage(input.startConstantVoltageValue());
            case Type::endConstantVoltage():
                return catta::modbus::si::request::Request::endConstantVoltage();
            case Type::setPowerFactor():
                return catta::modbus::si::request::Request::setPowerFactor(input.setPowerFactorValue());
            case Type::controlBatteryInvert():
                return catta::modbus::si::request::Request::controlBatteryInvert(input.controlBatteryInvertValue());
            case Type::limitBatteryInvert():
                return catta::modbus::si::request::Request::limitBatteryInvert(input.limitBatteryInvertValue());
            case Type::readError():
                return catta::modbus::si::request::Request::readError();
            default:
                return catta::modbus::si::request::Request::empty();
        }
    }();
    if (debug) test.status(catta::tostring::toString(input));
    if (input != output) return test.failedExpected(output, input, "output");
    return true;
}

int main()
{
    using Type = catta::modbus::si::request::Request;
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
