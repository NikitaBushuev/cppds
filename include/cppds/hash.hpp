#pragma once

#include <cstddef>
#include <cstdint>

namespace cppds {
    size_t __fnv1hash(const void *_data, std::size_t _size) {
        const std::uint32_t __FNV_BASIS32 = 0x811c9dc5u;
        const std::uint32_t __FNV_PRIME32 = 0x01000193u;

        const std::uint8_t *buf = (const std::uint8_t *) _data;

        std::size_t hash = __FNV_BASIS32;

        for (std::size_t i = 0; i < _size; ++i) {
            hash *= __FNV_PRIME32;
            hash ^= (size_t) buf[i];
        }

        return hash;
    }
}