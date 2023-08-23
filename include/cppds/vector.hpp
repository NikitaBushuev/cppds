#pragma once

#include <cppds/allocator.hpp>

#include <cstring>

#include <utility>

namespace cppds {
    template <typename T, typename Alloc = allocator<T>>
    class vector {
    public:
        using value_type = T;
        using size_type = std::size_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using allocator_type = Alloc;

        vector() = default;

        vector(std::initializer_list<T> const& il) {
            for (auto const& value: il) {
                push_back(value);
            }
        }

        ~vector() {
            clear();
        }

        inline void push_back(value_type const& value) {
            ++m_length;
            m_data = m_alloc.reallocate(m_data, m_length);
            m_data[m_length - 1] = value;
        }

        inline void pop_back() {
            if (empty()) {
                return;
            }

            --m_length;
            m_data[m_length].~value_type();
            m_data = m_alloc.reallocate(m_data, m_length);
        }

        inline size_type length() const noexcept {
            return m_length;
        }

        inline bool empty() const noexcept {
            return not m_length;
        }

        inline void clear() {
            while (not empty()) {
                pop_back();
            }
        }

        constexpr inline reference operator[](size_type pos) noexcept {
            return this->m_data[pos];
        }

        constexpr inline const_reference operator[](size_type pos) const noexcept {
            return this->m_data[pos];
        }
    
    protected:
        pointer m_data {};
        size_type m_length {};
        allocator_type m_alloc {};
    };
}