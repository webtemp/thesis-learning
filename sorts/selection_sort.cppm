export module selection_sort;

import std;

export namespace sorts {
    template <typename Element, typename Compare = std::less<> >
    void selection_sort(std::span<Element> array, Compare compare = std::less<>{}) {
        for (int i = 0; i < std::ssize(array)-1; i++) {
            int tmp_key = i;
            for (int j = i+1; j < std::ssize(array); j++) {
                if (compare(array[j], array[tmp_key])) {
                    tmp_key = j;
                }
            }
            // array[tmp_key] always holds the smallest/greates even if it's equal to array[i] so do the sway anyway.
            std::swap(array[tmp_key], array[i]);
        }
    }
}