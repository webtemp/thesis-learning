import std;
import bubble_sort;
import selection_sort;
import insertion_sort;
import counting_sort;
import merge_sort;
import quick_sort;
import shell_sort;
import heap_sort;

import adj_list;
import bfs;
import dfs;
import dijkstra;
import graph_types;

template <typename Compare = std::less<> >
static void check_sort(std::string_view name, const std::vector<int>& numbers, const Compare compare = {}) {
  std::string verdict = "CORRECT";
  if (!std::ranges::is_sorted(numbers, compare)) {
    verdict = "WRONG";
  }
  std::println("{} : {}\n{}", name, verdict, numbers);
}

static void check_dijkstra(std::string_view name, const graphs::WeightedAdjacencyList& graph, const graphs::IntVector& expected) {
  const graphs::IntVector distances = graphs::dijkstra(graph, 0);

  if (distances == expected) {
    std::println("{}: CORRECT {}", name, distances);
  } else {
    std::println("{}: WRONG {} expected {}", name, distances, expected);
  }
}

void run_sorts() {
  constexpr std::greater<> DESCENDING{};

  std::mt19937 random{};
  std::uniform_int_distribution<int> pick{-1000000, 1000000};

  std::vector<int> numbers(500);
  for (int& number : numbers) {
    number = pick(random);
  }

  sorts::bubble_sort(std::span{numbers});
  check_sort("Bubble sort", numbers);
  sorts::bubble_sort(std::span{numbers}, DESCENDING);
  check_sort("Bubble sort", numbers, DESCENDING);

  sorts::selection_sort(std::span{numbers});
  check_sort("Selection sort", numbers);
  sorts::selection_sort(std::span{numbers}, DESCENDING);
  check_sort("Selection sort", numbers, DESCENDING);

  sorts::insertion_sort(std::span{numbers});
  check_sort("Insertion sort", numbers);
  sorts::insertion_sort(std::span{numbers}, DESCENDING);
  check_sort("Insertion sort", numbers, DESCENDING);

  sorts::counting_sort(std::span{numbers});
  check_sort("Counting sort", numbers);
  sorts::counting_sort(std::span{numbers}, DESCENDING);
  check_sort("Counting sort", numbers, DESCENDING);

  sorts::merge_sort(std::span{numbers});
  check_sort("Merge sort", numbers);
  sorts::merge_sort(std::span{numbers}, DESCENDING);
  check_sort("Merge sort", numbers, DESCENDING);

  sorts::quick_sort(std::span{numbers});
  check_sort("Quick sort", numbers);
  sorts::quick_sort(std::span{numbers}, DESCENDING);
  check_sort("Quick sort", numbers, DESCENDING);

  sorts::shell_sort(std::span{numbers});
  check_sort("Shell sort", numbers);
  sorts::shell_sort(std::span{numbers}, DESCENDING);
  check_sort("Shell sort", numbers, DESCENDING);

  sorts::heap_sort(std::span{numbers});
  check_sort("Heap sort", numbers);
  sorts::heap_sort(std::span{numbers}, DESCENDING);
  check_sort("Heap sort", numbers, DESCENDING);
}

void run_traversals(const std::size_t graphsize = 10) {
  const graphs::AdjacencyList graph = adj_list::gen_adj_list(graphsize);

  for (int vertex = 0; vertex < std::ssize(graph); vertex++) {
    std::println("{}: {}", vertex, graph[vertex]);
  }
  std::println("BFS: {}", graphs::bfs(graph, 0));
  std::println("DFS: {}", graphs::dfs(graph, 0));
}

void run_dijkstra() {
  // each pair is {to, weight}, start is always vertex 0
  const graphs::WeightedAdjacencyList clrs{
      {{1, 10}, {3, 5}},
      {{2, 1}, {3, 2}},
      {{4, 4}},
      {{1, 3}, {2, 9}, {4, 2}},
      {{0, 7}, {2, 6}},
  };
  check_dijkstra("CLRS graph from book", clrs, {0, 8, 9, 5, 7});

  const graphs::WeightedAdjacencyList airports{
      {{1, 184}, {4, 621}, {5, 946}},
      {{0, 184}, {2, 144}, {3, 187}, {4, 740}, {5, 1090}, {6, 1391}},
      {{1, 144}, {4, 849}},
      {{1, 187}, {4, 867}, {5, 1258}, {7, 2704}},
      {{0, 621}, {1, 740}, {2, 849}, {3, 867}, {6, 802}, {7, 1846}},
      {{0, 946}, {1, 1090}, {3, 1258}, {6, 1121}, {8, 2342}},
      {{1, 1391}, {4, 802}, {5, 1121}, {7, 1464}, {8, 1235}},
      {{3, 2704}, {4, 1846}, {6, 1464}, {8, 337}},
      {{5, 2342}, {6, 1235}, {7, 337}},
  };
  check_dijkstra("Airports", airports, {0, 184, 328, 371, 621, 946, 1423, 2467, 2658});

  const graphs::WeightedAdjacencyList unreachable{{{1, 4}}, {}, {{0, 1}}};
  check_dijkstra("Unreachable vertex", unreachable, {0, 4, graphs::INF});

  const graphs::WeightedAdjacencyList single{{}};
  check_dijkstra("Single vertex", single, {0});

  const graphs::WeightedAdjacencyList zero_weights{{{1, 0}, {2, 5}}, {{2, 0}}, {}};
  check_dijkstra("Zero-weight edges", zero_weights, {0, 0, 0});
}

int main() {
  run_sorts();
  std::println();
  run_traversals();
  std::println();
  run_dijkstra();
}
