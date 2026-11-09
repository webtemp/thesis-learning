export module heap_sort;

import std;
import heap;

export namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void heap_sort(std::span<Element> array, Compare compare = {}) {
    graphs::build_heap(array, compare);
    constexpr unsigned short TOP_ELEMENT = 0;

    // Start sorting
    std::size_t heap_size = array.size();
    while (heap_size > 1) {
      std::swap(array[TOP_ELEMENT], array[heap_size-1]);
      heap_size--;
      graphs::heap_sift_down(array.first(heap_size), TOP_ELEMENT, compare);
    }
  }

}