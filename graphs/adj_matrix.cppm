export module adj_matrix;

import std;

export namespace graphs{

  long long int rand_int(const long long int min, const long long int max) {
    static std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution<long long int> flip(min, max);
    return flip(mt);
  }

  auto gen_adj_matrix(int v_size = -1, const bool directed = false, const bool complete = false) {
    if (v_size < 0) v_size = rand_int(5,100);
    if (v_size > 10000) v_size = 10000;

    std::vector<std::vector<int>> matrix(v_size, std::vector<int>(v_size, 0));

    for (int i=0; i<v_size; i++) {
      for(int j=(directed ? 0 : i+1);j<v_size;j++) {
        if(i == j) continue;
        matrix[i][j] = complete? 1 : rand_int(0,1);
        if(!directed) {
          matrix[j][i] = matrix[i][j];
        }
      }
    }

    return matrix;
  }

  std::vector<std::vector<int>> adj_matrix(const int v_size, std::span<const std::pair<int, int>> pairs, const bool directed = false) {
    std::vector<std::vector<int>> matrix(v_size, std::vector<int>(v_size, 0));

    for (const auto &pair : pairs) {
      matrix[pair.first][pair.second] = 1;
      if (!directed) {
        matrix[pair.second][pair.first] = 1;
      }
    }

    return matrix;
  }
}
