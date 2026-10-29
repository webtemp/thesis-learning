export module bubble_sort;

import std;

export namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void bubble_sort(std::span<Element> array, Compare compare = std::less<>{}) {
    for (int i = 0; i < std::ssize(array)-1; i++) {
      for (int j = i+1; j < std::ssize(array); j++) {
        if (compare(array[j], array[i])) {
          std::swap(array[i], array[j]);
        }
      }
    }
  }

}

