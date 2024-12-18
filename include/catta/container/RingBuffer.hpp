#pragma once

// std
#include <array>

namespace catta
{
namespace container
{
/**
 * @tparam T Type to hold in ringbuffer container.
 * @tparam SIZE Max number of elements.
 * @brief Container to hold number of elements. Does not allocate new memory while using. Can be used for queue stuff (FIFO).
 * @author CattaTech - Maik Urbannek
 */
template <class T, std::size_t SIZE>
class RingBuffer
{
  public:
    /**
     * Constructor.
     */
    [[nodiscard]] constexpr RingBuffer() noexcept : _size(0), _index(0), _buffer() {}
    /**
     * Destructor.
     */
    constexpr ~RingBuffer() noexcept = default;
    /**
     * @param[in] c Element to push at the end.
     * Puts c at the end of the buffer. If the buffer is full the oldest element will be overwritten.
     */
    constexpr void push(const T &c)
    {
        _buffer[(_index + _size) % SIZE] = c;
        if (_size >= SIZE) [[unlikely]]
            _index = (_index + 1) % SIZE;
        else
            _size++;
    }
    /**
     * @return Returns the first (oldest) element.
     * @warning Is only valid if size() is not null.
     */
    [[nodiscard]] constexpr const T &front() const noexcept { return _buffer[_index]; }
    /**
     * Removes first (oldest) element. Checks for empty container (no further check needed).
     */
    constexpr void pop()
    {
        if (_size == 0) [[unlikely]]
            return;
        _index = (_index + 1) % SIZE;
        _size--;
    }
    /**
     * @return Returns number of elements.
     */
    [[nodiscard]] constexpr std::size_t size() const noexcept { return _size; }
    /**
     * @return Returns the buffer size. Is SIZE.
     */
    [[nodiscard]] static constexpr std::size_t maxSize() { return SIZE; }
    /**
     * Move constructor.
     * @param[in,out] other Other ringbuffer. Moves other ringbuffer in this ringbuffer. Other ringbuffer is empty afterwards.
     */
    constexpr RingBuffer(RingBuffer &&other) : _size(other._size), _index(other._index), _buffer(std::move(other._buffer))
    {
        other._size = 0;
        other._index = 0;
    }
    /**
     * Move assigment.
     * @param[in,out] other Other ringbuffer. Moves ringbuffer in this ringbuffer. Other ringbuffer is empty afterwards.
     */
    constexpr void operator=(RingBuffer &&other) noexcept
    {
        _size = other._size;
        _index = other._index;
        _buffer = std::move(other._buffer);
        other._size = 0;
        other._index = false;
    }

  private:
    std::size_t _size;
    std::size_t _index;
    std::array<T, SIZE> _buffer;
};
}  // namespace container
}  // namespace catta
