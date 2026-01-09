#pragma once
#include "LoanBookData.h"
#include <map>
#include <algorithm>

class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:
    // Constructor
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
    // Destructor
	~BpTreeNode() {

	}

    // Setter
	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }

    // Getter
	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

    // Virtual functions 
	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

    // Virtual functions for data node operations
	virtual void insertDataMap(string n, LoanBookData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}
    
    // Virtual functions for getting maps
	virtual map<string, BpTreeNode*>* getIndexMap() { return {}; }
	virtual map<string, LoanBookData*>* getDataMap() { return {}; }

    void updateIndexKey(const std::string& oldKey, const std::string& newKey) {
        auto& indexMap = *getIndexMap(); // Assuming getIndexMap() returns a pointer

        auto it = indexMap.find(oldKey);
        if (it != indexMap.end()) {
            // Insert the new key-value pair and remove the old one
            indexMap[newKey] = move(it->second);
            indexMap.erase(it);
        }
    }

    // Merge data from another data node into the current data node
    void mergeData(BpTreeNode* other) {
        // Assuming you have the appropriate map in your class
        for (auto& entry : *other->getDataMap()) getDataMap()->insert(entry);
        // Assuming you have the appropriate pointers in your class
        setNext(other->getNext());
    }

    // Merge index nodes
    void mergeIndex(BpTreeNode* other) {
        // Assuming you have the appropriate map in your class
        for (auto& entry : *other->getIndexMap()) getIndexMap()->insert(entry);
    }

    BpTreeNode* findLeftSibling(BpTreeNode* pNode) const {
        // No parent, hence no left sibling
        if (pParent == nullptr) return nullptr;
        auto& indexMap = *pParent->getIndexMap();

        // Find the key associated with pNode
        auto it = find_if(indexMap.begin(), indexMap.end(), [pNode](const pair<const std::string, BpTreeNode*>& entry) { return entry.second == pNode; });

        // pNode is the leftmost child, so no left sibling
        if (it == indexMap.begin()) return nullptr;

        --it; // Move to the left sibling
        return it->second;
    }

    BpTreeNode* findRightSibling(BpTreeNode* pNode) const {
        // No parent, hence no right sibling
        if (pParent == nullptr) return nullptr;

        auto& indexMap = *pParent->getIndexMap();
        // Find the key associated with pNode
        auto it = find_if(indexMap.begin(), indexMap.end(), [pNode](const pair<const std::string, BpTreeNode*>& entry) { return entry.second == pNode; });

        ++it; // Move to the right sibling
        // pNode is the rightmost child, so no right sibling
        if (it == indexMap.end()) return nullptr;

        return it->second;
    }
};
#pragma once
