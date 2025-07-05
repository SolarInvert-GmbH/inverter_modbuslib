#pragma once

// catta
#include <catta/modbus/si/ReadRegister.hpp>

// random
#include <catta/random/modbus/si/RegisterAddress.hpp>

template <>
class catta::random::Create<catta::modbus::si::ReadRegister>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::modbus::si::ReadRegister() const { return _value; }

  private:
    catta::modbus::si::ReadRegister _value;
    static catta::modbus::si::ReadRegister create(Random& random)
    {
        using A = catta::modbus::si::RegisterAddress;
        static constexpr std::size_t N = []()
        {
            std::size_t result = 0;
            for (std::uint8_t i = 0; i < A::empty(); i++)
                if (A(i).isReadable()) result++;
            return result;
        }();
        static constexpr std::array<A, N> a = []()
        {
            std::array<A, N> result;
            std::size_t r = 0;
            const auto set = [&r, &result](const A v)
            {
                result[r] = v;
                r++;
            };
            for (std::uint8_t i = 0; i < A::empty(); i++)
                if (A(i).isReadable()) set(A(i));
            return result;
        }();
        const auto address = a[random.interval(std::size_t(0), a.size() - 1)];
        return catta::modbus::si::ReadRegister::create(address);
    }
};
