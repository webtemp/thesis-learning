export module dfs;

import std;
import graph_types;

namespace graphs {
  // Absurd, but if i change visited to be of type BoolVector i get a runtime error "*** stack smashing detected ***: terminated"
  // but with std::vector<bool> it works ...
  void visit(AdjacencyList &graph, const int start, IntVector &order, std::vector<bool> &visited) {
    visited[start] = true;
    order.push_back(start);

    for(auto &neighbour : graph[start]) {
      if (!visited[neighbour]) {
        visit(graph, neighbour, order, visited);
      }
    }
  }
}

export namespace graphs {
  IntVector dfs(AdjacencyList &graph, const int start) {
    IntVector order;
    BoolVector visited (graph.size(), false);

    visit(graph, start, order, visited);

    return order;
  }
}
