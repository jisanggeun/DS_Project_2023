#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph* graph, char option, int vertex, ofstream *fout) {
    // Check if the starting vertex is valid
    if (vertex >= graph->getSize()) return false; 

    // Initialize
    queue<int> queue;
    map<int, int> adjacentNodes;
    int* visited = new int[graph->getSize()] {0}; 
    visited[vertex] = 1;

    *fout << "========== BFS ============" << endl;
    *fout << (option == 'Y' ? "Directed Graph BFS result" : "Undirected Graph BFS result") << endl;
    *fout << "startvertex: " << vertex << endl;

    // Enqueue the starting vertex and begin BFS traversal
    queue.push(vertex);

    while(!queue.empty()) {
        // Process the front vertex of the queue
        int frontValue = queue.front();
        graph->getAdjacentEdges(frontValue, &adjacentNodes);
        queue.pop(); // Pop
        *fout << frontValue;

        // Explore adjacent vertices
        for (auto& adjacent : adjacentNodes) {
            if (!visited[adjacent.first]) { // first = vertex, second = weight
                queue.push(adjacent.first); // push the adjacent vertex
                visited[adjacent.first] = 1; // Mark the adjacent vertex as visited
            }
        }
        if (!queue.empty()) *fout << " -> "; 
    }
    *fout << endl << "==========================" << endl << endl;
    // Deallocate memory used for the visited
    delete[] visited; 
    // Return
    return true;
}

bool DFS(Graph* graph, char option, int vertex, ofstream* fout) {
    // Check if the starting vertex is valid
    if (vertex >= graph->getSize()) return false;

    // Initialize
    stack<int> stack;
    map<int, int> adjacentNodes;
    int* visited = new int[graph->getSize()] {0};
    visited[vertex] = 1; // Mark the starting vertex as visited

    *fout << "========== DFS ============" << endl;
    *fout << (option == 'Y' ? "Directed Graph DFS result" : "Undirected Graph DFS result") << endl;
    *fout << "startvertex: " << vertex << endl;

    // Push the starting vertex onto the stack and begin DFS traversal
    stack.push(vertex);

    while (!stack.empty()) {
        // Process the top vertex of the stack
        int endValue = stack.top();
        graph->getAdjacentEdges(endValue, &adjacentNodes);
        stack.pop();
        *fout << endValue;

        // Explore adjacent vertices in reverse order
        for (auto iter = adjacentNodes.rbegin(); iter != adjacentNodes.rend(); ++iter) {
            if (!visited[iter->first]) { // first = vertex, second = weight
                stack.push(iter->first); // Push the adjacent vertex onto the stack
                visited[iter->first] = 1; // Mark the adjacent vertex as visited
            }
        }
        if (!stack.empty()) *fout << " -> ";
    }
    *fout << endl << "==========================" << endl << endl;

    // Deallocate memory used for the visited
    delete[] visited;

    // Return
    return true;
 }

