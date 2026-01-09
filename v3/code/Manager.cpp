#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Manager::Manager() {
	graph = nullptr;	
	fout.open("log.txt", ios::app);
	load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
	if(load)	//if graph is loaded, delete graph
		delete graph;	
		delete nodirection_graph;
		delete direction_graph;
	if(fout.is_open())	//if fout is opened, close file
		fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
	ifstream fin;	//Command File Input File Stream
	fin.open(command_txt, ios_base::in);//File open with read mode

	string line;
		
	if(!fin) { //If command File cannot be read, Print error
		fout<<"command file open error"<<endl;
		return;	//Return
	}

	while (getline(fin, line)) {
		if(fin.fail()) {
			fin.clear(); // buffer clear
			continue;
		}
		
		if(line.find("LOAD") != string::npos) { // Load instruction
			istringstream iss(line);
			string command, filename;

			iss >> command >> filename; // split
			// convert
			const char* input_cmd = command.c_str(); 
			const char* input_name = filename.c_str();
			int state = LOAD(input_name); // LOAD
			if(state) { // Success
				fout << "======= LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=====================" << endl << endl;
			} else if(!state) printErrorCode(100); // Error code
		} else if (line.find("PRINT") != string::npos) {
			int state = PRINT(); // PRINT 
			if(!state) printErrorCode(200); // Error code
		} else if (line.find("BFS") != string::npos) {
			istringstream iss(line);
			string command;
			char type;
			int start = -1; // initialize

			iss >> command >> type >> start; // split

			int state = mBFS(type, start); // BFS function 
			if (!state) printErrorCode(300); // Error code
		} else if (line.find("DFS") != string::npos) {
			istringstream iss(line);
			string command;
			char type;
			int start = -1; // initialize

			iss >> command >> type >> start; // split

			int state = mDFS(type, start); // DFS function
			if (!state) printErrorCode(400); // Error code
		} else if (line.find("KWANGWOON") != string::npos) {
			int state = mKwangWoon(1); // Kwangwoon Algorithm
			if (!state) printErrorCode(500); // Error code
		} else if (line.find("KRUSKAL") != string::npos) {
			int state = mKRUSKAL(); // Kruskal algorithm
			if (!state) printErrorCode(600); // Error code
		} else if (line.find("DIJKSTRA") != string::npos) {
			istringstream iss(line);
			string command;
			char type;
			int start = -1; // initialize

			iss >> command >> type >> start; // split

			int state = mDIJKSTRA(type, start); // Dijkstra function
			if (!state) printErrorCode(700); // Error code
		} else if (line.find("BELLMANFORD") != string::npos) {
			istringstream iss(line);
			string command;
			char type;
			int start = -1; // initialize
			int end = -1;

			iss >> command >> type >> start >> end; // split

			int state = mBELLMANFORD(type, start, end); // BellmanFord 
			if (!state) printErrorCode(800); // Error code
		} else if (line.find("FLOYD") != string::npos) {
			istringstream iss(line);
			string command;
			char type;

			iss >> command >> type; // split

			int state = mFLOYD(type); // Floyd
			if (!state) printErrorCode(900); // Error code
		} else if (line.find("EXIT") != string::npos) {
			return; // Program Exit
		} else {
			printErrorCode(1000); // Error Code
		}
	}
	
	fin.close(); // file close
	return;
}

