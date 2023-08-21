#pragma once

#include <utility>

namespace cppds {
    /**
     * @brief A fixed-size array template class.
     * 
     * This class provides a simple fixed-size array implementation with compile-time
     * dimensions.
     * 
     * @tparam T The type of elements in the array.
     * @tparam N The number of elements in the array.
     */
    template <typename T, std::size_t N>
    class array {
    public:
        using value_type = T;                    ///< The type of elements in the array.
        using size_type = std::size_t;           ///< The type used for size-related operations.
        using reference = value_type &;          ///< Reference to an element in the array.
        using const_reference = const value_type &; ///< Const reference to an element in the array.
        using pointer = value_type *;            ///< Pointer to an element in the array.
        using const_pointer = const value_type *; ///< Const pointer to an element in the array.

        /**
         * @brief Default constructor.
         * 
         * Constructs an instance of the array with default-initialized elements.
         */
        array() = default;

        /**
         * @brief Constructs an array using values from an initializer list.
         *
         * Initializes the array with values from the provided initializer list.
         *
         * @param il The initializer list containing values to initialize the array.
         */
        array(std::initializer_list<value_type> const& il) {
            size_type i = 0;

            for (const value_type &value: il) {
                if (i >= N) {
                    break;
                }

                m_data[i++] = value;
            }
        }

        /**
         * @brief Get the length of the array.
         * 
         * @return The number of elements in the array.
         */
        constexpr inline size_type length() const noexcept {
            return N;
        }

        /**
         * @brief Access an element in the array by index.
         * 
         * Provides non-const access to the element at the specified index.
         * 
         * @param pos The index of the element to access.
         * @return Reference to the element at the specified index.
         */
        constexpr inline reference operator[](size_type pos) noexcept {
            return this->m_data[pos];
        }

        /**
         * @brief Access an element in the array by index (const version).
         * 
         * Provides const access to the element at the specified index.
         * 
         * @param pos The index of the element to access.
         * @return Const reference to the element at the specified index.
         */
        constexpr inline const_reference operator[](size_type pos) const noexcept {
            return this->m_data[pos];
        }

    protected:
        value_type m_data[N] {}; ///< The storage for array elements.
    };
}
