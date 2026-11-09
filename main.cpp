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
import dijkstra;

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

  auto graph = adj_list::gen_adj_list(10);
  std::println("Graph");
  for (int v = 0; v < std::ssize(graph); v++) {
    std::println("  {}: {}", v, graph[v]);
  }
  std::println();
  std::println("BFS: {}", graphs::bfs(graph, 0));
  std::println("DFS: {}", graphs::dfs(graph, 0));

  auto weighted_graph = adj_list::gen_weighted_adj_list(20, true);
  std::println("Weighted Graph");
  for (int v = 0; v < std::ssize(weighted_graph); v++) {
    std::println("  {}: {}", v, weighted_graph[v]);
  }
  std::println();
  int random_start = graphs::rand_int(0, std::ssize(weighted_graph) - 1);
  std::println("Djikstra from point {} {}", 0, graphs::dijkstra(weighted_graph, 0));
  std::println("Djikstra from random point {} {}", random_start, graphs::dijkstra(weighted_graph, random_start));
}
