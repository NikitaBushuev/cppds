/**
 * @file stack.h
 * @brief A stack container class implemented using a vector.
 */

#pragma once

#include "vector.hpp"           ///< Include the underlying vector implementation.

namespace cppds {

    /**
     * @brief A stack container class implemented using a vector.
     *
     * This class provides a stack implementation using the underlying vector class.
     * It supports stack-specific operations such as push, pop, top, size, empty, and clear.
     *
     * @tparam _Tp The type of elements stored in the stack.
     */
    template <typename _Tp>
    class stack : protected vector<_Tp> {
    public:
        using value_type = typename vector<_Tp>::value_type;    ///< The type of elements stored in the stack.
        using size_type = typename vector<_Tp>::size_type;      ///< The type used for size-related operations.

        /**
         * @brief Default constructor.
         */
        stack() = default;

        /**
         * @brief Constructor that initializes the stack from an initializer list.
         *
         * @param _list The initializer list to copy elements from.
         */
        stack(const std::initializer_list<value_type> &_list) :
            vector<value_type>::vector(_list) {}

        /**
         * @brief Push an element onto the top of the stack.
         *
         * @param _value The value to push onto the stack.
         */
        void push(const value_type &_value) {
            vector<value_type>::push_back(_value);
        }

        /**
         * @brief Pop the top element from the stack.
         */
        void pop() {
            vector<value_type>::pop_back();
        }

        /**
         * @brief Access the top element of the stack.
         *
         * @return A reference to the top element of the stack.
         */
        value_type &top() {
            return vector<value_type>::back();
        }

        /**
         * @brief Get the size of the stack.
         *
         * @return The size of the stack.
         */
        size_type size() const {
            return vector<value_type>::size();
        }

        /**
         * @brief Check if the stack is empty.
         *
         * @return True if the stack is empty, false otherwise.
         */
        bool empty() const {
            return vector<value_type>::empty();
        }

        /**
         * @brief Clear the stack.
         */
        void clear() {
            vector<value_type>::clear();
        }
    };

} // namespace cppds
