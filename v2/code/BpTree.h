#ifndef _BpTree_H_
#define _BpTree_H_

#include "BpTreeDataNode.h"
#include "BpTreeIndexNode.h"
#include "LoanBookData.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <list>

class BpTree {
	private:
		BpTreeNode* root;
		int order; // m children
		ofstream* fout;

	public:
		// Constructor
		BpTree(ofstream* fout, int order = 3) {
			root = NULL;
			this->order = order;
			this->fout = fout;
		}

		// Destructor
		~BpTree() {
			destroyTree(root);
		}

		/* essential */
		// Insert a new data node into the BpTree
		bool Insert(LoanBookData* newData);
		// Check if data node exceeds the maximum capacity
		bool excessDataNode(BpTreeNode* pDataNode);
		// Check if index node exceeds the maximum capacity
		bool excessIndexNode(BpTreeNode* pIndexNode);
		// Split data node
		void splitDataNode(BpTreeNode* pDataNode);
		// Split index node
		void splitIndexNode(BpTreeNode* pIndexNode);

		// Get root of BpTree
		BpTreeNode* getRoot() { return root; }
		// Search for data node by name
		BpTreeNode* searchDataNode(string name);

		// Search for book by name
		bool searchBook(string name);
		// Search for books within a given range
		bool searchRange(string start, string end);
		// Print all data nodes in the BpTree
		bool printBook();

		// Get book data by name
		LoanBookData* getBookData(string name);

		// Delete a data node from the BpTree
		bool Delete(LoanBookData* newData);
		// Borrow a key from a sibling data node
		bool borrowKeyFromSibling(BpTreeNode* pDataNode);
		// Merge with a sibling data node
		bool mergeWithDataNodeSibling(BpTreeNode* pDataNode);
		// Adjust the parent index node after deletion
		void adjustParentIndexNode(BpTreeNode* pIndexNode);

		// Destructor processing
		void destroyTree(BpTreeNode* pNode);
};

#endif
