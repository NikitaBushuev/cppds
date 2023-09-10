/**
 * @file map.hpp
 * @brief A custom map implementation using open addressing for collision resolution.
 */

#pragma once

#include <cstring>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>

#include "hash.hpp" // Include necessary header(s)

namespace cppds {
    /**
     * @brief A custom map data structure.
     *
     * This map uses open addressing for collision resolution and supports basic operations
     * like insert, erase, contains, clear, size, and empty.
     *
     * @tparam _KTp The type of keys in the map.
     * @tparam _Tp The type of values in the map.
     */
    template <typename _KTp, typename _Tp>
    class map {
    protected:
        using __pair_type = std::pair<_KTp, _Tp>;

    public:
        // Type aliases for clarity
        using key_type = _KTp;
        using value_type = _Tp;
        using size_type = std::size_t;

        /**
         * @brief Default constructor for the map.
         */
        map() = default;

        /**
         * @brief Constructor to initialize the map from an array of key-value pairs.
         *
         * @param _array An array of key-value pairs to initialize the map with.
         * @tparam N The size of the array.
         */
        template <size_type N>
        map(__pair_type (&_array)[N]) {
            operator=(_array);
        }

        /**
         * @brief Constructor to initialize the map from an initializer list of key-value pairs.
         *
         * @param _list An initializer list of key-value pairs to initialize the map with.
         */
        map(const std::initializer_list<__pair_type> &_list) {
            operator=(_list);
        }

        /**
         * @brief Assignment operator to assign key-value pairs from an array.
         *
         * @param _array An array of key-value pairs to assign to the map.
         * @tparam N The size of the array.
         * @return A reference to the modified map.
         */
        template <size_type N>
        map &operator=(__pair_type (&_array)[N]) {
            this->clear();
            for (const __pair_type &pair: _array) {
                this->insert(pair.first, pair.second);
            }
            return *this;
        }

        /**
         * @brief Assignment operator to assign key-value pairs from an initializer list.
         *
         * @param _list An initializer list of key-value pairs to assign to the map.
         * @return A reference to the modified map.
         */
        map &operator=(const std::initializer_list<__pair_type> &_list) {
            this->clear();
            for (const __pair_type &pair: _list) {
                this->insert(pair.first, pair.second);
            }
            return *this;
        }

        /**
         * @brief Destructor to clean up the map.
         */
        ~map() {
            this->clear();
        }

        /**
         * @brief Insert a key-value pair into the map.
         *
         * @param _key The key to insert.
         * @param _value The corresponding value to insert.
         */
        void insert(const key_type &_key, const value_type &_value) {
            // Calculate hash using a custom hash function
            size_type hash = __fnv1hash(&_key, sizeof(_key));

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

            this->_M_kdata[idx] = _key;
            this->_M_vdata[idx] = _value;
            this->_M_hdata[idx] = hash;
        }

        /**
         * @brief Erase a key and its corresponding value from the map.
         *
         * @param _key The key to erase.
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
                this->_M_kdata[idx].~key_type();
                this->_M_vdata[idx].~value_type();
            }
        }

        /**
         * @brief Check if a key exists in the map.
         *
         * @param _key The key to check for.
         * @return `true` if the key exists in the map, `false` otherwise.
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
         * @brief Clear the map, removing all key-value pairs.
         */
        void clear() {
            for (size_type i = 0; i < this->capacity(); ++i) {
                if (this->_M_hdata[i]) {
                    this->_M_kdata[i].~key_type();
                    this->_M_vdata[i].~value_type();
                }
            }

            std::free(this->_M_hdata);
            std::free(this->_M_kdata);
            std::free(this->_M_vdata);

            this->_M_capacity = 0;

            this->_M_hdata = nullptr;
            this->_M_kdata = nullptr;
            this->_M_vdata = nullptr;
        }

        /**
         * @brief Get the size of the map.
         *
         * @return The number of key-value pairs in the map.
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
         * @brief Check if the map is empty.
         *
         * @return `true` if the map is empty, `false` otherwise.
         */
        bool empty() const {
            return this->size() == 0;
        }

    protected:
        /**
         * @brief Get the current capacity of the map.
         *
         * @return The current capacity of the map.
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

            this->_M_kdata = (key_type *)
                std::realloc(this->_M_kdata, _capacity * sizeof(value_type));

            this->_M_hdata = (size_type *)
                std::realloc(this->_M_hdata, _capacity * sizeof(size_type));

            std::memset(this->_M_hdata + old_capacity, 0,
                (_capacity - old_capacity) * sizeof(size_type));

            for (size_t i = 0; i < old_capacity; ++i) {
                if (this->_M_hdata[i]) {
                    this->_M_hdata[i] = 0;
                    this->insert(this->_M_kdata[i], this->_M_vdata[i]);
                }
            }
        }

        size_type *_M_hdata {}; // Array to store hash values
        key_type *_M_kdata {}; // Array to store keys
        value_type *_M_vdata {}; // Array to store values
        size_type _M_capacity {}; // Current capacity of the map
    };
}
