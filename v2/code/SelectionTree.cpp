#include "SelectionTree.h"

// Function to insert a new LoanBookData into the SelectionTree
bool SelectionTree::Insert(LoanBookData* newData) {
    // Start searching for the appropriate node based on the book code
    SelectionTreeNode* findNode = getRoot();
    int findIndex = newData->getCode();

    // Heads to the root of min heap based on findIndex
    if (findIndex < 400) {
        findNode = findNode->getLeftChild();
        if (findIndex < 200) {
            findNode = findNode->getLeftChild();
            if (findIndex < 100) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
        else {
            findNode = findNode->getRightChild();
            if (findIndex < 300) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
    }
    else {
        findNode = findNode->getRightChild();
        if (findIndex < 600) {
            findNode = findNode->getLeftChild();
            if (findIndex < 500) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
        else {
            findNode = findNode->getRightChild();
            if (findIndex < 700) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
    }

    // Insert data into the heap via getheap
    findNode->getHeap()->Insert(newData);

    // level 3 selection tree node
    SelectionTreeNode* heapRootNode1 = getRoot()->getLeftChild()->getLeftChild()->getLeftChild();
    SelectionTreeNode* heapRootNode2 = getRoot()->getLeftChild()->getLeftChild()->getRightChild();
    SelectionTreeNode* heapRootNode3 = getRoot()->getLeftChild()->getRightChild()->getLeftChild();
    SelectionTreeNode* heapRootNode4 = getRoot()->getLeftChild()->getRightChild()->getRightChild();
    SelectionTreeNode* heapRootNode5 = getRoot()->getRightChild()->getLeftChild()->getLeftChild();
    SelectionTreeNode* heapRootNode6 = getRoot()->getRightChild()->getLeftChild()->getRightChild();
    SelectionTreeNode* heapRootNode7 = getRoot()->getRightChild()->getRightChild()->getLeftChild();
    SelectionTreeNode* heapRootNode8 = getRoot()->getRightChild()->getRightChild()->getRightChild();

    // Filling the level 3 selection tree node with data
    if(heapRootNode1->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode1->setBookData(heapRootNode1->getHeap()->getRoot()->getBookData());
    if(heapRootNode2->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode2->setBookData(heapRootNode2->getHeap()->getRoot()->getBookData());
    if(heapRootNode3->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode3->setBookData(heapRootNode3->getHeap()->getRoot()->getBookData());
    if(heapRootNode4->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode4->setBookData(heapRootNode4->getHeap()->getRoot()->getBookData());
    if(heapRootNode5->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode5->setBookData(heapRootNode5->getHeap()->getRoot()->getBookData());
    if(heapRootNode6->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode6->setBookData(heapRootNode6->getHeap()->getRoot()->getBookData());
    if(heapRootNode7->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode7->setBookData(heapRootNode7->getHeap()->getRoot()->getBookData());
    if(heapRootNode8->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode8->setBookData(heapRootNode8->getHeap()->getRoot()->getBookData());

    // level 2 selection tree node
    SelectionTreeNode* tempNode1 = getRoot()->getLeftChild()->getLeftChild();
    SelectionTreeNode* tempNode2 = getRoot()->getLeftChild()->getRightChild();
    SelectionTreeNode* tempNode3 = getRoot()->getRightChild()->getLeftChild();
    SelectionTreeNode* tempNode4 = getRoot()->getRightChild()->getRightChild();

    // Filling the level 2 selection tree node with data through competition
    if (heapRootNode1->getBookData() == nullptr && heapRootNode2->getBookData() != nullptr) tempNode1->setBookData(heapRootNode2->getBookData());
    else if (heapRootNode1->getBookData() != nullptr && heapRootNode2->getBookData() == nullptr) tempNode1->setBookData(heapRootNode1->getBookData());
    else if (heapRootNode1->getBookData() == nullptr && heapRootNode2->getBookData() == nullptr) tempNode1->setBookData(nullptr);
    else if (heapRootNode1->getBookData()->getName() > heapRootNode2->getBookData()->getName()) tempNode1->setBookData(heapRootNode2->getBookData());
    else tempNode1->setBookData(heapRootNode1->getBookData());

    if (heapRootNode3->getBookData() == nullptr && heapRootNode4->getBookData() != nullptr) tempNode2->setBookData(heapRootNode4->getBookData());
    else if (heapRootNode3->getBookData() != nullptr && heapRootNode4->getBookData() == nullptr) tempNode2->setBookData(heapRootNode3->getBookData());
    else if (heapRootNode3->getBookData() == nullptr && heapRootNode4->getBookData() == nullptr) tempNode2->setBookData(nullptr);
    else if (heapRootNode3->getBookData()->getName() > heapRootNode4->getBookData()->getName()) tempNode2->setBookData(heapRootNode4->getBookData());
    else tempNode2->setBookData(heapRootNode3->getBookData());

    if (heapRootNode5->getBookData() == nullptr && heapRootNode6->getBookData() != nullptr) tempNode3->setBookData(heapRootNode6->getBookData());
    else if (heapRootNode5->getBookData() != nullptr && heapRootNode6->getBookData() == nullptr) tempNode3->setBookData(heapRootNode5->getBookData());
    else if (heapRootNode5->getBookData() == nullptr && heapRootNode6->getBookData() == nullptr) tempNode3->setBookData(nullptr);
    else if (heapRootNode5->getBookData()->getName() > heapRootNode6->getBookData()->getName()) tempNode3->setBookData(heapRootNode6->getBookData());
    else tempNode3->setBookData(heapRootNode5->getBookData());

    if (heapRootNode7->getBookData() == nullptr && heapRootNode8->getBookData() != nullptr) tempNode4->setBookData(heapRootNode8->getBookData());
    else if (heapRootNode7->getBookData() != nullptr && heapRootNode8->getBookData() == nullptr) tempNode4->setBookData(heapRootNode7->getBookData());
    else if (heapRootNode7->getBookData() == nullptr && heapRootNode8->getBookData() == nullptr) tempNode4->setBookData(nullptr);
    else if (heapRootNode7->getBookData()->getName() > heapRootNode8->getBookData()->getName()) tempNode4->setBookData(heapRootNode8->getBookData());
    else tempNode4->setBookData(heapRootNode7->getBookData());

    // level 1 selection tree node
    SelectionTreeNode* tempNode5 = getRoot()->getLeftChild();
    SelectionTreeNode* tempNode6 = getRoot()->getRightChild();

    // Filling the level 1 selection tree node with data through competition
    if (tempNode1->getBookData() == nullptr && tempNode2->getBookData() != nullptr) tempNode5->setBookData(tempNode2->getBookData());
    else if (tempNode1->getBookData() != nullptr && tempNode2->getBookData() == nullptr) tempNode5->setBookData(tempNode1->getBookData());
    else if (tempNode1->getBookData() == nullptr && tempNode2->getBookData() == nullptr) tempNode5->setBookData(nullptr);
    else if (tempNode1->getBookData()->getName() > tempNode2->getBookData()->getName()) tempNode5->setBookData(tempNode2->getBookData());
    else tempNode5->setBookData(tempNode1->getBookData());

    if (tempNode3->getBookData() == nullptr && tempNode4->getBookData() != nullptr) tempNode6->setBookData(tempNode4->getBookData());
    else if (tempNode3->getBookData() != nullptr && tempNode4->getBookData() == nullptr) tempNode6->setBookData(tempNode3->getBookData());
    else if (tempNode3->getBookData() == nullptr && tempNode4->getBookData() == nullptr) tempNode6->setBookData(nullptr);
    else if (tempNode3->getBookData()->getName() > tempNode4->getBookData()->getName()) tempNode6->setBookData(tempNode4->getBookData());
    else tempNode6->setBookData(tempNode3->getBookData());

    // level 0 selection tree node == root node
    SelectionTreeNode* tempNode7 = getRoot();

    // Filling the level 0 selection tree node with data through competition
    if (tempNode5->getBookData() == nullptr && tempNode6->getBookData() != nullptr) tempNode7->setBookData(tempNode6->getBookData());
    else if (tempNode5->getBookData() != nullptr && tempNode6->getBookData() == nullptr) tempNode7->setBookData(tempNode5->getBookData());
    else if (tempNode5->getBookData() == nullptr && tempNode6->getBookData() == nullptr) tempNode7->setBookData(nullptr);
    else if (tempNode5->getBookData()->getName() > tempNode6->getBookData()->getName())tempNode7->setBookData(tempNode6->getBookData());
    else tempNode7->setBookData(tempNode5->getBookData());

    return true;
}

// Function to delete LoanBookData into the SelectionTree
bool SelectionTree::Delete() {
    // nullptr == empty selection tree
    if (root == nullptr) return false;

    SelectionTreeNode* findNode = getRoot();
    if (findNode->getBookData() == nullptr) return false;

    // save root's code 
    int bookCode = findNode->getBookData()->getCode();

    // delete node
    findNode->setBookData(nullptr);

    // According to the min winner tree rules, find and delete child nodes with the same code.
    if (bookCode == 0) {
        for (int i = 0; i < 3; i++) {
            findNode = findNode->getLeftChild();
            findNode->setBookData(nullptr);
        }
    } else if (bookCode == 100) {
        for (int i = 0; i < 2; i++) {
            findNode = findNode->getLeftChild();
            findNode->setBookData(nullptr);
        }
        findNode = findNode->getRightChild();
        findNode->setBookData(nullptr);
    } else if (bookCode == 200) {
        findNode = findNode->getLeftChild();
        findNode->setBookData(nullptr);
        
        findNode = findNode->getRightChild();
        findNode->setBookData(nullptr);

        findNode = findNode->getLeftChild();
        findNode->setBookData(nullptr);
    } else if (bookCode == 300) {
        findNode = findNode->getLeftChild();
        findNode->setBookData(nullptr);

        for (int i = 0; i < 2; i++) {
            findNode = findNode->getRightChild();
            findNode->setBookData(nullptr);
        }
    } else if (bookCode == 400) {
        findNode = findNode->getRightChild();
        findNode->setBookData(nullptr);
        for (int i = 0; i < 2; i++) {
            findNode = findNode->getLeftChild();
            findNode->setBookData(nullptr);
        }
    } else if (bookCode == 500) {
        findNode = findNode->getRightChild();
        findNode->setBookData(nullptr);
        
        findNode = findNode->getLeftChild();
        findNode->setBookData(nullptr);
        
        findNode = findNode->getRightChild();
        findNode->setBookData(nullptr);
    } else if (bookCode == 600) {
        for (int i = 0; i < 2; i++) {
            findNode = findNode->getRightChild();
            findNode->setBookData(nullptr);
        }

        findNode = findNode->getLeftChild();
        findNode->setBookData(nullptr);
    } else if (bookCode == 700) {
        for (int i = 0; i < 3; i++) {
            findNode = findNode->getRightChild();
            findNode->setBookData(nullptr);
        }
    }

    // When arriving at the heap, delete the root of the heap.
    findNode->getHeap()->Delete();

    // Fill the min winner tree value again through competition
    // level 3 selection tree node
    SelectionTreeNode* heapRootNode1 = getRoot()->getLeftChild()->getLeftChild()->getLeftChild();
    SelectionTreeNode* heapRootNode2 = getRoot()->getLeftChild()->getLeftChild()->getRightChild();
    SelectionTreeNode* heapRootNode3 = getRoot()->getLeftChild()->getRightChild()->getLeftChild();
    SelectionTreeNode* heapRootNode4 = getRoot()->getLeftChild()->getRightChild()->getRightChild();
    SelectionTreeNode* heapRootNode5 = getRoot()->getRightChild()->getLeftChild()->getLeftChild();
    SelectionTreeNode* heapRootNode6 = getRoot()->getRightChild()->getLeftChild()->getRightChild();
    SelectionTreeNode* heapRootNode7 = getRoot()->getRightChild()->getRightChild()->getLeftChild();
    SelectionTreeNode* heapRootNode8 = getRoot()->getRightChild()->getRightChild()->getRightChild();

    // Filling the level 3 selection tree node with data
    if (heapRootNode1->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode1->setBookData(heapRootNode1->getHeap()->getRoot()->getBookData());
    if (heapRootNode2->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode2->setBookData(heapRootNode2->getHeap()->getRoot()->getBookData());
    if (heapRootNode3->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode3->setBookData(heapRootNode3->getHeap()->getRoot()->getBookData());
    if (heapRootNode4->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode4->setBookData(heapRootNode4->getHeap()->getRoot()->getBookData());
    if (heapRootNode5->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode5->setBookData(heapRootNode5->getHeap()->getRoot()->getBookData());
    if (heapRootNode6->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode6->setBookData(heapRootNode6->getHeap()->getRoot()->getBookData());
    if (heapRootNode7->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode7->setBookData(heapRootNode7->getHeap()->getRoot()->getBookData());
    if (heapRootNode8->getHeap()->getRoot()->getBookData() != nullptr) heapRootNode8->setBookData(heapRootNode8->getHeap()->getRoot()->getBookData());

    // level 2 selection tree node
    SelectionTreeNode* tempNode1 = getRoot()->getLeftChild()->getLeftChild();
    SelectionTreeNode* tempNode2 = getRoot()->getLeftChild()->getRightChild();
    SelectionTreeNode* tempNode3 = getRoot()->getRightChild()->getLeftChild();
    SelectionTreeNode* tempNode4 = getRoot()->getRightChild()->getRightChild();

    // Filling the level 2 selection tree node with data through competition
    if (heapRootNode1->getBookData() == nullptr && heapRootNode2->getBookData() != nullptr) tempNode1->setBookData(heapRootNode2->getBookData());
    else if (heapRootNode1->getBookData() != nullptr && heapRootNode2->getBookData() == nullptr) tempNode1->setBookData(heapRootNode1->getBookData());
    else if (heapRootNode1->getBookData() == nullptr && heapRootNode2->getBookData() == nullptr) tempNode1->setBookData(nullptr);
    else if (heapRootNode1->getBookData()->getName() > heapRootNode2->getBookData()->getName()) tempNode1->setBookData(heapRootNode2->getBookData());
    else tempNode1->setBookData(heapRootNode1->getBookData());

    if (heapRootNode3->getBookData() == nullptr && heapRootNode4->getBookData() != nullptr) tempNode2->setBookData(heapRootNode4->getBookData());
    else if (heapRootNode3->getBookData() != nullptr && heapRootNode4->getBookData() == nullptr) tempNode2->setBookData(heapRootNode3->getBookData());
    else if (heapRootNode3->getBookData() == nullptr && heapRootNode4->getBookData() == nullptr) tempNode2->setBookData(nullptr);
    else if (heapRootNode3->getBookData()->getName() > heapRootNode4->getBookData()->getName()) tempNode2->setBookData(heapRootNode4->getBookData());
    else tempNode2->setBookData(heapRootNode3->getBookData());

    if (heapRootNode5->getBookData() == nullptr && heapRootNode6->getBookData() != nullptr) tempNode3->setBookData(heapRootNode6->getBookData());
    else if (heapRootNode5->getBookData() != nullptr && heapRootNode6->getBookData() == nullptr) tempNode3->setBookData(heapRootNode5->getBookData());
    else if (heapRootNode5->getBookData() == nullptr && heapRootNode6->getBookData() == nullptr) tempNode3->setBookData(nullptr);
    else if (heapRootNode5->getBookData()->getName() > heapRootNode6->getBookData()->getName()) tempNode3->setBookData(heapRootNode6->getBookData());
    else tempNode3->setBookData(heapRootNode5->getBookData());

    if (heapRootNode7->getBookData() == nullptr && heapRootNode8->getBookData() != nullptr) tempNode4->setBookData(heapRootNode8->getBookData());
    else if (heapRootNode7->getBookData() != nullptr && heapRootNode8->getBookData() == nullptr) tempNode4->setBookData(heapRootNode7->getBookData());
    else if (heapRootNode7->getBookData() == nullptr && heapRootNode8->getBookData() == nullptr) tempNode4->setBookData(nullptr);
    else if (heapRootNode7->getBookData()->getName() > heapRootNode8->getBookData()->getName()) tempNode4->setBookData(heapRootNode8->getBookData());
    else tempNode4->setBookData(heapRootNode7->getBookData());

    // level 1 selection tree node
    SelectionTreeNode* tempNode5 = getRoot()->getLeftChild();
    SelectionTreeNode* tempNode6 = getRoot()->getRightChild();

    // Filling the level 1 selection tree node with data through competition
    if (tempNode1->getBookData() == nullptr && tempNode2->getBookData() != nullptr) tempNode5->setBookData(tempNode2->getBookData());
    else if (tempNode1->getBookData() != nullptr && tempNode2->getBookData() == nullptr) tempNode5->setBookData(tempNode1->getBookData());
    else if (tempNode1->getBookData() == nullptr && tempNode2->getBookData() == nullptr) tempNode5->setBookData(nullptr);
    else if (tempNode1->getBookData()->getName() > tempNode2->getBookData()->getName()) tempNode5->setBookData(tempNode2->getBookData());
    else tempNode5->setBookData(tempNode1->getBookData());

    if (tempNode3->getBookData() == nullptr && tempNode4->getBookData() != nullptr) tempNode6->setBookData(tempNode4->getBookData());
    else if (tempNode3->getBookData() != nullptr && tempNode4->getBookData() == nullptr) tempNode6->setBookData(tempNode3->getBookData());
    else if (tempNode3->getBookData() == nullptr && tempNode4->getBookData() == nullptr) tempNode6->setBookData(nullptr);
    else if (tempNode3->getBookData()->getName() > tempNode4->getBookData()->getName()) tempNode6->setBookData(tempNode4->getBookData());
    else tempNode6->setBookData(tempNode3->getBookData());

    // level 0 selection tree node == root node
    SelectionTreeNode* tempNode7 = getRoot();

    // Filling the level 0 selection tree node with data through competition
    if (tempNode5->getBookData() == nullptr && tempNode6->getBookData() != nullptr) tempNode7->setBookData(tempNode6->getBookData());
    else if (tempNode5->getBookData() != nullptr && tempNode6->getBookData() == nullptr) tempNode7->setBookData(tempNode5->getBookData());
    else if (tempNode5->getBookData() == nullptr && tempNode6->getBookData() == nullptr) tempNode7->setBookData(nullptr);
    else if (tempNode5->getBookData()->getName() > tempNode6->getBookData()->getName())tempNode7->setBookData(tempNode6->getBookData());
    else tempNode7->setBookData(tempNode5->getBookData());

    return true;
}

// Function to print Book data
bool SelectionTree::printBookData(int bookCode) {
    // Find the node corresponding to the given bookCode
    SelectionTreeNode* findNode = getRoot();

    // Go to the corresponding heap with bookCode
    if (bookCode < 400) {
        findNode = findNode->getLeftChild();
        if (bookCode < 200) {
            findNode = findNode->getLeftChild();
            if (bookCode < 100) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
        else {
            findNode = findNode->getRightChild();
            if (bookCode < 300) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
    }
    else {
        findNode = findNode->getRightChild();
        if (bookCode < 600) {
            findNode = findNode->getLeftChild();
            if (bookCode < 500) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
        else {
            findNode = findNode->getRightChild();
            if (bookCode < 700) findNode = findNode->getLeftChild();
            else findNode = findNode->getRightChild();
        }
    }
    
    if (findNode != nullptr) {
        LoanBookHeapNode* root = findNode->getHeap()->getRoot(); // heap's root
        bool state = traverseHeap(root); // traverse 
        if (!state) return false; // heap is empty
    }

    // print
    *fout << "========" << "PRINT_ST" << "========" << endl;
    for (const auto& entry : bookMap) {
        string str_code;
        if(entry.second->getCode() == 0) str_code = "000";
        else str_code = to_string(entry.second->getCode());
        *fout << entry.first << "/" << str_code << "/" << entry.second->getAuthor() << "/" << entry.second->getYear() << "/" << entry.second->getLoanCount() << endl;
    }
    *fout << "========================" << endl << endl;

    // map initialize
    bookMap.clear();

    return true;
}

// Function to make Selection tree
SelectionTreeNode* SelectionTree::createSelectionTree() {
    // Create a full binary tree with 15 nodes and associated heaps
    SelectionTreeNode* nodes[15];
    LoanBookHeap* heaps[8];

    // generate new selection tree node
    for (int i = 0; i < 15; i++) nodes[i] = new SelectionTreeNode();

    // Creates a relationship between nodes
    for (int i = 0; i < 7; i++) {
        nodes[i]->setLeftChild(nodes[2 * i + 1]);
        nodes[i]->setRightChild(nodes[2 * i + 2]);
        nodes[2 * i + 1]->setParent(nodes[i]);
        nodes[2 * i + 2]->setParent(nodes[i]);
    }

    // Connects the node at the last level of the selection tree with the root of the heap.
    for (int i = 7; i < 15; i++) {
        heaps[i - 7] = new LoanBookHeap();
        nodes[i]->setHeap(heaps[i - 7]);
    }

    return nodes[0]; // Return the root of the tree
}

// Function to stores bookdata while traverse the heap
bool SelectionTree::traverseHeap(LoanBookHeapNode* node) {
    // Traverse the heap and store book data in bookMap
    if (node != nullptr && node->getBookData() != nullptr) {
        traverseHeap(node->getLeftChild());

        string bookName = node->getBookData()->getName();
        bookMap[bookName] = node->getBookData();

        traverseHeap(node->getRightChild());
        return true;
    }
    return false;
}

// Function to destructor processing
void SelectionTree::deleteTree(SelectionTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively delete the left and right subtrees
    deleteTree(node->getLeftChild());
    deleteTree(node->getRightChild());

    // Delete the current node
    delete node;
}