bool Kruskal(Graph* graph, ofstream* fout) {
    if(graph == nullptr) return false;
    
    int size = graph->getSize();
    int k = 1;
    int cost = 0;
    int check_neg = 0;
    int edgesAdded = 0;
    

    int parent[size];
    int distance[size][size];
    int p_weight[size][size];
    int l_weight[size * size] = { 0 };

    // initialize
    for (int i = 1; i < size; ++i) {
        parent[i] = -1;
        for (int j = 1; j < size; ++j) {
            distance[i][j] = 0;
            p_weight[i][j] = 0;
        }
    }

    // Fill the distance matrix with edge weights from the graph
    for (int i = 1; i < size; ++i) {
        map<int, int> adjacentNodes;
        graph->getAdjacentEdges(i, &adjacentNodes);

        for (auto iter = adjacentNodes.begin(); iter != adjacentNodes.end(); ++iter) {
            int adjacentVertex = iter->first;
            int adjacentWeight = iter->second;

            distance[i][iter->first] = adjacentWeight;

            if (distance[adjacentVertex][i] == distance[i][adjacentVertex]) distance[i][adjacentVertex] = 0;
            else if (distance[i][adjacentVertex] > distance[adjacentVertex][i] && distance[adjacentVertex][i] != 0) distance[i][adjacentVertex] = 0;
            else if (distance[i][adjacentVertex] < distance[adjacentVertex][i] && distance[i][adjacentVertex] != 0) distance[adjacentVertex][i] = 0;
        }
    }
    // Populate the l_weight array with unique edge weights
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            if (distance[i][j] != 0) l_weight[k++] = distance[i][j];
        }
    }
    // Sort the l_weight array using QuickSort algorithm
    QuickSort(l_weight, 1, k - 1);

    // Iterate through sorted edge weights
    for (int i = 1; i < k; ++i) {
        int nextEdgeWeight = l_weight[i];

        // Find the endpoints of the edge in the original graph
        for (int u = 1; u < size; ++u) {
            for (int v = 1; v < size; ++v) {
                if (distance[u][v] == nextEdgeWeight) {
                    int setU = findSet(u, parent);
                    int setV = findSet(v, parent);

                    // Check if adding the edge creates a cycle
                    if (setU != setV) {
                        // Include the edge in the minimum spanning tree
                        unionSets(setU, setV, parent);
                        p_weight[u][v] = nextEdgeWeight;

                        ++edgesAdded;
                        if (edgesAdded == size - 1)
                            break;
                    }
                }
            }
        }
    }

    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            if (p_weight[i][j] != 0) p_weight[j][i] = p_weight[i][j];
        }
    }

    *fout << "========== Kruskal ============" << endl;
    for (int i = 1; i < size; ++i) {
        *fout << "[" << i << "]" << "\t";
        for (int j = 1; j < size; ++j) {
            if (p_weight[i][j] != 0) {
                *fout << j << "(" << p_weight[i][j] << ") ";
                cost = cost + p_weight[i][j];
            }
        }
        *fout << endl;
    }
    cost = cost / 2;

    // Output the total cost of the minimum spanning tree
    *fout << "cost: " << cost << endl;
    *fout << "==========================" << endl << endl;
    return true;
}

bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout) {
   if (vertex > graph->getSize() - 1 || vertex < 1) return false;

    int* distance = new int[graph->getSize()];
    int* visit = new int[graph->getSize()];
    int* path = new int[graph->getSize()];

   // Initialize arrays for Dijkstra's algorithm
    for (int i = 1; i < graph->getSize(); i++) {
        distance[i] = 0;
        visit[i] = 0;
        path[i] = -1;
    }

    stack<int> s;
    s.push(vertex);
    int back_value;

    while (!s.empty()) {
        back_value = s.top();
        visit[back_value] = 1;
        s.pop();

        // Iterate through connected vertices
        for (int i = 1; i < graph->getSize(); i++) {
            if (i != back_value && graph->connectVertex(back_value, i) == true && i != vertex) {
                // Check if first time visiting
                if (visit[i] == 0) {
                    s.push(i);
                }
                // Update distance and path if a shorter path is found
                if ((distance[i] != 0 && distance[i] > (distance[back_value] + graph->getWeight(back_value, i))) || distance[i] == 0) {
                    distance[i] = distance[back_value] + graph->getWeight(back_value, i);
                    path[i] = back_value;
                }
            }
        }
    }

    *fout << "====== Dijkstra =======" << endl;
    *fout << (option == 'Y' ? "Directed Graph Dijkstra result" : "Undirected Graph Dijkstra result") << endl;
    *fout << "startvertex: " << vertex << endl;

    int find_back_value;
    // Print Dijkstra's algorithm result
    for (int i = 1; i < graph->getSize(); i++) {
        if (i == vertex) continue; 
        *fout << "[" << i << "] ";
        find_back_value = i;
        stack<int> s;
        while (1) {
            if (path[find_back_value] == -1)  break;
            s.push(path[find_back_value]);
            find_back_value = path[find_back_value];
        }
        if (s.empty()) {
            *fout << "x" << endl;
            continue;
        }
        while (!s.empty()) {
            *fout << s.top() << " -> ";
            s.pop();
        }

        *fout << i << " (" << distance[i] << ")" << endl;
    }

    // Output footer information to the file stream
    *fout << "==========================" << endl << endl;

    // Deallocate memory
    delete[] distance;
    delete[] visit;
    delete[] path;

    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout) {
    // Get the size of the graph
    int graphSize = graph->getSize();

    // Check if source and end vertices are within the valid range
    if (s_vertex >= graphSize || e_vertex >= graphSize) return false; 
    
    bool* visited = new bool[graphSize] {false};
    int distance[graphSize];
    int prev[graphSize];

    // Initialize distance and previous arrays
    for (int i = 1; i < graphSize; i++) {
        distance[i] = 999999;
        prev[i] = -1;
    }
    // Set the distance of the source vertex to 0
    distance[s_vertex] = 0;

    // Iterate over vertices to relax edges
    for (int i = 2; i <= graphSize; i++) {
        for (int j = 1; j < graphSize; j++) {
            map<int, int> adjacentEdges;
            // Skip vertices with infinite distance
            if (distance[j] == 999999) continue;
            graph->getAdjacentEdges(j, &adjacentEdges); // Get adjacent nodes for the current vertex

             // Iterate over adjacent edges
            for (const auto& adjacentEdge : adjacentEdges) {
                int nextVertex = adjacentEdge.first;
                int edgeWeight = adjacentEdge.second;
                // Relax the edge
                if (distance[nextVertex] > distance[j] + edgeWeight) { 
                    distance[nextVertex] = distance[j] + edgeWeight;
                    prev[nextVertex] = j; // Update the previous vertex

                    if (i == graphSize) return false; // if negative cycle print error code
                }
            }
        }
    }

    *fout << "======Bellman-Ford======" << endl;
    *fout << (option == 'Y' ? "Directed Graph Bellman-Ford result" : "Undirected Graph Bellman-Ford result") << endl;
    // If there is no path to the end vertex, print 'x'
    if (distance[e_vertex] == 999999) *fout << "x"; 
    else {
        stack<int> pathStack; // If a path exists, reconstruct the path and print it
        for (int j = e_vertex; j != -1; j = prev[j]) pathStack.push(j);
        *fout << pathStack.top();
        pathStack.pop();
        // Print the rest of the path
        while (!pathStack.empty()) { //stack is empty finish path
            *fout << " -> " << pathStack.top();
            pathStack.pop();
        }
        // Print the total cost of the path
        *fout << endl << "cost: " << distance[e_vertex]; //print path weight
    }
    *fout << endl << "====================" << endl << endl;
    // Clean up allocated memory
    delete[] visited;
    // Return
    return true;
}