bool Manager::LOAD(const char* filename) {
	ifstream fdata;
	fdata.open(filename); // file open

	if (!fdata.is_open()) { // Check if the file is open
		fdata.close();
		return false;
	} 

	if (fdata.peek() == ifstream::traits_type::eof()) { // Check if the file is empty
		fdata.close();
		return false;
	}

	string str_type, str_size;
	int size;

	getline(fdata, str_type); // str_type <- fdata
	getline(fdata, str_size); // str_size <- fdata

	size = stoi(str_size); // convert str to int
	size++; // size up

	// list graph
	if(string(filename) == "graph_L.txt") {
		string line, temp;

		// dynamic allocation
		graph = new ListGraph(0, size);
		nodirection_graph = new ListGraph(0, size);
		direction_graph = new ListGraph(0, size);

		while(getline(fdata, line)) {
			istringstream iss(line);
			string str_vertex, str_weight;

			getline(iss, str_vertex, ' ');
			getline(iss, str_weight, ' ');
			if(!str_weight.empty()) {
				int int_vertex = stoi(str_vertex); // vertex
				int int_weight = stoi(str_weight); // weight
				int int_temp = stoi(temp); // next vertex

				// graph initialize
				graph->insertEdge(int_temp, int_vertex, int_weight);
				direction_graph->insertEdge(int_temp, int_vertex, int_weight);
				if (nodirection_graph->getWeight(int_vertex, int_temp) < int_weight && nodirection_graph->getWeight(int_vertex, int_temp) != 0) continue;

				nodirection_graph->insertEdge(int_temp, int_vertex, int_weight);
				nodirection_graph->insertEdge(int_vertex, int_temp, int_weight);
			} else {
				temp = str_vertex;
			}
		}

	} else if(string(filename) == "graph_M.txt") { // Matrix Graph
		string line, temp;

		// Dynamic allocation
		graph = new MatrixGraph(1, size);
		nodirection_graph = new MatrixGraph(1, size);
		direction_graph = new MatrixGraph(1, size);

		// Top to bottom
		for(int i = 1; i < size; i++) {
			getline(fdata, line);
			// Use istringstream to tokenize the line based on spaces
			istringstream iss(line);
			string str_weight;

			getline(iss, str_weight, ' ');
			int int_weight = stoi(str_weight); // convert string to int

			// Insert the edge into the graph, directed graph, and undirected graph
			graph->insertEdge(i, 1, int_weight);
			direction_graph->insertEdge(i, 1, int_weight);

			// Insert the edge into the undirected graph only if the weight is non-zero
			if (int_weight != 0) {
				nodirection_graph->insertEdge(i, 1, int_weight);
				nodirection_graph->insertEdge(1, i, int_weight);
			}
			
			// Loop through each remaining vertex from 2 to size - 1
			for(int j = 2; j < size; j++) {
				if (getline(iss, str_weight, ' ')) int_weight = stoi(str_weight);
				graph->insertEdge(i, j, int_weight);
				direction_graph->insertEdge(i, j, int_weight);
				if (int_weight == 0) continue; // If the weight is zero, skip further processing for undirected graph
				else if(int_weight != 0) {
					if (nodirection_graph->getWeight(j, i) < int_weight && nodirection_graph->getWeight(j, i) != 0) {
						// If the existing weight is less than the current weight, update it
						int ori_weight = nodirection_graph->getWeight(j, i);
						nodirection_graph->insertEdge(i, j, ori_weight);
					} else {
						// Otherwise, insert the edge into the undirected graph with current weight
						nodirection_graph->insertEdge(i, j, int_weight);
						nodirection_graph->insertEdge(j, i, int_weight);
					}
				}
			}
		}

	}

	return true;
}

bool Manager::PRINT() {
	if(graph == nullptr) return false; // graph is none
	if(graph->printGraph(&fout)) return true; // PRINT function
	return false;
}

bool Manager::mBFS(char option, int vertex)	{
	if(graph == nullptr) return false; // graph is none
	if(vertex == -1) return false; // vertex is none

	// Separated according to direction
	if (option == 'Y') {
		if (!BFS(direction_graph, 'Y', vertex, &fout)) return false;
	} else if (option == 'N') {
		if (!BFS(nodirection_graph, 'N', vertex, &fout)) return false;
	}
	return true;
}

bool Manager::mDFS(char option, int vertex)	{
	if (graph == nullptr) return false; // graph is none
	if(vertex == -1) return false; // vertex is none

	// Separated according to direction
	if (option == 'Y') {
		if (!DFS(direction_graph, 'Y', vertex, &fout)) return false;
	} else if (option == 'N') {
		if (!DFS(nodirection_graph, 'N', vertex, &fout)) return false;
	}
	return true;
}

bool Manager::mKRUSKAL() {
	if(graph == nullptr) return false; // graph is none 
	if(!Kruskal(nodirection_graph, &fout)) return false; // KRUSKAL

	return true;
}

bool Manager::mDIJKSTRA(char option, int vertex) {
	if (graph == nullptr) return false; // graph is none
	if(vertex == -1) return false; // vertex is none

	// Separated according to direction
	if (option == 'Y') {
		if (!Dijkstra(direction_graph, 'Y', vertex, &fout)) return false;
	}
	else if (option == 'N') {
		if (!Dijkstra(nodirection_graph, 'N', vertex, &fout)) return false;
	}
	return true;
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) {
	if (graph == nullptr) return false; // graph is none
	if(s_vertex == -1 || e_vertex == -1) return false; // start vertex or end vertex is none

	// Separated according to direction
	if (option == 'Y') {
		if (!Bellmanford(direction_graph, 'Y', s_vertex, e_vertex, &fout)) return false;
	}
	else if (option == 'N') {
		if (!Bellmanford(nodirection_graph, 'N', s_vertex, e_vertex, &fout)) return false;
	}
	return true;
}

bool Manager::mFLOYD(char option) {
	if (graph == nullptr) return false; // graph is none
	// Separated according to direction
	if (option == 'Y') {
		if (!FLOYD(direction_graph, 'Y', &fout)) return false;
	}
	else if (option == 'N') {
		if (!FLOYD(nodirection_graph, 'N', &fout)) return false;
	}
	return true;
}

bool Manager::mKwangWoon(int vertex) {
	if (graph == nullptr) return false; // graph is none
	// KwangWoon algorithm
	if(!KWANGWOON(nodirection_graph, vertex, &fout)) return false;
	return true;
}

void Manager::printErrorCode(int n) // Error code Print
{
	fout<<"========ERROR======="<<endl;
	fout<<n<<endl;
	fout<<"===================="<<endl << endl;
}


