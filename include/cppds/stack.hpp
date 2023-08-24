#pragma once

#include <cppds/allocator.hpp>
#include <cppds/vector.hpp>

namespace cppds {
    template <typename T, typename Alloc = allocator<T>>
    class stack: protected vector<T, Alloc> {
    public:
        using size_type = typename vector<T, Alloc>::size_type;
        using value_type = typename vector<T, Alloc>::value_type;
        using reference = typename vector<T, Alloc>::reference;

        stack() = default;

        stack(const std::initializer_list<T> &il):
            vector<T, Alloc>::vector(il) {}
        
        inline void push(const value_type &value) {
            vector<T, Alloc>::push_back(value);
        }

        inline void pop() {
            vector<T, Alloc>::pop_back();
        }

        inline reference top() {
            return vector<T, Alloc>::back();
        }

        inline size_type length() const noexcept {
            return vector<T, Alloc>::length();
        }

        inline bool empty() const noexcept {
            return vector<T, Alloc>::empty();
        }

        inline void clear() {
            vector<T, Alloc>::clear();
        }
    };
}