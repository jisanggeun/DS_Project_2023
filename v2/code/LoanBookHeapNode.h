#pragma once
#include "LoanBookData.h"

class LoanBookHeapNode 
{
private:
    LoanBookData* pData; // Pointer to LoanBookData 
    LoanBookHeapNode* pLeft; // Pointer to the leftchild
    LoanBookHeapNode* pRight; // Pointer to the rightchild
    LoanBookHeapNode* pParent; // Pointer to the parent node

public:
    // Constructor
    LoanBookHeapNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
    }
    // Destructor
    ~LoanBookHeapNode() {

    }
    // Set the LoanBookData for the node
    void setBookData(LoanBookData* data) {this->pData = data; }
    // Set the left child
    void setLeftChild(LoanBookHeapNode* pL) { this->pLeft = pL; }
    // Set the right child
    void setRightChild(LoanBookHeapNode* pR) { this->pRight = pR; }
    // Set the parent node
    void setParent(LoanBookHeapNode* pP) { this->pParent = pP; }

    // Get the LoanBookData of the node
    LoanBookData* getBookData() { return pData; }
    // Get the leftchild
    LoanBookHeapNode* getLeftChild() { return pLeft; }
    // Get the rightchild
    LoanBookHeapNode* getRightChild() { return pRight; }
    // Get the parent node
    LoanBookHeapNode* getParent() { return pParent; }
};