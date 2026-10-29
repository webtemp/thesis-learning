export module quick_sort;

import std;

namespace sorts {
  template <typename Element, typename Compare = std::less<> >
  // [3, 1, 2, 5, 4]
  // last_el = 5-1 = 4 (index)
  // pivot = 4, store = 0
  // 3 is less then 4, swap array[i](0) with array[store] (0), store++
  // The same for 1, 2
  // i = 3, store 3
  // Final swap - array[store](val 5, index 3) with array[last_el] last el 4, val 4
  // So array after this is [3, 1, 2 , 4, 5]
  // Store 3, function return 3
  // int pivot = 3
  // auto left = array.subspan(0, 3-1); -> 0, 2 [3, 1, 2]
  // auto right = array.subspan(3 + 1); [5] ?
  int partition(std::span<Element> array, Compare compare = std::less<>{}) {
    const int last_el = std::ssize(array) - 1;
    const Element pivot = array[last_el];
    int store = 0;

    for (int i = 0; i <last_el; i++) {
      if (compare(array[i], pivot)) {
        std::swap(array[i], array[store]);
        store++;
      }
    }

    std::swap(array[store], array[last_el]);

    return store;
  }
}

export namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void quick_sort(std::span<Element> array, Compare compare = std::less<>{}) {
    const int len = std::ssize(array);
    if (len <= 1) return ;

    int pivot = partition(array, compare);
    // SUBSPAN is subspan(OFFSET, COUNT!!!!!)
    auto left = array.subspan(0, pivot);
    auto right = array.subspan(pivot + 1);

    quick_sort(left, compare);
    quick_sort(right, compare);
  }

}
