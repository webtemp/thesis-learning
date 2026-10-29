export module heap_sort;

import std;

namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void sift_down_v2(std::span<Element> array, std::size_t parent_index, Compare compare = {}) {
    const std::size_t len = array.size();

    while (parent_index < len / 2) {
      std::size_t largest_index = parent_index;
      const std::size_t left_child = 2 * parent_index + 1;
      const std::size_t right_child = 2 * parent_index + 2;

      if (left_child < len && compare(array[largest_index], array[left_child])) {
        largest_index = left_child;
      }

      if (right_child < len && compare(array[largest_index], array[right_child])) {
        largest_index = right_child;
      }

      if (largest_index == parent_index) {
        break;
      }

      std::swap(array[largest_index], array[parent_index]);
      parent_index = largest_index;
    }
  }

  template <typename Element, typename Compare = std::less<> >
  void sift_down(std::span<Element> array, std::size_t parent_index, Compare compare = {}) {
    std::size_t len = array.size();

    if (parent_index >= len / 2) { // len / 2 -1 is the LAST possible root element
      return;
    }

    std::size_t largest_index = parent_index;
    std::size_t left_child = 2 * parent_index + 1;
    std::size_t right_child = 2 * parent_index + 2;

    if (left_child < len && compare(array[largest_index], array[left_child])) {
      largest_index = left_child;
    }

    if (right_child < len && compare(array[largest_index], array[right_child])) {
      largest_index = right_child;
    }

    if (largest_index != parent_index) {
      std::swap(array[largest_index], array[parent_index]);
      sift_down(array, largest_index, compare); // Continue sifting down from the swapped child's position
    }
  }

  template <typename Element, typename Compare = std::less<> >
  void build_heap(std::span<Element> array, Compare compare = {}) {
    std::size_t parent = array.size() / 2;

    while (parent > 0) {
      parent--; // We do this because std::size_t can do a POSITIVE overflow
      sift_down(array, parent, compare);
    }
  }
}

export namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void heap_sort(std::span<Element> array, Compare compare = {}) {
    build_heap(array, compare);
    constexpr unsigned short TOP_ELEMENT = 0;

    // Start sorting
    std::size_t heap_size = array.size();
    while (heap_size > 1) {
      std::swap(array[TOP_ELEMENT], array[heap_size-1]);
      heap_size--;
      sift_down(array.first(heap_size), TOP_ELEMENT, compare);
    }
  }

}