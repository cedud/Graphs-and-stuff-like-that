# Graph Analysis in C++

## Overview
This project implements a program for analyzing graphs using various algorithms. The program processes multiple graphs from input and determines key properties such as degree sequence, the number of components, bipartiteness, vertex coloring, and subgraph detection.

## Features
The program computes the following parameters for each graph:

1. **Degree sequence** - A sequence representing the degree of each vertex.
2. **Number of components** - Determines the number of connected components in the graph.
3. **Bipartiteness** - Checks if the graph is bipartite.
4. **Vertex coloring**:
   - Greedy algorithm (using vertex order based on its number)
   - LF (Largest First) method
5. **Number of different C4 subgraphs** - Counts the number of cycles of length 4.
6. **Number of edges in the complement graph**

## Input Format
The input consists of multiple graph data sets:
- The first line contains an integer `k`, representing the number of graphs.
- The next `k` sections contain the description of each graph:
  - An integer `n`, the number of vertices in the graph.
  - `n` lines follow, each describing a vertex:
    - The first number is `s`, the number of neighbors.
    - The next `s` numbers are the IDs of the neighboring vertices (ranging from `1` to `n`).

## Output Format
For each graph, the program outputs:

1. Degree sequence (space-separated numbers).
2. Number of components (`T` or `F`).
3. Bipartiteness (`T` or `F`).
4. Vertex coloring:
   - Greedy method sequence.
   - LF method sequence.
5. Number of different C4 subgraphs.
6. Number of edges in the complement graph.

Each result is printed in the order specified above.

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/cedud/Graphs-and-stuff-like-that.git
   cd Graphs-and-stuff-like-that
   ```
2. Compile the project using a C++ compiler:
   ```sh
   g++ -o Graphs-and-stuff-like-that main.cpp
   ```

## Usage
Run the program and provide input via a file or standard input:
```sh
./Graphs-and-stuff-like-that < input.txt
```

## Example
### Input:
```
1
10
7 3 4 5 6 7 8 9
8 3 4 5 6 7 8 9 10
9 1 2 4 5 6 7 8 9 10
9 1 2 3 5 6 7 8 9 10
8 1 2 3 4 6 8 9 10
9 1 2 3 4 5 7 8 9 10
8 1 2 3 4 6 8 9 10
9 1 2 3 4 5 6 7 9 10
9 1 2 3 4 5 6 7 8 10
8 2 3 4 5 6 7 8 9
```
### Output:
```
9 9 9 9 9 8 8 8 8 7 
1
F
1 1 2 3 4 5 4 6 7 8 
6 6 1 2 7 3 7 4 5 8 
473
3
```

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
