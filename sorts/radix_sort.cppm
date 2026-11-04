export module radix_sort;

import std;

namespace sorts {
    void sort_by_digit(std::span<int> array, const int place, const int base) {
        std::vector<std::vector<int> > piles(base);

        int digit;
        for (auto &e : array) {
            digit = (e / place) % base;
            piles[digit].push_back(e);
        }

        int position = 0;
        for (int d = 0; d < base; d++) {
            for (auto &value : piles[d]) {
                array[position] = value;
                position++;
            }
        }
    }
}

export namespace sorts {
    template <typename Compare = std::less<> >
    void radix_sort(std::span<int> array, Compare compare = {}, const int base = 10) {
        const int min_value = std::ranges::min(array);

        for (auto &e : array) {
            e -= min_value;
        }

        const int max_value = std::ranges::max(array);
        int place = 1;

        while (max_value/place > 0) {
            sort_by_digit(array, place, base);
            place *= base;
        }

        for (auto &e : array) {
            e += min_value;
        }

        if (compare(1, 0)) {
            std::ranges::reverse(array);
        }
    }
}
