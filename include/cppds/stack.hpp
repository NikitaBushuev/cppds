#pragma once

#include <cppds/allocator.hpp>
#include <cppds/vector.hpp>

namespace cppds {
    template <typename T, typename Alloc = allocator<T>>
    class stack: protected vector<T, Alloc> {
    public:
        using size_type = typename vector<T, Alloc>::size_type;
        using value_type = typename vector<T, Alloc>::value_type;
        using allocator_type = typename vector<T, Alloc>::allocator_type;

        stack() = default;

        stack(const std::initializer_list<T> &il):
            vector<value_type, allocator_type>::vector(il) {}
        
        inline void push(const value_type &value) {
            vector<value_type, allocator_type>::push_back(value);
        }

        inline void pop() {
            vector<value_type, allocator_type>::pop_back();
        }

        inline value_type &top() {
            return vector<value_type, allocator_type>::back();
        }

        inline size_type length() const noexcept {
            return vector<value_type, allocator_type>::length();
        }

        inline bool empty() const noexcept {
            return vector<value_type, allocator_type>::empty();
        }

        inline void clear() {
            vector<value_type, allocator_type>::clear();
        }
    };
}