bool FLOYD(Graph* graph, char option, ofstream* fout) {
    int** distance;

    // Allocate memory for the distance array
    distance = new int* [graph->getSize()];
    for (int i = 1; i < graph->getSize(); i++) {
        distance[i] = new int[graph->getSize()];
    }

    // Initialize
    for (int i = 1; i < graph->getSize(); i++) {
        for (int j = 1; j < graph->getSize(); j++) {
            if (i == j) distance[i][j] = 0;
            else if (graph->getWeight(i, j) != 0) distance[i][j] = graph->getWeight(i, j);
            else distance[i][j] = 999999;
        }
    }

    // Perform the Floyd algorithm
    for (int k = 1; k < graph->getSize(); k++)
        for (int i = 1; i < graph->getSize(); i++)
            for (int j = 1; j < graph->getSize(); j++)
                distance[i][j] = getMin(distance[i][j], distance[i][k] + distance[k][j]); // Update distance if a shorter path is found through vertex k
            
        
    

    // Check for negative cycles in the graph
    for (int i = 1; i < graph->getSize(); i++)
        for (int j = 1; j < graph->getSize(); j++)
            if (distance[i][j] < 999999 && distance[i][j]>500000) return false; // If distance is not the MAX value and greater than 500000, it indicates a negative cycle

    *fout << "======== FLOYD =========" << endl;
    *fout << (option == 'Y' ? "Directed Graph FLOYD result" : "Undirected Graph FLOYD result") << endl;
    *fout << "\t";

    // Output column indices
    for (int i = 1; i < graph->getSize(); i++) {
        *fout << "[" << i << "]" << '\t';
    }
    *fout << endl;

    // Output the shortest distances between vertices
    for (int i = 1; i < graph->getSize(); i++) {
        *fout << "[" << i << "]";
        for (int j = 1; j < graph->getSize() && *fout << '\t'; j++) {
            // Output 'x' if there is no path, otherwise output the shortest distance
            if (distance[i][j] == 999999) *fout << "x"; 
            else *fout << distance[i][j]; 
        }
        *fout << endl;
    }
    *fout << "===========================" << endl << endl;
   
    // Deallocate memory for the distance array
    for (int i = 1; i < graph->getSize(); i++) {
        delete[] distance[i];
    }
    delete[] distance;
    // Return true
    return true;
}

bool KWANGWOON(Graph* graph, int vertex, ofstream* fout) {
    map<int, int> adjacentNodes;
    vector<int> segTree;
    vector<int> beforeVertex;
    int index = 0, diff = 0;

    for (int i = vertex; i < graph->getSize(); i++) {
        // Clear the map of adjacent nodes
        adjacentNodes.clear();
        // Get and update the adjacent edges for the current vertex
        graph->getAdjacentEdges(i, &adjacentNodes);
        graph->updateKWGraph(i, adjacentNodes);

        const auto& kwGraph = graph->getKWGraph(i);

        vector<int> element(kwGraph.begin(), kwGraph.end());

        vector<int> segElement(kwGraph.size());
        fill(segElement.begin(), segElement.end(), 1);
        // Resize the segment tree
        segTree.resize(graph->getKWGraph(i).size() * 4);
        // Initialize the segment tree for the current KWANGWOON graph
        segTreeInit(1, 0, graph->getKWGraph(i).size() - 1, segElement, segTree);
    }

    const auto& kwGraph = graph->getKWGraph(1);
    vector<int> element(kwGraph.begin(), kwGraph.end());
    // Add the starting vertex to the list of previously visited vertices
    beforeVertex.push_back(vertex);

    bool isEven = element.size() % 2 == 0;

    // Adjust the starting vertex based on the number of adjacent edges
    int startVertex = (isEven) ? *min_element(kwGraph.begin(), kwGraph.end()) : *max_element(kwGraph.begin(), kwGraph.end());

    int count = graph->getSize() - 2; // index 1 start not 0, and 1st index is done
    *fout << "======== KWANGWOON =========" << endl;
    *fout << "startvertex: " << vertex << endl;
    *fout << vertex;
    // Perform KWANGWOON algorithm iterations
    while (count--) {
        index = 0, diff = 0;
        *fout << " -> " << startVertex;
        // Get the KWANGWOON graph for the current vertex
        const auto& kwGraph = graph->getKWGraph(startVertex);
        vector<int> element(kwGraph.begin(), kwGraph.end());

        // Update the element vector to remove previously visited vertices
        for (int i = 0; i < element.size(); i++) {
            for (int value : beforeVertex) {
                if (element[i] == value) {
                    element[i] = 0;
                    diff = element[i];
                    break;
                }
            }
        }

        // Remove zero values from the element vector
        element.erase(remove(element.begin(), element.end(), 0), element.end());
        // size update
        int size = element.size() - 1;
        // Update the segment tree with the changes in the element vector
        segTreeUpdate(1, 0, size - 1, 1, diff, element, segTree);

        beforeVertex.push_back(startVertex);
        // Check if the element vector is empty, and break if true
        if (element.size() == 0) break;
        isEven = element.size() % 2 == 0; // Check if the size of the KWANGWOON graph is even
        // Adjust the next vertex based on the number of adjacent edges
        startVertex = (isEven) ? *min_element(element.begin(), element.end()) : *max_element(element.begin(), element.end());
    }
    *fout << endl << "===========================" << endl << endl;
    // Return true
    return true;
}

