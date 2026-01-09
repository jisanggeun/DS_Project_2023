#include "LoanBookHeap.h"

// Function to maintain the heap property by moving a node up the heap if necessary
void LoanBookHeap::heapifyUp(LoanBookHeapNode* pN) {
    // Sorting is completed when the book names of all parent nodes are less than or equal to the book names of child nodes.
    while ((pN->getParent() != nullptr) && (pN->getBookData()->getName() < pN->getParent()->getBookData()->getName())) {
        // Swap the book data between the current node and its parent
        LoanBookData* temp = pN->getBookData();
        pN->setBookData(pN->getParent()->getBookData());
        pN->getParent()->setBookData(temp);
        // Move to the parent for the next iteration
        pN = pN->getParent();
    }
}

// Function to maintain the heap property by moving a node down the heap if necessary
void LoanBookHeap::heapifyDown(LoanBookHeapNode* pN) {
    if (pN == nullptr) return; // Skip if the node is nullptr

    // Identify the smallest node among the current node and its children
    LoanBookHeapNode* smallNode = pN;
    LoanBookHeapNode* leftChild_Node = pN->getLeftChild();
    LoanBookHeapNode* rightChild_Node = pN->getRightChild();

    if ((leftChild_Node != nullptr) && (leftChild_Node->getBookData()->getName() < smallNode->getBookData()->getName())) smallNode = leftChild_Node;
    if ((rightChild_Node != nullptr) && (rightChild_Node->getBookData()->getName() < smallNode->getBookData()->getName())) smallNode = rightChild_Node;

    // If a smaller child is found, swap the book data and continue heapifying down
    if (smallNode != pN) {
        LoanBookData* temp = pN->getBookData();
        pN->setBookData(smallNode->getBookData());
        smallNode->setBookData(temp);
        heapifyDown(smallNode);
    }
}

// Function to insert a new node into the heap
bool LoanBookHeap::Insert(LoanBookData* data) {
    LoanBookHeapNode* newNode = new LoanBookHeapNode();
    newNode->setBookData(data);

    // If the heap is empty, set the new node as the root
    if (root->getBookData() == nullptr) root = newNode;
    else {
        // Find the last node in the heap and new node at the end
        LoanBookHeapNode* curNode = root;
        while (curNode->getLeftChild() != nullptr || curNode->getRightChild() != nullptr) {
            if (curNode->getLeftChild() != nullptr && curNode->getRightChild() != nullptr) curNode = curNode->getLeftChild();
            else break;
        }

        // Insert the new node at the end
        if (curNode->getLeftChild() == nullptr) {
            curNode->setLeftChild(newNode);
            newNode->setParent(curNode);
        } else {
            curNode->setRightChild(newNode);
            newNode->setParent(curNode);
        }

        // Fix the heap property
        heapifyUp(newNode);
    }
    return true;
}

// Function to delete the root node from the heap
bool LoanBookHeap::Delete() {
    if (root == nullptr) return false;  // Heap is empty

    // Find the last node in the heap and swap it with the root
    LoanBookHeapNode* lastNode = findLastNode(root);
    swap(root, lastNode);

    // Remove the last node from the heap
    if (lastNode->getParent() != nullptr) {
        if (lastNode == lastNode->getParent()->getLeftChild()) lastNode->getParent()->setLeftChild(nullptr);
        else lastNode->getParent()->setRightChild(nullptr);
    }
    else lastNode->setBookData(nullptr); // only root in heap
    
    // Fix the heap property
    heapifyDown(root);

    // Delete the last node
    delete lastNode->getBookData();

    return true;
}

// Function to find the last node in the heap
LoanBookHeapNode* LoanBookHeap::findLastNode(LoanBookHeapNode* node) {
    while (node->getLeftChild() != nullptr || node->getRightChild() != nullptr) {
        if (node->getRightChild() != nullptr) node = node->getRightChild();
        else node = node->getLeftChild();
    }
    return node;
}

// Function to swap the book data between two nodes
void LoanBookHeap::swap(LoanBookHeapNode* node1, LoanBookHeapNode* node2) {
    LoanBookData* temp = node1->getBookData();
    node1->setBookData(node2->getBookData());
    node2->setBookData(temp);
}

// Function to create an empty heap and return the root node
LoanBookHeapNode* LoanBookHeap::createHeaps() {
    LoanBookHeapNode* heap;
    heap = new LoanBookHeapNode();
    return heap; // Return the root of the tree
}

// Function to destructor processing
void LoanBookHeap::destroyHeap(LoanBookHeapNode* node) {
    if (node == nullptr) return; // Base case: reached a nullptr node

    // Recursively delete the left and right subtrees
    destroyHeap(node->getLeftChild());
    destroyHeap(node->getRightChild());

    // Delete the current node
    delete node;
}