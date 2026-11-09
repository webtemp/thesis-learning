export module graph_types;

import std;

export namespace graphs {
    using AdjacencyList = std::vector<std::vector<int>>;
    using WeightedAdjacencyList = std::vector<std::vector<std::pair<int, int>>>;
    using IntVector = std::vector<int>;
    using IntQueue = std::queue<int>;
    using BoolVector = std::vector<bool>;
    using Pair = std::pair<int, int>;
    constexpr int INF = std::numeric_limits<int>::max();
}
