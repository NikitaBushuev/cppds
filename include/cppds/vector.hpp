#pragma once

#include <cppds/allocator.hpp>

#include <cstring>
#include <utility>
#include <stdexcept>

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

        vector(const std::initializer_list<T> &il) {
            for (const auto &value: il) {
                push_back(value);
            }
        }

        ~vector() {
            clear();
        }

        inline void push_back(const value_type &value) {
            ++this->m_length;

            this->m_data = (pointer)
                this->m_alloc.reallocate(this->m_data, this->m_length);
            
            this->m_data[this->m_length - 1] = value;
        }

        inline void pop_back() {
            if (empty()) {
                return;
            }

            --this->m_length;

            this->m_data[this->m_length].~value_type();

            this->m_data = (pointer)
                m_alloc.reallocate(this->m_data, this->m_length);
        }

        constexpr inline size_type length() const noexcept {
            return this->m_length;
        }

        inline bool empty() const noexcept {
            return not this->m_length;
        }

        inline void clear() {
            while (not this->empty()) {
                this->pop_back();
            }
        }

        inline reference back() {
            return this->operator[](this->m_length - 1);
        }

        inline const_reference back() const {
            return this->operator[](this->m_length - 1);
        }

        constexpr inline reference operator[](size_type pos) {
            if (pos >= this->m_length) {
                throw std::out_of_range("index out of range");
            }
            return this->m_data[pos];
        }

        constexpr inline const_reference operator[](size_type pos) const {
            if (pos >= this->m_length) {
                throw std::out_of_range("index out of range");
            }
            return this->m_data[pos];
        }
    
    protected:
        pointer m_data {};
        size_type m_length {};
        allocator_type m_alloc {};
    };
}