#pragma once
#include "SelectionTreeNode.h"

#include <fstream>
#include <iostream>
#include <map>

class SelectionTree
{
private:
    SelectionTreeNode* root;
    ofstream* fout;

public:
    SelectionTree(ofstream* fout) {
        this->root = createSelectionTree();
        this->fout = fout;
    }
    ~SelectionTree() {
        deleteTree(root);
    }
    // map to save book
    map<string, LoanBookData*> bookMap;

    // Function to make Selection tree
    SelectionTreeNode* createSelectionTree();

    // Function to set root
    void setRoot(SelectionTreeNode* pN) { this->root = pN; }
    // Function to get root
    SelectionTreeNode* getRoot() { return root; }

    // Function to insert a new LoanBookData into the SelectionTree
    bool Insert(LoanBookData* newData);
    // Function to delete LoanBookData into the SelectionTree
    bool Delete();
    // Function to print Book data
    bool printBookData(int bookCode);
    // Function to stores bookdata while traverse the heap
    bool traverseHeap(LoanBookHeapNode* node);

    // Recursive function to deallocate memory for all nodes in the SelectionTree
    void deleteTree(SelectionTreeNode* node);
};