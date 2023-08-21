#pragma once

#include <cstddef>

namespace cppds {
    template <typename T, std::size_t N>
    class array {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;

        array() = default;

        constexpr inline size_type length() const noexcept {
            return N;
        }

        constexpr inline reference operator[](size_type pos) noexcept {
            return this->m_data[pos];
        }

        constexpr inline const_reference operator[](size_type pos) const noexcept {
            return this->m_data[pos];
        }

    protected:
        value_type m_data[N] {};
    };
}