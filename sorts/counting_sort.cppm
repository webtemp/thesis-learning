export module counting_sort;

import std;

export namespace sorts {

    template <typename Compare = std::less<> >
    void counting_sort(std::span<int> array, Compare compare = std::less<>{}){
        if (array.empty()) return;
        const int maxvalue = std::ranges::max(array);
        const int minvalue = std::ranges::min(array);// can be negative !

        std::vector<int> output(maxvalue - minvalue + 1);

        for (int i = 0; i < std::ssize(array); i++) {
            output[array[i] - minvalue]++;
        }

        int array_index = 0;
        for (int i = 0; i < std::ssize(output); i++) {
            for (int j = 0; j < output[i]; j++) {
                array[array_index++] = i + minvalue;
            }
        }
        if (compare(1,0)) {
            std::ranges::reverse(array);
        }
    }

}
