export module merge_sort;

import std;

namespace sorts {
  template <typename Element, typename Compare = std::less<> >
  std::vector<Element> merge(std::span<Element> left, std::span<Element> right, Compare compare = std::less<>{}) {
    int i = 0, j = 0;
    std::vector<Element> results;
    results.reserve(std::size(left) + std::size(right));

    while (i < std::ssize(left) && j < std::ssize(right)) {
      if (compare(right[j], left[i])) {
        results.push_back(right[j]);
        j++;
      }
      else {
        results.push_back(left[i]);
        i++;
      }
    }

    results.append_range(left.subspan(i));
    results.append_range(right.subspan(j));

    return results;
  }
}

export namespace sorts {

  template <typename Element, typename Compare = std::less<> >
  void merge_sort(std::span<Element> array, Compare compare = std::less<>{}) {
    const int len = std::ssize(array);
    if (len <= 1) return;
    const int middle = len / 2;

    auto left = array.subspan(0, middle);
    auto right = array.subspan(middle);

    merge_sort(left, compare);
    merge_sort(right, compare);

    std::vector<Element> merge_result = merge(left, right, compare);

    std::ranges::copy(merge_result, array.begin());
  }

}
