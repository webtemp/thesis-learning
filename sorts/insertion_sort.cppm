export module insertion_sort;

import std;

export namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void insertion_sort(std::span<Element> array, Compare compare = std::less<>{}) {
    for (int i = 1; i < std::ssize(array); i++) {
      Element current_value = array[i];
      int previous_value_key = i - 1;

      while (previous_value_key >= 0 && compare(current_value, array[previous_value_key])) {
        array[previous_value_key + 1] = array[previous_value_key];
        previous_value_key--;
      }

      array[previous_value_key + 1] = current_value;
    }
  }

}
