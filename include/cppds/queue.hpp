#pragma once

#include "vector.hpp"

namespace cppds {
    template <typename _Tp>
    class queue : protected vector<_Tp> {
    public:
        using value_type = typename vector<_Tp>::value_type;    ///< The type of elements stored in the queue.
        using size_type = typename vector<_Tp>::size_type;      ///< The type used for size-related operations.

        using vector<_Tp>::back;
        using vector<_Tp>::front;

        using vector<_Tp>::size;
        using vector<_Tp>::empty;

        using vector<_Tp>::clear;

        /**
         * @brief Default constructor.
         */
        queue() = default;

        /**
         * @brief Constructor that initializes the queue from an initializer list.
         *
         * @param _list The initializer list to copy elements from.
         */
        queue(const std::initializer_list<value_type> &_list) :
            vector<value_type>::vector(_list) {}

        /**
         * @brief Push an element onto the top of the queue.
         *
         * @param _value The value to push onto the queue.
         */
        void push(const value_type &_value) {
            vector<value_type>::push_back(_value);
        }

        /**
         * @brief Pop the first element from the queue.
         */
        void pop() {
            vector<value_type>::pop_front();
        }
    };
}