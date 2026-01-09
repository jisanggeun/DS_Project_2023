#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph{	
private:
	map < int, int >* m_List; // list graph
	vector<int>* kw_graph; // Kwangwoon Algorithm
	
public:	
	ListGraph(bool type, int size);
	~ListGraph();
	
	// Function to find adjacent nodes
	void getAdjacentEdges(int vertex, map<int, int>* m);	
	void getAdjacentEdgesDirect(int vertex, map<int, int>* m);
	// Function to insert edge
	void insertEdge(int from, int to, int weight);	
	// Function to Print
	bool printGraph(ofstream *fout);

	// Function to get Weight
	int getWeight(int i, int j);
	// Function to connect i and j vertices
	bool connectVertex(int i, int j);
	// Function to update Kw Graph
	void updateKWGraph(int vertex, const map<int, int>& adjacentNodes);
	vector<int> getKWGraph(int vertex);
};

#endif