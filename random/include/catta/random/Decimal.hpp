#pragma once

// catta
#include <catta/Decimal.hpp>

// random
#include <catta/random/Random.hpp>

template <>
class catta::random::Create<catta::Decimal<std::uint8_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::uint8_t>() const { return _value; }

  private:
    catta::Decimal<std::uint8_t> _value;

    static catta::Decimal<std::uint8_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 2))
            {
                case 0:
                    return random.interval(std::uint8_t(100), std::uint8_t(255));
                case 1:
                    return random.interval(std::uint8_t(10), std::uint8_t(99));
                default:
                    return random.interval(std::uint8_t(0), std::uint8_t(9));
            }
        };
        return catta::Decimal<std::uint8_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::uint16_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::uint16_t>() const { return _value; }

  private:
    catta::Decimal<std::uint16_t> _value;

    static catta::Decimal<std::uint16_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 4))
            {
                case 0:
                    return random.interval(std::uint16_t(10'000), std::uint16_t(65'535));
                case 1:
                    return random.interval(std::uint16_t(1'000), std::uint16_t(9999));
                case 2:
                    return random.interval(std::uint16_t(100), std::uint16_t(999));
                case 3:
                    return random.interval(std::uint16_t(10), std::uint16_t(99));
                default:
                    return random.interval(std::uint16_t(0), std::uint16_t(9));
            }
        };
        return catta::Decimal<std::uint16_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::uint32_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::uint32_t>() const { return _value; }

  private:
    catta::Decimal<std::uint32_t> _value;

    static catta::Decimal<std::uint32_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 9))
            {
                case 0:
                    return random.interval(std::uint32_t(1'000'000'000), std::uint32_t(4'294'967'296));
                case 1:
                    return random.interval(std::uint32_t(100'000'000), std::uint32_t(999'999'999));
                case 2:
                    return random.interval(std::uint32_t(10'000'000), std::uint32_t(99'999'999));
                case 3:
                    return random.interval(std::uint32_t(1'000'000), std::uint32_t(9'999'999));
                case 4:
                    return random.interval(std::uint32_t(100'000), std::uint32_t(999'999));
                case 5:
                    return random.interval(std::uint32_t(10'000), std::uint32_t(99'999));
                case 6:
                    return random.interval(std::uint32_t(1'000), std::uint32_t(9999));
                case 7:
                    return random.interval(std::uint32_t(100), std::uint32_t(999));
                case 8:
                    return random.interval(std::uint32_t(10), std::uint32_t(99));
                default:
                    return random.interval(std::uint32_t(0), std::uint32_t(9));
            }
        };
        return catta::Decimal<std::uint32_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::uint64_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::uint64_t>() const { return _value; }

  private:
    catta::Decimal<std::uint64_t> _value;

    static catta::Decimal<std::uint64_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 19))
            {
                case 0:
                    return random.interval(std::uint64_t(10'000'000'000'000'000'000ull), std::uint64_t(18'446'744'073'709'551'615ull));
                case 1:
                    return random.interval(std::uint64_t(1'000'000'000'000'000'000), std::uint64_t(9'999'999'999'999'999'999ull));
                case 2:
                    return random.interval(std::uint64_t(100'000'000'000'000'000), std::uint64_t(999'999'999'999'999'999));
                case 3:
                    return random.interval(std::uint64_t(10'000'000'000'000'000), std::uint64_t(99'999'999'999'999'999));
                case 4:
                    return random.interval(std::uint64_t(1'000'000'000'000'000), std::uint64_t(9'999'999'999'999'999));
                case 5:
                    return random.interval(std::uint64_t(100'000'000'000'000), std::uint64_t(999'999'999'999'999));
                case 6:
                    return random.interval(std::uint64_t(10'000'000'000'000), std::uint64_t(99'999'999'999'999));
                case 7:
                    return random.interval(std::uint64_t(1'000'000'000'000), std::uint64_t(9'999'999'999'999));
                case 8:
                    return random.interval(std::uint64_t(100'000'000'000), std::uint64_t(999'999'999'999));
                case 9:
                    return random.interval(std::uint64_t(10'000'000'000), std::uint64_t(99'999'999'999));
                case 10:
                    return random.interval(std::uint64_t(1'000'000'000), std::uint64_t(9'999'999'999));
                case 11:
                    return random.interval(std::uint64_t(100'000'000), std::uint64_t(999'999'999));
                case 12:
                    return random.interval(std::uint64_t(10'000'000), std::uint64_t(99'999'999));
                case 13:
                    return random.interval(std::uint64_t(1'000'000), std::uint64_t(9'999'999));
                case 14:
                    return random.interval(std::uint64_t(100'000), std::uint64_t(999'999));
                case 15:
                    return random.interval(std::uint64_t(10'000), std::uint64_t(99'999));
                case 16:
                    return random.interval(std::uint64_t(1'000), std::uint64_t(9999));
                case 17:
                    return random.interval(std::uint64_t(100), std::uint64_t(999));
                case 18:
                    return random.interval(std::uint64_t(10), std::uint64_t(99));
                default:
                    return random.interval(std::uint64_t(0), std::uint64_t(9));
            }
        };
        return catta::Decimal<std::uint64_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::int8_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::int8_t>() const { return _value; }

  private:
    catta::Decimal<std::int8_t> _value;

    static catta::Decimal<std::int8_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 5))
            {
                case 0:
                    return random.interval(std::int8_t(100), std::int8_t(127));
                case 1:
                    return random.interval(std::int8_t(10), std::int8_t(99));
                case 2:
                    return random.interval(std::int8_t(0), std::int8_t(9));
                case 3:
                    return random.interval(std::int8_t(-9), std::int8_t(-1));
                case 4:
                    return random.interval(std::int8_t(-99), std::int8_t(-10));
                default:
                    return random.interval(std::int8_t(-128), std::int8_t(-100));
            }
        };
        return catta::Decimal<std::int8_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::int16_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::int16_t>() const { return _value; }

  private:
    catta::Decimal<std::int16_t> _value;

    static catta::Decimal<std::int16_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 9))
            {
                case 0:
                    return random.interval(std::int16_t(10'000), std::int16_t(32'767));
                case 1:
                    return random.interval(std::int16_t(1'000), std::int16_t(9999));
                case 2:
                    return random.interval(std::int16_t(100), std::int16_t(999));
                case 3:
                    return random.interval(std::int16_t(10), std::int16_t(99));
                case 4:
                    return random.interval(std::int16_t(0), std::int16_t(9));
                case 5:
                    return random.interval(std::int16_t(-9), std::int16_t(-1));
                case 6:
                    return random.interval(std::int16_t(-99), std::int16_t(-10));
                case 7:
                    return random.interval(std::int16_t(-999), std::int16_t(-100));
                case 8:
                    return random.interval(std::int16_t(-9'999), std::int16_t(-1'000));
                default:
                    return random.interval(std::int16_t(-32'768), std::int16_t(-10'000));
            }
        };
        return catta::Decimal<std::int16_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::int32_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::int32_t>() const { return _value; }

  private:
    catta::Decimal<std::int32_t> _value;

    static catta::Decimal<std::int32_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 19))
            {
                case 0:
                    return random.interval(std::int32_t(1'000'000'000), std::int32_t(2'147'483'647));
                case 1:
                    return random.interval(std::int32_t(100'000'000), std::int32_t(999'999'999));
                case 2:
                    return random.interval(std::int32_t(10'000'000), std::int32_t(99'999'999));
                case 3:
                    return random.interval(std::int32_t(1'000'000), std::int32_t(9'999'999));
                case 4:
                    return random.interval(std::int32_t(100'000), std::int32_t(999'999));
                case 5:
                    return random.interval(std::int32_t(10'000), std::int32_t(99'999));
                case 6:
                    return random.interval(std::int32_t(1'000), std::int32_t(9999));
                case 7:
                    return random.interval(std::int32_t(100), std::int32_t(999));
                case 8:
                    return random.interval(std::int32_t(10), std::int32_t(99));
                case 9:
                    return random.interval(std::int32_t(0), std::int32_t(9));
                case 10:
                    return random.interval(std::int32_t(-9), std::int32_t(-1));
                case 11:
                    return random.interval(std::int32_t(-99), std::int32_t(-10));
                case 12:
                    return random.interval(std::int32_t(-999), std::int32_t(-100));
                case 13:
                    return random.interval(std::int32_t(-9'999), std::int32_t(-1'000));
                case 14:
                    return random.interval(std::int32_t(-99'999), std::int32_t(-10'000));
                case 15:
                    return random.interval(std::int32_t(-999'999), std::int32_t(-100'000));
                case 16:
                    return random.interval(std::int32_t(-9'999'999), std::int32_t(-1'000'000));
                case 17:
                    return random.interval(std::int32_t(-99'999'999), std::int32_t(-10'000'000));
                case 18:
                    return random.interval(std::int32_t(-999'999'999), std::int32_t(-100'000'000));
                default:
                    return random.interval(std::int32_t(-2'147'483'648), std::int32_t(-1'000'000'000));
            }
        };
        return catta::Decimal<std::int32_t>(count());
    }
};

