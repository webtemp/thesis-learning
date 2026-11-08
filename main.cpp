import std;
import bubble_sort;
import selection_sort;
import insertion_sort;
import counting_sort;
import merge_sort;
import quick_sort;
import shell_sort;
import heap_sort;


import adj_matrix;
import adj_list;
import bfs;
import dfs;

namespace {
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

  //std::vector<std::pair<int,int>> pairs{{0,1}, {0,3}, {1,2}, {1,4}, {3,4}};
  //auto matrix = adj_matrix::adj_matrix(5, pairs, false);
  // auto matrix = graphs::gen_adj_matrix(15, true, false);
  //
  // std::println("Matrix");
  // for (const auto& row : matrix) {
  //   std::println("  {}", row);
  // }

  auto graph = adj_list::gen_adj_list(10);
  std::println("Graph");
  for (int v = 0; v < std::ssize(graph); v++) {
    std::println("  {}: {}", v, graph[v]);
  }
  std::println();
  std::println("BFS: {}", graphs::bfs(graph, 0));
  std::println("DFS: {}", graphs::dfs(graph, 0));
}
