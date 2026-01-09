#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <map>
#include "Graph.h"

class MatrixGraph : public Graph{	
private:
	int** m_Mat; // Matrix graph

public:
	MatrixGraph(bool type, int size);
	~MatrixGraph();

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