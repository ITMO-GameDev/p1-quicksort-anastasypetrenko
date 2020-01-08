#pragma once

#include <algorithm>

template <typename T, typename Comp>
void sortSlow(const T first, const T last, Comp comp) {
    for (T i = first; i < last; ++i) {
        for (T j = i; j > first; --j) {
            T iterPrev = j - 1;
            auto key = *iterPrev;
            if (comp(*j, key)) {
                std::swap(*j, *(iterPrev));
            }
        }
    }
}

template <typename T, typename Comp>
T anastasy_partition(T first, T last, T pivot, Comp comp) {
    auto pivotVal = *pivot;
    std::swap(*pivot, *--last);
    pivot = last;
    while (first < last) {
        if (comp(*first, pivotVal)) {
            ++first;
        } else {
            std::swap(*first, *--last);
        }
    }
    std::swap(*pivot, *first);
    return first;
}

template <typename T, typename Comp>
void anastasy_sort(T first, T last, Comp comp) {
    while (first < last) {
        auto length = std::distance(first, last);
        if (length < 8) {
            sortSlow(first, last, comp);
            return;
        }

        T pivot = anastasy_partition(first, last, first + length / 2, comp);

        auto lengthBottom = std::distance(first, pivot);
        auto lengthHigh = std::distance(pivot + 1, last);

        if (lengthBottom < lengthHigh) {
            anastasy_sort(first, pivot, comp);
            first = pivot + 1;
        } else {
            anastasy_sort(pivot + 1, last, comp);
            last = pivot - 1;
        }
    }
}
