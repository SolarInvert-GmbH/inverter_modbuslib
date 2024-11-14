#pragma once

// catta
#include <catta/state/ActiveCloseErrorState.hpp>

// random
#include <catta/random/Random.hpp>

template <class ERROR_TYPE>
class catta::random::Create<catta::state::ActiveCloseErrorState<ERROR_TYPE>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::state::ActiveCloseErrorState<ERROR_TYPE>() const { return _value; }

  private:
    catta::state::ActiveCloseErrorState<ERROR_TYPE> _value;
    constexpr static catta::state::ActiveCloseErrorState<ERROR_TYPE> create(Random& random)
    {
        switch (random.interval(std::uint8_t(0), std::uint8_t(2)))
        {
            case 0:
                return catta::state::ActiveCloseErrorState<ERROR_TYPE>::active();
            case 1:
                return catta::state::ActiveCloseErrorState<ERROR_TYPE>::closed();
            default:
                return catta::state::ActiveCloseErrorState<ERROR_TYPE>::error(Create<ERROR_TYPE>(random));
        }
    }
};
