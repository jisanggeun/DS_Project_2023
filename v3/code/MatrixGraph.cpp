#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size) { // constructor
    // Dynamic allocation
    m_Mat = new int*[size];
    for(int i = 0; i < size; i++) {
		m_Mat[i] = new int[size];
		fill_n(m_Mat[i], size, 0);
	}
}

MatrixGraph::~MatrixGraph() { // desctructor
    for(int i = 0; i < getSize(); i++) delete[] m_Mat[i];
    delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m) {	 // Definition of getAdjacentEdges(No Direction == Undirected)
    for(int i = 0; i<getSize(); i++) {
		if(m_Mat[vertex][i] != 0) m->insert({i, m_Mat[vertex][i]}); // Insert map data
	}
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m) // Definition of getAdjacentEdges(Directed graph)
{
	
}

void MatrixGraph::insertEdge(int from, int to, int weight) { // Definition of insertEdge
	m_Mat[from][to] = weight; // insert data
	return;
}

bool MatrixGraph::printGraph(ofstream *fout) { // Print Function
	if( m_Size < 0 ) return false;

    // Print Format
    *fout << "======== PRINT========" << endl;

	*fout << '\t';
    for (int i = 1; i < m_Size; i++) *fout << "[" << i << "]" << '\t';
    *fout << endl;

	for (int i = 1; i < m_Size; i++) {
        *fout << "[" << i << "]";
        for (int j = 1; j < m_Size && *fout << '\t'; j++) *fout << m_Mat[i][j];
        *fout << endl;
    }
    *fout << "=====================" << endl << endl;
	return true;
}
 
int MatrixGraph::getWeight(int i, int j) { // Get edge's weight 
    return m_Mat[i][j];
}

bool MatrixGraph::connectVertex(int i, int j) { // Function to connect i and j vertices
    return m_Mat[i][j] != 0;
}

void MatrixGraph::updateKWGraph(int vertex, const map<int, int>& adjacentNodes) {

}
	
vector<int> MatrixGraph::getKWGraph(int vertex) {

}
