#pragma once

#include <cstdlib>

namespace cppds {
    /**
     * @brief Memory allocator for dynamic memory management.
     * 
     * This class provides a simple memory allocator for allocating and deallocating
     * memory blocks of a specified type.
     * 
     * @tparam T The type of elements for memory allocation.
     */
    template <typename T>
    class allocator {
    public:
        using value_type = T;   ///< The type of elements.
        using size_type = std::size_t;  ///< The type used for size-related operations.
        using pointer = value_type *;   ///< Pointer to allocated memory.

        /**
         * @brief Allocate memory for a specified number of elements.
         * 
         * @param count The number of elements to allocate memory for.
         * @return Pointer to the allocated memory block.
         */
        inline pointer allocate(size_type count) const {
            return (pointer) std::malloc(count * sizeof(value_type));
        }

        /**
         * @brief Reallocate memory for a previously allocated block.
         * 
         * @param ptr Pointer to the previously allocated memory block.
         * @param count The new number of elements to allocate memory for.
         * @return Pointer to the reallocated memory block.
         */
        inline pointer reallocate(pointer ptr, size_type count) const {
            return (pointer) std::realloc(ptr, count * sizeof(value_type));
        }

        /**
         * @brief Deallocate memory for a previously allocated block.
         * 
         * @param ptr Pointer to the memory block to deallocate.
         */
        inline void deallocate(pointer ptr) const {
            std::free(ptr);
        }
    };
}