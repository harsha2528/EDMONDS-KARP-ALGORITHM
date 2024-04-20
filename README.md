# EDMONDS-KARP-ALGORITHM

## Overview
The Edmonds-Karp algorithm is a popular method for finding the maximum flow in a flow network. It efficiently determines the maximum amount of flow that can be sent from a source node to a sink node in a directed graph with capacities on the edges. This algorithm is based on augmenting paths found using breadth-first search (BFS) in the residual graph of the network.

## Features
- Finds the maximum flow in a flow network.
- Utilizes the residual graph to efficiently update flow capacities.
- Guarantees correctness and optimality in determining maximum flow.

## Usage
1. **Input**: The algorithm requires input in the form of a directed graph with edge capacities. The graph can be represented using an adjacency list or an adjacency matrix.
2. **Initialization**: Initialize the residual graph and auxiliary data structures.
3. **Algorithm Execution**: Execute the Edmonds-Karp algorithm to find the maximum flow in the flow network.
4. **Output**: Retrieve the maximum flow value and flow distribution across edges.

## Complexity
- Time Complexity: O(VE^2), where V is the number of vertices and E is the number of edges in the graph.
- Space Complexity: O(V^2) due to the storage of the graph and auxiliary data structures.

## Applications
- Network flow optimization
- Transportation planning
- Network routing
- Assignment and scheduling problems

## References
- [Introduction to Algorithms (CLRS)](https://en.wikipedia.org/wiki/Introduction_to_Algorithms)
- [Edmonds-Karp Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm)

## License
This project is licensed under the [MIT License](LICENSE).
