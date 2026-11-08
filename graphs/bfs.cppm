export module bfs;

import std;
import graph_types;

export namespace graphs {
  IntVector bfs(const AdjacencyList &graph, const int start) {
    IntQueue pending;
    IntVector order;
    BoolVector visited(graph.size(), false);

    visited[start] = true;
    pending.push(start);

    while (!pending.empty()) {
      const int top = pending.front();
      pending.pop();
      order.push_back(top);

      for (int n : graph[top]) {
        if (!visited[n]) {
          visited[n] = true;
          pending.push(n);
        }
      }
    }

    return order;
  }
}
