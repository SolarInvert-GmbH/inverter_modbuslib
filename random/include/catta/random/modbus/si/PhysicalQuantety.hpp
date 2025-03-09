#pragma once

// catta
#include <catta/modbus/si/PhysicalQuantety.hpp>

// random
#include <catta/random/Random.hpp>

template <const char* UNIT>
class catta::random::Create<catta::modbus::si::PhysicalQuantety<UNIT>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::PhysicalQuantety<UNIT>() const { return _value; }

  private:
    catta::modbus::si::PhysicalQuantety<UNIT> _value;
    static catta::modbus::si::PhysicalQuantety<UNIT> create(Random& random)
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 21))
            {
                case 0:
                    return random.interval(std::int64_t(10'000'000'000), std::int64_t(99'999'999'999));
                case 1:
                    return random.interval(std::int64_t(1'000'000'000), std::int64_t(9'999'999'999));
                case 2:
                    return random.interval(std::int64_t(100'000'000), std::int64_t(999'999'999));
                case 3:
                    return random.interval(std::int64_t(10'000'000), std::int64_t(99'999'999));
                case 4:
                    return random.interval(std::int64_t(1'000'000), std::int64_t(9'999'999));
                case 5:
                    return random.interval(std::int64_t(100'000), std::int64_t(999'999));
                case 6:
                    return random.interval(std::int64_t(10'000), std::int64_t(99'999));
                case 7:
                    return random.interval(std::int64_t(1'000), std::int64_t(9999));
                case 8:
                    return random.interval(std::int64_t(100), std::int64_t(999));
                case 9:
                    return random.interval(std::int64_t(10), std::int64_t(99));
                case 10:
                    return random.interval(std::int64_t(0), std::int64_t(9));
                case 11:
                    return random.interval(std::int64_t(-9), std::int64_t(-1));
                case 12:
                    return random.interval(std::int64_t(-99), std::int64_t(-10));
                case 13:
                    return random.interval(std::int64_t(-999), std::int64_t(-100));
                case 14:
                    return random.interval(std::int64_t(-9'999), std::int64_t(-1'000));
                case 15:
                    return random.interval(std::int64_t(-99'999), std::int64_t(-10'000));
                case 16:
                    return random.interval(std::int64_t(-999'999), std::int64_t(-100'000));
                case 17:
                    return random.interval(std::int64_t(-9'999'999), std::int64_t(-1'000'000));
                case 18:
                    return random.interval(std::int64_t(-99'999'999), std::int64_t(-10'000'000));
                case 19:
                    return random.interval(std::int64_t(-999'999'999), std::int64_t(-100'000'000));
                case 20:
                    return random.interval(std::int64_t(-9'999'999'999), std::int64_t(-1'000'000'000));
                default:
                    return random.interval(std::int64_t(-99'999'999'999), std::int64_t(-10'000'000'000));
            }
        };
        static constexpr double dfactor = 100'000'000;
        const std::int64_t i = count();
        const double value = double(i) / dfactor;
        return catta::modbus::si::PhysicalQuantety<UNIT>::create(value);
    }
};
