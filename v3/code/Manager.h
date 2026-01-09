#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager{	
private:
	Graph* graph; // init Graph
	Graph* nodirection_graph; // undirected graph
	Graph* direction_graph;	// directed graph
	vector<vector<int>> KWvector; // Kwangwoon Algorithm's vector
	ofstream fout;
	int load; // load determination

public:
	Manager();	
	~Manager();	

	void run(const char * command_txt);
	
	bool LOAD(const char* filename); // Load Function
	bool PRINT(); // Print Function
	bool mBFS(char option, int vertex);	// BFS Function
	bool mDFS(char option, int vertex);	// DFS Function
	bool mDIJKSTRA(char option, int vertex); // Dijkstra Function
	bool mKRUSKAL(); // Kruskal Function
	bool mBELLMANFORD(char option, int s_vertex, int e_vertex);	// BellmanFord Function
	bool mFLOYD(char option); // Floyd Function
	bool mKwangWoon(int vertex); // KwangWoon Function
	void printErrorCode(int n); // Error Code Function
};

#endif