#pragma once
#include "LoanBookData.h"
#include "LoanBookHeap.h"

class SelectionTreeNode 
{
private:
    LoanBookData* pData; // LoanBookData Pointer
    SelectionTreeNode* pLeft; // leftchild Pointer
    SelectionTreeNode* pRight; // rightchild Pointer
    SelectionTreeNode* pParent; // parent node Pointer
    LoanBookHeap* hRoot; // heap's root Pointer

public:
    // Constructor
    SelectionTreeNode() {
        this->pData = NULL;
        this->pLeft = NULL;
        this->pRight = NULL;
        this->pParent = NULL;
        this->hRoot = NULL;
    }
    // Destructor
    ~SelectionTreeNode() {

    }

    // Set the LoanBookData for the node
    void setBookData(LoanBookData* data) { this->pData = data; }
    // Set the leftchild 
    void setLeftChild(SelectionTreeNode* pL) { this->pLeft = pL; }
    // Set the rightchild
    void setRightChild(SelectionTreeNode* pR) { this->pRight = pR; }
    // Set the parent node
    void setParent(SelectionTreeNode* pP) { this->pParent = pP; }
    // Set the root of the LoanBookHeap for the node
    void setHeap(LoanBookHeap* pHR) { this->hRoot = pHR; }

    // function to output heap data stored in LoanBookHeap according to book classification code
    LoanBookHeapNode* deepCopy(LoanBookHeapNode* root) {
        if (root == NULL) return nullptr;

        LoanBookHeapNode* copy = new LoanBookHeapNode();
        copy->setLeftChild(deepCopy(root->getLeftChild()));
        copy->setRightChild(deepCopy(root->getLeftChild()));

        return copy;
    } 

    // Get the LoanBookData of the node
    LoanBookData* getBookData() { return pData; }
    // Get the leftchild
    SelectionTreeNode* getLeftChild() { return pLeft; }
    // Get the rightchild
    SelectionTreeNode* getRightChild() { return pRight; }
    // Get the parent node
    SelectionTreeNode* getParent() { return pParent; }
    // Get the root of the LoanBookHeap for the node
    LoanBookHeap* getHeap() { return hRoot; }
};