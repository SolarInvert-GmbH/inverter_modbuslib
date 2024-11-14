#pragma once

// catta
#include <catta/ConstString.hpp>

// random
#include <catta/random/Random.hpp>

template <std::size_t SIZE>
class catta::random::Create<catta::ConstString<SIZE>>
{
  public:
    Create(Random& random) : _value(catta::ConstString<SIZE>::create(raw(random))) {}
    operator catta::ConstString<SIZE>() const { return _value; }

  private:
    catta::ConstString<SIZE> _value;
    typedef typename ConstString<SIZE>::Raw Raw;
    constexpr static Raw raw(Random& random)
    {
        Raw raw = {};
        for (std::size_t i = 0; i < SIZE; i++) raw[i] = random.ascii();
        return raw;
    }
};
