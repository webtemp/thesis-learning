export module dijkstra;

import std;
import graph_types;
import priority_queue;

export namespace graphs {
  IntVector dijkstra(const WeightedAdjacencyList &graph, const int start) {
    IntVector distances(graph.size(), INF);
    distances[start] = 0;

    PriorityQueue<Pair, std::greater<>> pq;
    pq.push({0, start});// distance to start is 0

    while (!pq.empty()) {
      auto [d, u] = pq.pop();// My implementation of pq returns the item with pop so no need for top();

      if (d > distances[u]) {
        continue;
      }

      for (auto [v, w] : graph[u]) {
        if (distances[u] + w < distances[v]) {
          distances[v] = distances[u] + w;
          pq.push({distances[v], v});
        }
      }
    }

    return distances;
  }
}
