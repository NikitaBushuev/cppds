#pragma once

namespace cppds {
    template <class _Tp1, class _Tp2>
    class pair {
    public:
        _Tp1 first {};
        _Tp2 second {};

        pair() = default;

        pair(const _Tp1 &first, const _Tp2 &second):
            first(first), second(second) {}
    };
} /* cppds */
