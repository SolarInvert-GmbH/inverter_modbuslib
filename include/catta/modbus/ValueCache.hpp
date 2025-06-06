#pragma once

//
#include <catta/modbus/si/request/Request.hpp>
#include <catta/modbus/si/response/Response.hpp>

//
#include <array>
#include <chrono>
#include <functional>
#include <tuple>

namespace catta
{
namespace modbus
{
/**
 * @tparam N Number of cache variables.
 * @brief Class for caching modbus responses.
 *
 * @author CattaTech - Maik Urbannek
 */
template <std::size_t N>
class ValueCache
{
  public:
    /**
     * Response.
     */
    using Response = catta::modbus::si::response::Response;
    /**
     * Request.
     */
    using Request = catta::modbus::si::request::Request;
    /**
     * Callback when new response arrives.
     */
    using Callback = std::function<void(const Response& Response)>;
    /**
     * Constructor.
     */
    ValueCache() noexcept : _data{}, _roundRobin(0)
    {
        for (auto& t : _data)
        {
            std::get<REQUEST_RECEIVED>(t) = std::chrono::microseconds::zero();
            std::get<VALID_TIME>(t) = ALLWAYS_VALID;
        }
    }
    /**
     * @param i The index. Has to be smaller than @b N.
     * @param request The request to send to get value.
     * @warning @b i has to be smaller than @b N.
     */
    void setRequest(const std::size_t i, const Request& request) noexcept { std::get<REQUEST>(_data[i]) = request; }
    /**
     * @param i The index. Has to be smaller than @b N.
     * @param callback The callback that will be executed when new response arrives.
     * @warning @b i has to be smaller than @b N.
     */
    void setCallback(const std::size_t i, const Callback& callback) noexcept { std::get<CALLBACK>(_data[i]) = callback; }
    /**
     * @param i The index. Has to be smaller than @b N.
     * @param validTime The time that the value is valid. After 25% of the time a request will be sent to get the new response. If not set (or max is
     * set), the value will not expirer.
     * @warning @b i has to be smaller than @b N.
     */
    void setValidTime(const std::size_t i, const std::chrono::microseconds validTime) noexcept { std::get<VALID_TIME>(_data[i]) = validTime; }
    /**
     * Invalidates the i-th value.
     * @param i The index. Has to be smaller than @b N.
     * @warning @b i has to be smaller than @b N.
     */
    void setInvalid(const std::size_t i) noexcept
    {
        if (!std::get<RESPONSE>(_data[i]).isEmpty())
        {
            std::get<RESPONSE>(_data[i]) = Response::empty();
            if (std::get<CALLBACK>(_data[i])) std::get<CALLBACK>(_data[i])(Response::empty());
        }
    }
    /**
     * @param i The index. Has to be smaller than @b N.
     * @warning @b i has to be smaller than @b N.
     * @return Returns the last response if valid, otherwise empty.
     */
    const Response& getResponse(const std::size_t i) const noexcept { return std::get<RESPONSE>(_data[i]); }
    /**
     * @param canTakeRequest Wether there is space to send request.
     * @param response The received response.
     * @param request The corresponding request to received response.
     * @param now The current time.
     * @return Returns the request to send.
     */
    Request work(const bool canTakeRequest, const Response& response, const Request& request, const std::chrono::microseconds now) noexcept
    {
        Request send;
        std::size_t newRoundRobin = _roundRobin;
        for (std::size_t i = 0; i < N; i++)
        {
            std::size_t j = (_roundRobin + i) % N;
            Tuple& tuple = _data[j];
            if (request == std::get<REQUEST>(tuple))
            {
                std::get<RESPONSE>(tuple) = response;
                std::get<REQUEST_RECEIVED>(tuple) = now;
                if (std::get<CALLBACK>(tuple)) std::get<CALLBACK>(tuple)(response);
            }
            if (!std::get<RESPONSE>(tuple).isEmpty() && std::get<VALID_TIME>(tuple) != ALLWAYS_VALID &&
                std::get<REQUEST_RECEIVED>(tuple) + std::get<VALID_TIME>(tuple) < now)
            {
                std::get<RESPONSE>(tuple) = Response::empty();
                if (std::get<CALLBACK>(tuple)) std::get<CALLBACK>(tuple)(Response::empty());
            }
            if (canTakeRequest && send.isEmpty() &&
                (std::get<RESPONSE>(tuple).isEmpty() ||
                 (std::get<VALID_TIME>(tuple) != ALLWAYS_VALID && std::get<REQUEST_RECEIVED>(tuple) + std::get<VALID_TIME>(tuple) / 4 < now)))
            {
                send = std::get<REQUEST>(tuple);
                newRoundRobin = (j + 1) % N;
            }
        }
        _roundRobin = newRoundRobin;
        return send;
    }

  private:
    using Tuple = std::tuple<Request, Response, Callback, std::chrono::microseconds, std::chrono::microseconds>;
    std::array<Tuple, N> _data;
    std::size_t _roundRobin;
    static constexpr std::size_t REQUEST = 0;
    static constexpr std::size_t RESPONSE = 1;
    static constexpr std::size_t CALLBACK = 2;
    static constexpr std::size_t REQUEST_RECEIVED = 3;
    static constexpr std::size_t VALID_TIME = 4;
    static constexpr std::chrono::microseconds ALLWAYS_VALID = std::chrono::microseconds::max();
};
}  // namespace modbus
}  // namespace catta
