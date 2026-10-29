import std;
import bubble_sort;
import selection_sort;
import insertion_sort;
import counting_sort;
import merge_sort;
import quick_sort;
import shell_sort;
import heap_sort;

namespace {
  // CHANGED: the parameter is "a vector of Element". The caller passes a std::vector<int>, so Element becomes int.
  // Before it was std::span<Element>, and a std::array or a std::vector is not a span, so Element could not be found.
  template <typename Element>
  void test_sort(std::string_view algorithm_name, const std::vector<Element>& array, auto sort) {
    std::vector<Element> ascending(std::from_range, array);
    std::vector<Element> descending(std::from_range, array);

    sort(std::span{ascending}, std::less<>{});
    sort(std::span{descending}, std::greater<>{});

    const auto ascending_ok = std::ranges::is_sorted(ascending);
    const auto descending_ok = std::ranges::is_sorted(descending, std::greater<>{});

    std::println("{}", algorithm_name);
    std::println("  Ascending  {}  {}", ascending_ok ? "CORRECT" : "WRONG  ", ascending);
    std::println("  Descending {}  {}", descending_ok ? "CORRECT" : "WRONG  ", descending);
    std::println();
  }

}

int main() {
  constexpr int MAX_NUMBERS = 500;
  constexpr int MILLION = 1000000;
  std::mt19937 mt{};
  std::uniform_int_distribution<int> prandom{-MILLION, MILLION};

  std::vector<int> numbers(MAX_NUMBERS);

  for (auto& number : numbers) {
    number = prandom(mt);
  }

  std::println("RANDOMS:\n {}", numbers);

  test_sort("Bubble sort", numbers, [](auto array, auto compare) { sorts::bubble_sort(array, compare); });
  test_sort("Selection sort", numbers, [](auto array, auto compare) { sorts::selection_sort(array, compare); });
  test_sort("Insertion sort", numbers, [](auto array, auto compare) { sorts::insertion_sort(array, compare); });
  test_sort("Counting sort", numbers, [](auto array, auto compare) { sorts::counting_sort(array, compare); });
  test_sort("Merge sort", numbers, [](auto array, auto compare) { sorts::merge_sort(array, compare); });
  test_sort("Quick sort", numbers, [](auto array, auto compare) { sorts::quick_sort(array, compare); });
  test_sort("Shell sort", numbers, [](auto array, auto compare) { sorts::shell_sort(array, compare); });
  test_sort("Heap sort", numbers, [](auto array, auto compare) { sorts::heap_sort(array, compare); });
}