template <>
class catta::random::Create<catta::Decimal<std::int64_t>>
{
  public:
    Create(Random& random) : _value(create(random)) {}
    operator catta::Decimal<std::int64_t>() const { return _value; }

  private:
    catta::Decimal<std::int64_t> _value;

    static catta::Decimal<std::int64_t> create(Random& random) noexcept
    {
        const auto count = [&random]()
        {
            switch (random.interval(0, 19))
            {
                case 0:
                    return random.interval(std::int64_t(1'000'000'000'000'000'000), std::int64_t(9'223'372'036'854'775'807));
                case 1:
                    return random.interval(std::int64_t(100'000'000'000'000'000), std::int64_t(999'999'999'999'999'999));
                case 2:
                    return random.interval(std::int64_t(10'000'000'000'000'000), std::int64_t(99'999'999'999'999'999));
                case 3:
                    return random.interval(std::int64_t(1'000'000'000'000'000), std::int64_t(9'999'999'999'999'999));
                case 4:
                    return random.interval(std::int64_t(100'000'000'000'000), std::int64_t(999'999'999'999'999));
                case 5:
                    return random.interval(std::int64_t(10'000'000'000'000), std::int64_t(99'999'999'999'999));
                case 6:
                    return random.interval(std::int64_t(1'000'000'000'000), std::int64_t(9'999'999'999'999));
                case 7:
                    return random.interval(std::int64_t(100'000'000'000), std::int64_t(999'999'999'999));
                case 8:
                    return random.interval(std::int64_t(10'000'000'000), std::int64_t(99'999'999'999));
                case 9:
                    return random.interval(std::int64_t(1'000'000'000), std::int64_t(9'999'999'999));
                case 10:
                    return random.interval(std::int64_t(100'000'000), std::int64_t(999'999'999));
                case 11:
                    return random.interval(std::int64_t(10'000'000), std::int64_t(99'999'999));
                case 12:
                    return random.interval(std::int64_t(1'000'000), std::int64_t(9'999'999));
                case 13:
                    return random.interval(std::int64_t(100'000), std::int64_t(999'999));
                case 14:
                    return random.interval(std::int64_t(10'000), std::int64_t(99'999));
                case 15:
                    return random.interval(std::int64_t(1'000), std::int64_t(9999));
                case 16:
                    return random.interval(std::int64_t(100), std::int64_t(999));
                case 17:
                    return random.interval(std::int64_t(10), std::int64_t(99));
                case 18:
                    return random.interval(std::int64_t(0), std::int64_t(9));
                case 19:
                    return random.interval(std::int64_t(-9), std::int64_t(-1));
                case 20:
                    return random.interval(std::int64_t(-99), std::int64_t(-10));
                case 21:
                    return random.interval(std::int64_t(-999), std::int64_t(-100));
                case 22:
                    return random.interval(std::int64_t(-9'999), std::int64_t(-1'000));
                case 23:
                    return random.interval(std::int64_t(-99'999), std::int64_t(-10'000));
                case 24:
                    return random.interval(std::int64_t(-999'999), std::int64_t(-100'000));
                case 25:
                    return random.interval(std::int64_t(-9'999'999), std::int64_t(-1'000'000));
                case 26:
                    return random.interval(std::int64_t(-99'999'999), std::int64_t(-10'000'000));
                case 27:
                    return random.interval(std::int64_t(-999'999'999), std::int64_t(-100'000'000));
                case 28:
                    return random.interval(std::int64_t(-9'999'999'999), std::int64_t(-1'000'000'000));
                case 29:
                    return random.interval(std::int64_t(-99'999'999'999), std::int64_t(-10'000'000'000));
                case 30:
                    return random.interval(std::int64_t(-999'999'999'999), std::int64_t(-100'000'000'000));
                case 31:
                    return random.interval(std::int64_t(-9'999'999'999'999), std::int64_t(-1'000'000'000'000));
                case 32:
                    return random.interval(std::int64_t(-99'999'999'999'999), std::int64_t(-10'000'000'000'000));
                case 33:
                    return random.interval(std::int64_t(-999'999'999'999'999), std::int64_t(-100'000'000'000'000));
                case 34:
                    return random.interval(std::int64_t(-9'999'999'999'999'999), std::int64_t(-1'000'000'000'000'000));
                case 35:
                    return random.interval(std::int64_t(-99'999'999'999'999'999), std::int64_t(-10'000'000'000'000'000));
                case 36:
                    return random.interval(std::int64_t(-999'999'999'999'999'999), std::int64_t(-100'000'000'000'000'000));
                default:
                    return random.interval(std::int64_t(-9'223'372'036'854'775'808ull), std::int64_t(-1'000'000'000'000'000'000));
            }
        };
        return catta::Decimal<std::int64_t>(count());
    }
};
