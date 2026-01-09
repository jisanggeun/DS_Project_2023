#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size) // constructor
{
	m_Type = type;
    // dynamic allocation
    m_List = new map<int, int>[size]; 
    kw_graph = new vector<int>[size];
}

ListGraph::~ListGraph()	
{
    // deallocate
	delete[] m_List; 
    delete[] kw_graph;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m) // Definition of getAdjacentEdges(No Direction == Undirected)
{
	for (const auto& edge : m_List[vertex]) m->insert(edge); // Put into neighbor node map
    return; // return
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m) // Definition of getAdjacentEdges(Directed graph)
{
	
}

void ListGraph::insertEdge(int from, int to, int weight) // Definition of insertEdge
{
    m_List[from].insert({to, weight}); // insert
	return;
}

bool ListGraph::printGraph(ofstream *fout) { // Print Function
    // Print Format
    *fout << "======== PRINT========" << endl;
    for(int i = 1; i < m_Size; i++) {
        *fout << "["<<i<<"]";
        for (const auto& edge : m_List[i]) *fout << " -> (" << edge.first << "," << edge.second << ")";
        *fout << endl;
    }
    *fout << "=====================" << endl << endl;

    return true;
}

int ListGraph::getWeight(int i, int j) { // Get edge's weight 
    auto it = m_List[i].find(j); // Declare and initialize iterator
    if(it != m_List[i].end()) return it->second;
    else if(it == m_List[i].end()) return 0;
}

bool ListGraph::connectVertex(int i, int j) { // Function to connect i and j vertices
    auto it = m_List[i].find(j);
    if(it != m_List[i].end() && it->second != 0) return true; // Check if element found and it->second is not 0 -> return true
    else return false; // else false
}

void ListGraph::updateKWGraph(int vertex, const map<int, int>& adjacentNodes) {
    // Loop through each key-value pair in the adjacentNodes map
    for (const auto& iter : adjacentNodes) {
        // Push the adjacent vertex into the kw_graph vector for the given vertex
        kw_graph[vertex].push_back(iter.first);
    }
}

vector<int> ListGraph::getKWGraph(int vertex) {
    return kw_graph[vertex]; // return kw_graph vector's vector-th index
}