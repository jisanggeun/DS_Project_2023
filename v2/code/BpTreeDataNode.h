#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, LoanBookData*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;

public:
	// Constructor
	BpTreeDataNode() {
		pNext = NULL;
		pPrev = NULL;
	}
	// Destructor
	~BpTreeDataNode() {
		for (auto it = mapData.begin(); it != mapData.end(); ++it) delete it->second;   
		mapData.clear();
	}

	// setters
	void setNext(BpTreeNode* pN) { pNext = pN; }
	void setPrev(BpTreeNode* pN) { pPrev = pN; }
	// getters
	BpTreeNode* getNext() { return pNext; }
	BpTreeNode* getPrev() { return pPrev; }

	// Insert a new data into the map
	void insertDataMap(string name, LoanBookData* pN) {
		mapData.insert(map<string, LoanBookData*>::value_type(name, pN));
	}
	// Delete an data from the map
	void deleteMap(string name) {
		mapData.erase(name);
	}
	// Get a pointer to the data map
	map<string, LoanBookData*>* getDataMap() { return &mapData; }
};

#endif
