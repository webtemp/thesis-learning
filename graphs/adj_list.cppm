export module adj_list;

import std;
import adj_matrix;

export namespace adj_list{

  std::vector<std::vector<int>> gen_adj_list(int v_size = -1, const bool directed = false, const bool complete = false) {
    if (v_size < 0) v_size = graphs::rand_int(5,100);
    if (v_size > 10000) v_size = 10000;

    std::vector<std::vector<int>> adj(v_size);

    for (int i = 0; i < v_size; i++) {
      for (int j = (directed ? 0 : i + 1); j < v_size; j++) {
        if (i == j) continue;
        if (complete || graphs::rand_int(0, 1) == 1) {
          adj[i].push_back(j);
          if (!directed) {
            adj[j].push_back(i);
          }
        }
      }
    }

    return adj;
  }

  std::vector<std::vector<int>> adj_list() {
    
  }
}
