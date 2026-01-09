#ifndef _BPTREEINDEXNODE_H_
#define _BPTREEINDEXNODE_H_

#include "BpTreeNode.h"
//template <class T>
class BpTreeIndexNode : public BpTreeNode {
private:
	// Map to store index information
	map <string, BpTreeNode*> mapIndex;

public:
	// Constructor
	BpTreeIndexNode() {};
	// Destructor
	~BpTreeIndexNode() {
		for (auto it = mapIndex.begin(); it != mapIndex.end(); ++it) delete it->second;   
		mapIndex.clear();
	};

	// Insert a new index into the map
	void insertIndexMap(string name, BpTreeNode* pN) {
		mapIndex.insert(map<string, BpTreeNode*>::value_type(name, pN));
	}
	// Delete an index from the map
	void deleteMap(string name) {
		mapIndex.erase(name);
	}
	// Get a pointer to the index map
	map<string, BpTreeNode*>* getIndexMap() { return &mapIndex; }
};

#endif