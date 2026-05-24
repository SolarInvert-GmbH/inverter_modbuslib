#pragma once

#include <array>
#include <cstdint>

namespace catta
{

/**
 * @tparam Ampitude The ampitude (half hight) of the sinus function.
 * @tparam Periode The periode (length) of the sinus. Has to be at least 4. If periode is a power of two the sinus function is much mor efficient.
 * @param[in] x The x value.
 * @return Returns sinus with ampitude and periode.
 */
template <std::int32_t Ampitude, std::uint32_t Periode>
constexpr std::int32_t sinus(const std::uint32_t x)
{
    static_assert(Periode >= 4, "Periode has to be at least 4.");
    const std::uint32_t normalized = x % Periode;
    const std::uint32_t qaudrant = (normalized * 4) / Periode;
    const auto cubic = [](const std::uint32_t x)
    {
        const auto lerp = [](const std::uint32_t parameter, const std::uint32_t complement, const std::int32_t a, const std::int32_t b)
        { return (static_cast<std::int32_t>(complement) * a + static_cast<std::int32_t>(parameter) * b) / (static_cast<std::int32_t>(Periode) / 4); };
        const std::uint32_t parameter = x;
        const std::uint32_t complement = Periode / 4 - x;

        static constexpr std::int32_t piOver6 = static_cast<std::int32_t>(3.141592653589793 * static_cast<double>(Ampitude) / 6.0);
        std::array<std::int32_t, 4> t = {0, piOver6, Ampitude, Ampitude};
        for (std::uint32_t r = 1; r <= 3; r++)
            for (std::uint32_t i = 0; i <= 3 - r; i++) t[i] = lerp(parameter, complement, t[i], t[i + 1]);
        return t[0];
    };
    switch (qaudrant)
    {
        case 0:
            return +cubic(normalized);
        case 1:
            return +cubic(Periode / 2 - normalized);
        case 2:
            return -cubic(normalized - Periode / 2);
        default:
            return -cubic(Periode - normalized);
    }
}

/**
 * @tparam Minimum The smallest value of the sinus function. The Minimum has to be smaller than the Maximum.
 * @tparam Maximum The biggest value of the sinus function. The Minimum has to be smaller than the Maximum.
 * @tparam Periode The periode (length) of the sinus. Has to be at least 4. If periode is a power of two the sinus function is much mor efficient.
 * @param[in] x The x value.
 * @return Returns sinus with minimum value and maximum value and periode.
 */
template <std::uint32_t Minimum, std::uint32_t Maximum, std::uint32_t Periode>
constexpr std::uint32_t sinusWindow(const std::uint32_t x)
{
    static_assert(Minimum < Maximum, "The Minimum has to be smaller than the Maximum.");
    static constexpr std::uint32_t Height = Maximum - Minimum;
    static constexpr std::int32_t Ampitude = static_cast<std::int32_t>(Height) / 2;
    static constexpr std::int32_t middle = static_cast<std::int32_t>(Minimum) + Ampitude;
    const std::int32_t value = sinus<Ampitude, Periode>(x);

    return static_cast<std::uint32_t>(value + middle);
}

/**
 * @tparam Periode The periode (length) of the sinus. If periode is a power of two the sinus function is much mor efficient.
 * @param[in] x The x value.
 * @return Returns saw.
 */
template <std::uint32_t Periode>
constexpr std::uint32_t saw(const std::uint32_t x)
{
    return x % Periode;
}

/**
 * @tparam Length The length of a step. Has to be at least 1.
 * @tparam Periode The periode (length) of the sinus. Has to be at least 4. If periode is a power of two the sinus function is much mor efficient.
 * @param[in] x The x value.
 * @return Returns step.
 */
template <std::uint32_t Periode, std::uint32_t Length>
constexpr std::uint32_t step(const std::uint32_t x)
{
    static_assert(Length >= 1, "Length has to be at least 4.");
    return saw<Periode>(x / Length);
}

}  // namespace catta
