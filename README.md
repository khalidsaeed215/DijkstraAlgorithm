# C++ Graph Shortest Path Finder

## Overview

This program, written in C++, is designed to find the shortest path between nodes in a graph using Dijkstra's algorithm. It uses a priority queue to efficiently prioritize the next node to visit, ensuring the shortest path is found from a starting node to all other nodes within the graph. The graph is constructed from a list of edges read from a file, allowing for flexible usage across different datasets.

## Features

- Utilizes Dijkstra's algorithm for shortest path finding.
- Reads graph data from a file to construct the graph.
- Allows user to select a starting node for path finding.
- Outputs the cheapest path and cost from the starting node to all other nodes.

## File Format

The program expects a file named `a5.txt` with the following structure to describe the graph's edges:

- Each line represents an edge in the graph.
- A line consists of three integers separated by spaces:
  - The first integer is the starting node (`from`) of the edge.
  - The second integer is the ending node (`dest`) of the edge.
  - The third integer represents the cost (`cost`) associated with traversing the edge.

Example of file content:
- 1 2 5
- 1 3 10
- 2 4 3
- 3 4 1

This represents edges from node 1 to node 2 with a cost of 5, from node 1 to node 3 with a cost of 10, etc.

## Compilation and Execution

To compile the program, use a C++ compiler such as g++:

```bash
g++ -o ShortestPathFinder ShortestPathFinder.cpp
```

To run the program:

./ShortestPathFinder