#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, char option, int vertex, ofstream* fout); // BFS
bool DFS(Graph* graph, char option,  int vertex, ofstream* fout); // DFS
bool KWANGWOON(Graph* graph, int vertex, ofstream* fout); // KwangWoon Algorithm
bool Kruskal(Graph* graph, ofstream* fout); // Kruskal Algorithm
bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout); // Djikstra Algorithm
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout); // BellmanFord Algorithm
bool FLOYD(Graph* graph, char option, ofstream* fout); // Floyd Algorithm

void QuickSort(int arr[], int low, int high); // QuickSort
void InsertionSort(int arr[], int n); // If less than Segment Size 

int findSet(int i, int parent[]); // 
void unionSets(int x, int y, int parent[]);
int getMin(int a, int b);

int segTreeInit(int node, int start, int end, vector<int>& _arr, vector<int>& _seg);
void segTreeUpdate(int node, int start, int end, int target, int diff_value, vector<int>& _arr, vector<int>& _seg);

#endif
