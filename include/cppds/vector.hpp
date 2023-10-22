/**
 * @file vector.h
 * @brief A dynamic array (vector) container class.
 */

#pragma once

#include <cstdlib>              ///< For and std::malloc, std::realloc and std::free
#include <initializer_list>     ///< For std::initializer_list
#include <stdexcept>            ///< For std::out_of_range exception

#include "pair.hpp"

namespace cppds {

    /**
     * @brief A dynamic array (vector) container class.
     *
     * This class provides a dynamic array implementation, similar to std::vector.
     * It supports various operations such as assignment, resizing, insertion, removal, and more.
     *
     * @tparam T The type of elements stored in the vector.
     */
    template <typename T>
    class vector {
    public:
        using value_type = T;             ///< The type of elements stored in the vector.
        using size_type = std::size_t;    ///< The type used for size-related operations.

        /**
         * @brief Default constructor.
         */
        vector() = default;

        /**
         * @brief Constructor that initializes the vector from a C-style array.
         *
         * @tparam N The size of the C-style array.
         * @param _array The C-style array to copy elements from.
         */
        template <size_type N>
        vector(value_type (&_array)[N]) {
            operator=(_array);
        }

        /**
         * @brief Constructor that initializes the vector from a C-style pointer.
         *
         * @param _pointer The C-style pointer to copy elements from.
         * @param _size The size of the C-style pointer.
         */
        vector(const value_type *_pointer, size_type _size) {
            operator=(pair<const value_type *, size_type>(_pointer, _size));
        }

        /**
         * @brief Constructor that initializes the vector from an initializer list.
         *
         * @param _list The initializer list to copy elements from.
         */
        vector(const std::initializer_list<value_type> &_list) {
            operator=(_list);
        }

        /**
         * @brief Copy constructor.
         *
         * @param _vector The vector to copy elements from.
         */
        vector(const vector<value_type> &_vector) {
            operator=(_vector);
        }

        /**
         * @brief Destructor. Clears the vector and frees memory.
         */
        ~vector() {
            clear();
        }

        /**
         * @brief Assignment operator for C-style arrays.
         *
         * @tparam N The size of the C-style array.
         * @param _array The C-style array to copy elements from.
         * @return A reference to the modified vector.
         */
        template <size_type N>
        vector &operator=(value_type (&_array)[N]) {
            clear();

            for (const value_type &value : _array) {
                push_back(value);
            }

            return *this;
        }

        /**
         * @brief Assignment operator for C-style pointers.
         *
         * @param _pair The pair of pointer and its size
         * @return A reference to the modified vector.
         */
        vector &operator=(const pair<const value_type *, size_type> &_pair) {
            const value_type *_pointer = _pair.first;

            size_type _size = _pair.second;

            clear();

            for (size_type i = 0; i < _size; ++i) {
                push_back(_pointer[i]);
            }

            return *this;
        }

        /**
         * @brief Assignment operator for initializer lists.
         *
         * @param _list The initializer list to copy elements from.
         * @return A reference to the modified vector.
         */
        vector &operator=(const std::initializer_list<value_type> &_list) {
            clear();

            for (const value_type &value : _list) {
                push_back(value);
            }

            return *this;
        }

        /**
         * @brief Assignment operator for copying another vector.
         *
         * @param _vector The vector to copy elements from.
         * @return A reference to the modified vector.
         */
        vector &operator=(const vector<value_type> &_vector) {
            clear();

            for (size_type i = 0; i < _vector.size(); ++i) {
                push_back(_vector[i]);
            }

            return *this;
        }

        /**
         * @brief Resize the vector to the specified size.
         *
         * @param _size The new size of the vector.
         */
        void resize(size_type _size) {
            size_type old_size = size();

            _M_size = _size;

            if (_size == 0) {
                free(_M_data);

                _M_data = nullptr;
                _M_size = 0;
            } else {
                _M_data = (value_type *)
					realloc(_M_data, _size * sizeof(value_type));

                for (size_type i = _size; i < old_size; ++i) {
                    _M_data[i].~value_type();
                }
            }
        }

        /**
         * @brief Clear the vector (set size to 0).
         */
        void clear() {
            resize(0);
        }

        /**
         * @brief Insert an element at the specified index.
         *
         * @param _index The index at which to insert the element.
         * @param _value The value to insert.
         */
        void insert(size_type _index, const value_type &_value) {
            resize(size() + 1);

            for (size_type i = _index; i < size() - 1; ++i) {
                operator[](i + 1) = operator[](i);
            }

            operator[](_index) = _value;
        }

        /**
         * @brief Erase an element at the specified index.
         *
         * @param _index The index of the element to erase.
         */
        void erase(size_type _index) {
            operator[](_index).~value_type();

            for (size_type i = _index; i < size() - 1; ++i) {
                operator[](i) = operator[](i + 1);
            }

            resize(size() - 1);
        }

        /**
         * @brief Add an element to the back of the vector.
         *
         * @param _value The value to add.
         */
        void push_back(const value_type &_value) {
            insert(size(), _value);
        }

        /**
         * @brief Add an element to the front of the vector.
         *
         * @param _value The value to add.
         */
        void push_front(const value_type &_value) {
            insert(0, _value);
        }

        /**
         * @brief Remove the last element from the vector.
         */
        void pop_back() {
            erase(size() - 1);
        }

        /**
         * @brief Remove the first element from the vector.
         */
        void pop_front() {
            erase(0);
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
         * @brief Get the size of the vector.
         *
         * @return The size of the vector.
         */
        size_type size() const {
            return _M_size;
        }

        /**
         * @brief Check if the vector is empty.
         *
         * @return True if the vector is empty, false otherwise.
         */
        bool empty() const {
            return size() == 0;
        }

        /**
         * @brief Access the last element in the vector (const version).
         *
         * @return A const reference to the last element in the vector.
         */
        const value_type &back() const {
            return operator[](size() - 1);
        }

        /**
         * @brief Access the last element in the vector.
         *
         * @return A reference to the last element in the vector.
         */
        value_type &back() {
            return operator[](size() - 1);
        }

        /**
         * @brief Access the first element in the vector (const version).
         *
         * @return A const reference to the first element in the vector.
         */
        const value_type &front() const {
            return operator[](0);
        }

        /**
         * @brief Access the first element in the vector.
         *
         * @return A reference to the first element in the vector.
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
        value_type *_M_data {};  ///< The underlying data storage.
        size_type _M_size {};    ///< The size of the vector.
    };

} // namespace cppds
