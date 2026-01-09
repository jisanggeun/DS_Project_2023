#pragma once
#include "LoanBookData.h"
#include "LoanBookHeapNode.h"

class LoanBookHeap
{
private:
    LoanBookHeapNode* root;

public:
    // contructor
    LoanBookHeap() {
        this->root = createHeaps();
    };
    // destructor
    ~LoanBookHeap() {
        destroyHeap(root);
    }

    // Function to set root
    void setRoot(LoanBookHeapNode* pN) { this->root = pN; }
    // Function to get root
    LoanBookHeapNode* getRoot() { return root; }

    // Function to maintain the heap property by moving a node up the heap if necessary
    void heapifyUp(LoanBookHeapNode* pN);
    // Function to maintain the heap property by moving a node down the heap if necessary
    void heapifyDown(LoanBookHeapNode* pN);

    // Function to insert a new node into the heap
    bool Insert(LoanBookData* data);
    // Function to delete the root node from the heap
    bool Delete();

    // Function to find the last node in the heap
    LoanBookHeapNode* findLastNode(LoanBookHeapNode* node);
    // Function to swap the book data between two nodes
    void swap(LoanBookHeapNode* node1, LoanBookHeapNode* node2);

    // Function to create an empty heap and return the root node
    LoanBookHeapNode* createHeaps(); 

    // Recursive function to deallocate memory for all nodes in the heap
    void destroyHeap(LoanBookHeapNode* node);
};
