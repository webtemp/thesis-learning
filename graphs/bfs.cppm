export module bfs;

import std;

export namespace graphs {
  std::vector<int> bfs(const std::vector<std::vector<int>>& graph, int start) {
    std::queue<int> pending;
    std::vector<bool> discovered(graph.size(), false);
    std::vector<int> order;

    discovered[start] = true;
    pending.push(start);

    while (!pending.empty()) {
      const int top = pending.front();
      pending.pop();
      order.push_back(top);

      for (int n : graph[top]) {
        if (!discovered[n]) {
          discovered[n] = true;
          pending.push(n);
        }
      }
    }

    return order;
  }
}
