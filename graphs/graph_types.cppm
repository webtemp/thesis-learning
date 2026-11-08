export module graph_types;

import std;

export namespace graphs {
    using AdjacencyList = std::vector<std::vector<int>>;
    using IntVector = std::vector<int>;
    using IntQueue = std::queue<int>;
    using BoolVector = std::vector<bool>;
}
