export module shell_sort;

import std;

export namespace sorts {
    template <typename Element, typename Compare = std::less<> >
    void shell_sort(std::span<Element> array, Compare compare = std::less<>{}) {
        const int len = std::ssize(array);
        for (int gap = len/2; gap > 0; gap /= 2) {
            for (int i = gap; i < len; i++ ) {
                Element current_element = array[i];
                int free_slot_index = i;

                while (free_slot_index >= gap && compare(current_element, array[free_slot_index - gap])) {
                    array[free_slot_index] = array[free_slot_index - gap];
                    free_slot_index -= gap;
                }

                array[free_slot_index] = current_element;
            }
        }

    }
}