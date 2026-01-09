# 📤 Project 3: Data Structure Implementation (using Graph Algorithm)

## 📘 Overview
    This project aims to implement various graph algorithms based on graph data structures (List Graph and Matrix Graph) and execute them through a command-based system.
    Users can create graphs from input files and perform graph traversals (BFS, DFS), minimum spanning tree construction (Kruskal), shortest path algorithms (Dijkstra, Bellman-Ford, Floyd), as well as a user-defined algorithm (KWANGWOON).

    All functionalities are centrally managed by the GraphManager, and each command follows predefined execution conditions and error-handling rules.

- **LOAD**
    - Applies to: `GraphManager (List Graph / Matrix Graph)`
    - Reads a graph input file and creates a graph in memory.
    
    - Description
        - List Graph: graph is created using an adjacency list
        - Matrix Graph: graph is created using an adjacency matrix
        - Supports both directed and undirected graphs
    
    - Execution Rules
        - LOAD can only be executed when no graph has been created yet
    
    - Error Handling
        - If the file does not exist, or
        - If a graph has already been created  
          → An error code is printed

    - Success Behavior
        - The graph is successfully created in memory
 
- **PRINT**
    - Applies to: `GraphManager`
    - Prints the structure of the graph created by the LOAD command.
    
    - Execution Rules
        - The graph must be loaded before executing PRINT

    - Error Handling
        - If PRINT is executed before a graph is created  
          → An error code is printed

    - Success Behavior
        - Vertex and edge information of the graph is written to the log file

- **BFS**
    - Applies to: `List Graph / Matrix Graph`
    - Arguments
        - Direction (`Y` / `N`)
        - Start Vertex

    - Description
        - Performs Breadth-First Search using a queue
        - Edge weights do not affect traversal order
        - Vertices are visited in ascending order

    - Error Handling
        - If the graph has not been created
        - If the start vertex does not exist or is out of range  
          → An error code is printed

    - Success Behavior
        - BFS traversal order is written to the log file
 
- **DFS**
    - Applies to: `List Graph / Matrix Graph`
    - Arguments
        - Direction (`Y` / `N`)
        - Start Vertex

    - Description
        - Performs Depth-First Search using a stack
        - Larger vertices are pushed first so that smaller vertices are visited earlier

    - Error Handling
        - If the graph has not been created
        - If the start vertex is invalid  
          → An error code is printed

    - Success Behavior
        - DFS traversal path is printed

- **KRUSKAL**
    - Applies to: `Undirected Graph`
    - Constructs a Minimum Spanning Tree (MST) using the Union-Find technique.
      Edges that form cycles are excluded.

    - Sorting Rule
        - Number of edges > 6 → Quick Sort
        - Number of edges ≤ 6 → Insertion Sort

    - Error Handling
        - If the graph has not been created  
          → An error code is printed
         
    - Success Behavior
        - Edges included in the MST and the total cost are printed

- **DIJKSTRA**
    - Applies to: `Directed / Undirected Graph`
    - Arguments
        - Direction (`Y` / `N`)
        - Start Vertex

    - Description
        - Computes the shortest paths from a single start vertex
        - Negative edge weights are not allowed

    - Error Handling
        - If negative edge weights exist
        - If the start vertex is invalid  
          → An error code is printed

    - Success Behavior
        - The shortest distance and path to each vertex are printed

- **BELLMAN-FORD**
    - Applies to: `Directed / Undirected Graph`

    - Arguments
        - Direction (`Y` / `N`)
        - Start Vertex
        - End Vertex

    - Description
        - Computes the shortest path by repeatedly relaxing all edges
        - Supports negative edge weights

    - Error Handling
        - If a negative cycle is detected  
          → An error code is printed

    - Success Behavior
        - The shortest distance and path from the start vertex to the end vertex are printed

- **FLOYD**
    - Applies to: `Directed / Undirected Graph`
    - Executes the Floyd–Warshall algorithm to compute shortest paths
      between all pairs of vertices.

    - Error Handling
        - If a negative cycle exists  
          → An error code is printed

    - Success Behavior
        - The complete distance matrix is printed


- **KWANGWOON**
    - Applies to: `List Graph Only`
    - A user-defined graph traversal algorithm.

    - Description
        - The start vertex is always `1`
        - If the number of adjacent vertices is odd → visit the largest vertex
        - If the number of adjacent vertices is even → visit the smallest vertex
        - A Segment Tree is used to manage visited vertices

    - Success Behavior
        - The traversal path of the KWANGWOON algorithm is printed


- **EXIT**
    - Applies to: `GraphManager`
    - Releases all dynamically allocated memory before program termination.

    - Cleanup Rules
        - Deallocates the Graph object and its internal nodes
        - Sequentially releases all auxiliary data structures

    - Success Behavior
        - Prints a termination message and calls `exit(0)`
      
## 🧾 Conclusion
    이번 프로젝트는 그래프 자료구조의 두 가지 표현 방식(List Graph, Matrix Graph)을 직접 구현하고, 이를 기반으로 다양한 그래프 알고리즘을 명령어 단위로 수행할 수 있도록 설계되었다. BFS와 DFS를 통한 기본 탐색 알고리즘부터, Kruskal을 이용한 MST, Dijkstra·Bellman-Ford·Floyd를 활용한 최단 경로 알고리즘까지 단계적으로 구현함으로써 그래프 알고리즘 전반에 대한 이해를 심화할 수 있었다.

    특히 동일한 알고리즘을 서로 다른 그래프 표현 방식에 적용함으로써, 자료구조 선택에 따른 구현 차이와 성능 특성을 비교·분석할 수 있었다.