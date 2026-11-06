# adj_matrix.cppm — what is happening

## The idea

A graph = vertices (0 .. V-1) and edges (links between them).
An adjacency matrix is a V x V table. Cell `m[i][j]` is 1 if there is an edge
from i to j, else 0.

**First bracket = row = from. Second bracket = column = to.** `m[from][to]`.
`m[1]` is a whole row (a `vector<int>`), `m[1][2]` is one cell in it.

Undirected edge {a, b} = two-way link. Both `m[a][b]` and `m[b][a]` are 1.
The matrix is symmetric.
Directed edge a->b = one arrow. Only `m[a][b]` is 1. `m[b][a]` is a separate edge.

Regions of the matrix:

```
      j=0  j=1  j=2  j=3
i=0 [  D    U    U    U  ]    D = diagonal (i == j)  self-loops, never used
i=1 [  L    D    U    U  ]    U = upper    (j > i)
i=2 [  L    L    D    U  ]    L = lower    (j < i)
i=3 [  L    L    L    D  ]
```

Undirected: each edge {a, b} has exactly one cell in U (smaller index as row).
Visit only U, mirror into L. Directed: U and L are different arrows, visit both.

Worked example, undirected, V = 5, edges (0,1) (0,3) (1,2) (1,4) (3,4):

```
      0  1  2  3  4
 0 [  0  1  0  1  0 ]
 1 [  1  0  1  0  1 ]     row 1 has three 1s -> degree of vertex 1 is 3,
 2 [  0  1  0  0  0 ]     its neighbours are the columns with a 1: 0, 2, 4
 3 [  1  0  0  0  1 ]
 4 [  0  1  0  1  0 ]
```

## rand_int(min, max)

```cpp
static std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<long long int> flip(min, max);
return flip(mt);
```

Two objects replace the old C `srand` / `rand`:
- the **engine** `mt19937` produces random bits. `static` = built and seeded
  once, on the first call, then kept. `random_device{}()` asks the OS for a
  seed so each run differs. Rebuilding it per call would be slow.
- the **distribution** shapes the bits into the range [min, max] without the
  bias of `rand() % n`. It is NOT static: each call has its own range.
  (A static distribution would keep the range of the first call forever.)

Open item: parameters are `long long`, everything that uses it is `int`.

## gen_adj_matrix(v_size, directed, complete)

Random graph. Defaults: random size, undirected, not complete.

```cpp
if (v_size < 0) v_size = rand_int(5,100);    // negative = "pick a size for me"
if (v_size > 10000) v_size = 10000;          // 10000^2 ints = 400 MB, hard cap

std::vector<std::vector<int>> matrix(v_size, std::vector<int>(v_size, 0));
```

V rows, each a row of V zeros. Parentheses, not braces: `vector<int>{V, 0}`
would be a 2-element vector holding V and 0.

```cpp
for (int i = 0; i < v_size; i++) {
  for (int j = (directed ? 0 : i + 1); j < v_size; j++) {
    if (i == j) continue;
```

- i = row = this vertex, j = column = candidate neighbour.
- undirected: j starts at i+1, visits only U. Each pair once.
  (Starting at 0 would visit (1,4) and later (4,1): same pair decided twice,
  the second draw overwrites the first. Still symmetric, but half the work
  is thrown away.)
- directed: j starts at 0, visits U and L. Every arrow gets its own coin.
- `i == j` skip: no self-loops. Only ever fires in the directed case.

```cpp
    matrix[i][j] = complete ? 1 : rand_int(0,1);   // complete = every edge; else coin
    if (!directed) {
      matrix[j][i] = matrix[i][j];                  // mirror: undirected edge is two-way
    }
```

Complete gives all 1s except D. All-ones is symmetric, so directed and
undirected complete graphs print the same.

## adj_matrix(v_size, pairs, directed)

Build from a known edge list.

```cpp
std::vector<std::vector<int>> matrix(v_size, std::vector<int>(v_size, 0));
for (const auto &pair : pairs) {
  matrix[pair.first][pair.second] = 1;
  if (!directed) {
    matrix[pair.second][pair.first] = 1;
  }
}
```

- `v_size` is a parameter on purpose. `pairs.size()` is the number of EDGES,
  not vertices. V=4 with edges (0,1) (2,3) would give a 2x2 matrix and
  `matrix[2][3]` would be out of bounds.
- `pair.first` / `pair.second` are a and b. Same as `for (const auto& [a, b] : pairs)`.
- `std::span` accepts a `std::vector` directly: `adj_matrix(5, edges)`.

## Cost

- memory: V^2 always, even with few edges.
- "is there an edge a-b?": one lookup, O(1).
- "all neighbours of v": scan a row, O(V), even if v has one neighbour.
- good for dense / complete graphs and Floyd-Warshall; bad for sparse graphs.
