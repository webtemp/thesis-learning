# adj_list.cppm — what is happening

## The idea

An adjacency list stores, for every vertex, the list of its neighbours.
Only edges that exist are stored. There are no cells for "no edge".

Same undirected graph as the matrix, V = 5, edges (0,1) (0,3) (1,2) (1,4) (3,4):

```
0: [1, 3]
1: [0, 2, 4]       <- compare matrix row 1 = [1, 0, 1, 0, 1]:
2: [1]                the list is the positions of the 1s
3: [0, 4]
4: [1, 3]
```

The value stored is a VERTEX ID (a neighbour), not a 0/1 flag.
Each undirected edge appears twice: (0,1) puts 1 in list 0 and 0 in list 1.

Reading it:
- neighbours of v: `adj[v]`, directly.
- degree of v: `adj[v].size()`.
- is a connected to b: search `adj[a]` for b. O(degree), slower than the matrix.

## Header

```cpp
export module adj_list;
import std;
import adj_matrix;      // for graphs::rand_int
```

## gen_adj_list(v_size, directed, complete)

Same three parameters and same defaults as gen_adj_matrix.

```cpp
std::vector<std::vector<int>> adj(v_size);
```

V inner vectors, all EMPTY. Difference 1 from the matrix: the matrix had V rows
of V zeros. A list starts at length 0 and grows only when an edge is added.
That is why `adj[i][j] = ...` crashes: position j does not exist yet.
Lists grow with `push_back`, never by index.

```cpp
for (int i = 0; i < v_size; i++) {
  for (int j = (directed ? 0 : i + 1); j < v_size; j++) {
    if (i == j) continue;
```

Identical to the matrix. i = this vertex, j = candidate neighbour.
Undirected visits only j > i (each pair once). Directed visits all j.
No self-loops.

```cpp
    if (complete || graphs::rand_int(0, 1) == 1) {
```

Difference 2: the matrix wrote a 1 or a 0 on every visit. A list has no cell
for "no edge", so when the coin says no we write NOTHING.
`complete ||` short-circuits: if complete, the coin is never flipped.

```cpp
      adj[i].push_back(j);        // was: matrix[i][j] = 1
      if (!directed) {
        adj[j].push_back(i);      // was: matrix[j][i] = matrix[i][j]
      }
    }
```

"Vertex i now has neighbour j." The value pushed is j itself.
Mirror for undirected: j also gets i. Same rule as the matrix, written for a list.

```cpp
return adj;     // moved out, no copy
```

Why this loop and not "random count of random ids": random ids give
self-loops (i itself) and duplicates (same neighbour twice). The per-pair
coin loop avoids both for free, exactly like the matrix.

## Matrix vs list

| | matrix | list |
|---|---|---|
| memory | V^2 always | V + 2E (undirected) |
| edge a-b exists? | O(1) | O(degree of a) |
| all neighbours of v | O(V) | O(degree of v) |
| good for | dense / complete graphs | sparse graphs, BFS/DFS/Dijkstra |

## Flat variants (for later)

- flat MATRIX: one `vector<int>` of V*V, cell (i,j) at `m[i*V + j]`. Still a
  matrix, still V^2 memory.
- CSR (compressed sparse row) LIST: all lists glued into one array `adj`
  plus `offset` of size V+1. Neighbours of v are `adj[offset[v] .. offset[v+1])`,
  degree is `offset[v+1] - offset[v]`. One memory block, fast to walk, cannot
  add edges after building.