void QuickSort(int arr[], int low, int high) {
    // Check if there are more than one element in the subarray
    if (low < high) {
        // Use InsertionSort for small subarrays (optimization)
        if(high - low + 1 <= 6) InsertionSort(arr, low + high);
        else {
            // Partition the array and get the pivot index
            int i = low;
            int j = high + 1;
            int pivot = arr[low];

            do {
                // Find the index i such that arr[i] is greater than the pivot
                do i++; while(arr[i] < pivot);
                // Find the index j such that arr[j] is less than the pivot
                do j--; while(arr[j] > pivot);
                // Swap arr[i] and arr[j] if i is less than j
                if(i < j) swap(arr[i], arr[j]);
            } while(i < j);
            // Swap the pivot element with the element at index j
            swap(arr[low], arr[j]);
            // Recursively sort the subarrays on the left and right of the pivot
            QuickSort(arr, low, j - 1);
            QuickSort(arr, j + 1, high);
        }
    }
}

void InsertionSort(int arr[], int n) {
    for(int i = 2; i <= n - 1; i++) {
        // Extract the element to be inserted (current element)
        int key = arr[i];
        // Set up a placeholder for the element's position
        int j = i - 1;
        arr[0] = key;
        // Shift larger elements to the right until a suitable position is found
        while(key < arr[i]) {
             // Move the larger element one position to the right
            arr[j + 1] = arr[j]; 
            j--;
        }
        // Insert the extracted element into the empty slot
        arr[j + 1] = key;
    }
}

int findSet(int i, int parent[]) {
    // Check if the current element is its own parent (root of the set)
    if (parent[i] == -1)
        // If it is, return the element itself
        return i;
    return findSet(parent[i], parent); // recursively call findSet 
}

void unionSets(int x, int y, int parent[]) {
    // Find the roots of the sets containing x and y
    int xset = findSet(x, parent);
    int yset = findSet(y, parent);
    // union
    parent[xset] = yset;
}

int getMin(int a, int b) {
    return a < b ? a : b; // return a < b -> a / a >= b -> b
}

int segTreeInit(int node, int start, int end, vector<int>& _arr, vector<int>& _seg) {
    if (start == end) return _seg[node] = _arr[start];
    // Calculate the mid point of the segment
    int mid = (start + end) / 2;

    segTreeInit(node * 2, start, mid, _arr, _seg); // left child node
    segTreeInit(node * 2 + 1, mid + 1, end, _arr, _seg); // right child node

    // Update the current node value to the sum of its children
    _seg[node] = _seg[node * 2] + _seg[node * 2 + 1];
}

void segTreeUpdate(int node, int start, int end, int target, int diff_value, vector<int>& _arr, vector<int>& _seg) {
    // If not within the section
    if (target < start || target > end) return;

    _seg[node] += diff_value;

    // If the segment has more than one element, recursively update its children
    if (start != end) {
        int mid = (start + end) / 2;
        // Recursively update the left child node
        segTreeUpdate(node * 2, start, mid, target, diff_value, _arr, _seg);
        // Recursively update the right child node
        segTreeUpdate(node * 2 + 1, mid + 1, end, target, diff_value, _arr, _seg);
    }
}