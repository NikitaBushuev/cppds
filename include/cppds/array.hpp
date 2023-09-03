/**
 * @file array.h
 * @brief A fixed-size array container class.
 */

#pragma once

#include <cstddef>              ///< For std::size_t
#include <initializer_list>     ///< For std::initializer_list
#include <stdexcept>            ///< For std::out_of_range exception

namespace cppds {

    /**
     * @brief A fixed-size array container class.
     *
     * This class provides a fixed-size array implementation, similar to std::array.
     * It supports various operations such as assignment, element access, and more.
     *
     * @tparam _Tp The type of elements stored in the array.
     * @tparam _Sz The fixed size of the array.
     */
    template <typename _Tp, std::size_t _Sz>
    class array {
    public:
        using value_type = _Tp;             ///< The type of elements stored in the array.
        using size_type = std::size_t;      ///< The type used for size-related operations.

        /**
         * @brief Default constructor.
         */
        array() = default;

        /**
         * @brief Constructor that initializes the array from a C-style array.
         *
         * @param _array The C-style array to copy elements from.
         */
        array(value_type (&_array)[_Sz]) {
            operator=(_array);
        }

        /**
         * @brief Constructor that initializes the array from an initializer list.
         *
         * @param _list The initializer list to copy elements from.
         */
        array(const std::initializer_list<value_type> &_list) {
            operator=(_list);
        }

        /**
         * @brief Copy constructor.
         *
         * @param _array The array to copy elements from.
         */
        array(const array &_array) {
            operator=(_array);
        }

        /**
         * @brief Destructor.
         */
        ~array() = default;

        /**
         * @brief Assignment operator for C-style arrays.
         *
         * @param _array The C-style array to copy elements from.
         * @return A reference to the modified array.
         */
        array &operator=(value_type (&_array)[_Sz]) {
            for (size_type i = 0; i < size(); ++i) {
                operator[](i) = _array[i];
            }
            return *this;
        }

        /**
         * @brief Assignment operator for initializer lists.
         *
         * @param _list The initializer list to copy elements from.
         * @return A reference to the modified array.
         */
        array &operator=(const std::initializer_list<value_type> &_list) {
            size_type i = 0;
            for (const value_type &value : _list) {
                if (i >= size()) {
                    break;
                }
                operator[](i++) = value;
            }
            return *this;
        }

        /**
         * @brief Assignment operator for copying another array.
         *
         * @param _array The array to copy elements from.
         * @return A reference to the modified array.
         */
        array &operator=(const array &_array) {
            for (size_type i = 0; i < size(); ++i) {
                operator[](i) = _array[i];
            }
            return *this;
        }

        /**
         * @brief Access the underlying data.
         *
         * @return A pointer to the underlying data.
         */
        value_type *data() {
            return _M_data;
        }

        /**
         * @brief Access the underlying data (const version).
         *
         * @return A const pointer to the underlying data.
         */
        const value_type *data() const {
            return _M_data;
        }

        /**
         * @brief Get the size of the array.
         *
         * @return The size of the array.
         */
        size_type size() const {
            return _Sz;
        }

        /**
         * @brief Check if the array is empty.
         *
         * @return True if the array is empty, false otherwise.
         */
        bool empty() const {
            return size() == 0;
        }

        /**
         * @brief Access the last element in the array (const version).
         *
         * @return A const reference to the last element in the array.
         */
        const value_type &back() const {
            return operator[](size() - 1);
        }

        /**
         * @brief Access the last element in the array.
         *
         * @return A reference to the last element in the array.
         */
        value_type &back() {
            return operator[](size() - 1);
        }

        /**
         * @brief Access the first element in the array (const version).
         *
         * @return A const reference to the first element in the array.
         */
        const value_type &front() const {
            return operator[](0);
        }

        /**
         * @brief Access the first element in the array.
         *
         * @return A reference to the first element in the array.
         */
        value_type &front() {
            return operator[](0);
        }

        /**
         * @brief Access an element at a specific index (const version).
         *
         * @param _index The index of the element to access.
         * @return A const reference to the element at the specified index.
         * @throw std::out_of_range if the index is out of range.
         */
        const value_type &at(size_type _index) const {
            if (_index >= size()) {
                throw std::out_of_range("index out of range");
            }
            return operator[](_index);
        }

        /**
         * @brief Access an element at a specific index.
         *
         * @param _index The index of the element to access.
         * @return A reference to the element at the specified index.
         * @throw std::out_of_range if the index is out of range.
         */
        value_type &at(size_type _index) {
            if (_index >= size()) {
                throw std::out_of_range("index out of range");
            }
            return operator[](_index);
        }

        /**
         * @brief Access an element at a specific index (const version).
         *
         * @param _index The index of the element to access.
         * @return A const reference to the element at the specified index.
         */
        const value_type &operator[](size_type _index) const {
            return data()[_index];
        }

        /**
         * @brief Access an element at a specific index.
         *
         * @param _index The index of the element to access.
         * @return A reference to the element at the specified index.
         */
        value_type &operator[](size_type _index) {
            return data()[_index];
        }

    protected:
        value_type _M_data[_Sz]{};   ///< The underlying data storage.
    };

} // namespace cppds
