#pragma once

#include <cstring>
#include <cstdlib>
#include <initializer_list>
#include <stdexcept>

#include "hash.hpp"

namespace cppds {
    template <typename _Tp>
    class set {
    public:
        using key_type = _Tp;
        using value_type = _Tp;
        using size_type = std::size_t;

        set() = default;

        template <size_type N>
        set(value_type (&_array)[N]) {
            operator=(_array);
        }

        set(const std::initializer_list<value_type> &_list) {
            operator=(_list);
        }

        template <size_type N>
        set &operator=(value_type (&_array)[N]) {
            for (const value_type &value: _array) {
                this->insert(value);
            }
            return *this;
        }

        set &operator=(const std::initializer_list<value_type> &_list) {
            for (const value_type &value: _list) {
                this->insert(value);
            }
            return *this;
        }

        ~set() {
            this->clear();
        }

        void insert(const value_type &_value) {
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

        void erase(const value_type &_value) {
            size_type hash = __fnv1hash(&_value, sizeof(_value));

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

        bool contains(const key_type &_key) const {
            size_type hash = __fnv1hash(&_key, sizeof(_key));

            size_t idx = this->capacity() ? hash % this->capacity() : 0;

            while (idx < this->capacity()
                && this->_M_hdata[idx]
                && this->_M_hdata[idx] != hash) {
                ++idx;
            }

            return idx < this->capacity() && this->_M_hdata[idx] == hash;
        }

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

        size_type size() const {
            size_type size = 0;

            for (size_type i = 0; i < this->capacity(); ++i) {
                if (this->_M_hdata[i]) {
                    ++size;
                }
            }

            return size;
        }

        bool empty() const {
            return this->size() == 0;
        }

    protected:
        size_type capacity() const {
            return this->_M_capacity;
        }

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

        size_type *_M_hdata {};
        value_type *_M_vdata {};
        size_type _M_capacity {};
    };
}