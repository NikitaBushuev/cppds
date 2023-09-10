/**
 * @file set.hpp
 * @brief A custom set implementation using open addressing for collision resolution.
 */

#pragma once

#include <cstring>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>

#include "hash.hpp" // Include necessary header(s)

namespace cppds {
    /**
     * @brief A custom set data structure.
     *
     * This set uses open addressing for collision resolution and supports basic operations
     * like insert, erase, contains, clear, size, and empty.
     *
     * @tparam _Tp The type of elements stored in the set.
     */
    template <typename _Tp>
    class set {
    public:
        // Type aliases for clarity
        using key_type = _Tp;
        using value_type = _Tp;
        using size_type = std::size_t;

        /**
         * @brief Default constructor for the set.
         */
        set() = default;

        /**
         * @brief Constructor to initialize the set from an array.
         *
         * @param _array An array of values to initialize the set with.
         * @tparam N The size of the array.
         */
        template <size_type N>
        set(value_type (&_array)[N]) {
            operator=(_array);
        }

        /**
         * @brief Constructor to initialize the set from an initializer list.
         *
         * @param _list An initializer list of values to initialize the set with.
         */
        set(const std::initializer_list<value_type> &_list) {
            operator=(_list);
        }

        /**
         * @brief Assignment operator to assign values from an array.
         *
         * @param _array An array of values to assign to the set.
         * @tparam N The size of the array.
         * @return A reference to the modified set.
         */
        template <size_type N>
        set &operator=(value_type (&_array)[N]) {
            this->clear();
            for (const value_type &value: _array) {
                this->insert(value);
            }
            return *this;
        }

        /**
         * @brief Assignment operator to assign values from an initializer list.
         *
         * @param _list An initializer list of values to assign to the set.
         * @return A reference to the modified set.
         */
        set &operator=(const std::initializer_list<value_type> &_list) {
            this->clear();
            for (const value_type &value: _list) {
                this->insert(value);
            }
            return *this;
        }

        /**
         * @brief Destructor to clean up the set.
         */
        ~set() {
            this->clear();
        }

        /**
         * @brief Insert a value into the set.
         *
         * @param _value The value to insert.
         */
        void insert(const value_type &_value) {
            // Calculate hash using a custom hash function
            size_type hash = __fnv1hash(&_value, sizeof(_value));

        try_again:
            size_t idx = this->capacity() ? hash % this->capacity() : 0;

            while (idx < this->capacity()
                && this->_M_hdata[idx]
                && this->_M_hdata[idx] != hash) {
                ++idx;
            }

            if (idx >= this->capacity()) {
                if (this->empty()) {
                    this->reserve(1);
                }
                else {
                    this->reserve(this->capacity() * 2);
                }
                goto try_again;
            }

            this->_M_vdata[idx] = _value;
            this->_M_hdata[idx] = hash;
        }

        /**
         * @brief Erase a value from the set.
         *
         * @param _key The value to erase.
         */
        void erase(const key_type &_key) {
            // Calculate hash using a custom hash function
            size_type hash = __fnv1hash(&_key, sizeof(_key));

            size_t idx = this->capacity() ? hash % this->capacity() : 0;

            while (idx < this->capacity()
                && this->_M_hdata[idx]
                && this->_M_hdata[idx] != hash) {
                ++idx;
            }

            if (idx < this->capacity()) {
                this->_M_hdata[idx] = 0;
                this->_M_vdata[idx].~value_type();
            }
        }

        /**
         * @brief Check if a value exists in the set.
         *
         * @param _key The value to check for.
         * @return `true` if the value exists in the set, `false` otherwise.
         */
        bool contains(const key_type &_key) const {
            // Calculate hash using a custom hash function
            size_type hash = __fnv1hash(&_key, sizeof(_key));

            size_t idx = this->capacity() ? hash % this->capacity() : 0;

            while (idx < this->capacity()
                && this->_M_hdata[idx]
                && this->_M_hdata[idx] != hash) {
                ++idx;
            }

            return idx < this->capacity() && this->_M_hdata[idx] == hash;
        }

        /**
         * @brief Clear the set, removing all elements.
         */
        void clear() {
            for (size_type i = 0; i < this->capacity(); ++i) {
                if (this->_M_hdata[i]) {
                    this->_M_vdata[i].~value_type();
                }
            }

            std::free(this->_M_hdata);
            std::free(this->_M_vdata);

            this->_M_capacity = 0;

            this->_M_hdata = nullptr;
            this->_M_vdata = nullptr;
        }

        /**
         * @brief Get the size of the set.
         *
         * @return The number of elements in the set.
         */
        size_type size() const {
            size_type size = 0;

            for (size_type i = 0; i < this->capacity(); ++i) {
                if (this->_M_hdata[i]) {
                    ++size;
                }
            }

            return size;
        }

        /**
         * @brief Check if the set is empty.
         *
         * @return `true` if the set is empty, `false` otherwise.
         */
        bool empty() const {
            return this->size() == 0;
        }

    protected:
        /**
         * @brief Get the current capacity of the set.
         *
         * @return The current capacity of the set.
         */
        size_type capacity() const {
            return this->_M_capacity;
        }

        /**
         * @brief Reserve space for a specified capacity.
         *
         * @param _capacity The new capacity to reserve.
         */
        void reserve(size_type _capacity) {
            if (_capacity < this->capacity()) {
                return;
            }

            size_type old_capacity = this->capacity();

            this->_M_capacity = _capacity;

            this->_M_vdata = (value_type *)
                std::realloc(this->_M_vdata, _capacity * sizeof(value_type));

            this->_M_hdata = (size_type *)
                std::realloc(this->_M_hdata, _capacity * sizeof(size_type));

            std::memset(this->_M_hdata + old_capacity, 0,
                (_capacity - old_capacity) * sizeof(size_type));

            for (size_t i = 0; i < old_capacity; ++i) {
                if (this->_M_hdata[i]) {
                    this->_M_hdata[i] = 0;
                    this->insert(this->_M_vdata[i]);
                }
            }
        }

        size_type *_M_hdata {}; // Array to store hash values
        value_type *_M_vdata {}; // Array to store values
        size_type _M_capacity {}; // Current capacity of the set
    };
}
