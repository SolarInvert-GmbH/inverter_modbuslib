#pragma once

// catta
#include <catta/FixedPointNumber.hpp>

// random
#include <catta/random/Decimal.hpp>

template <std::uint8_t DECIMAL_PLACES>
class catta::random::Create<catta::FixedPointNumber<DECIMAL_PLACES>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::FixedPointNumber<DECIMAL_PLACES>() const { return _value; }

  private:
    catta::FixedPointNumber<DECIMAL_PLACES> _value;

    static catta::FixedPointNumber<DECIMAL_PLACES> create(Random& random) noexcept
    {
        const std::int64_t n = static_cast<std::int64_t>(random.create<catta::Decimal<std::int64_t>>());
        return catta::FixedPointNumber<DECIMAL_PLACES>::create(n);
    }
};
