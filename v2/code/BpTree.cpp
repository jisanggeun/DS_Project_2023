#include "BpTree.h"

bool BpTree::Insert(LoanBookData* newData) {
    string key = newData->getName(); // book_name is key

    if (getRoot() == nullptr) { // BpTree is empty
        BpTreeNode* new_DataNode = new BpTreeDataNode(); // generate newDataNode 
        new_DataNode->insertDataMap(key, newData); // insert newDataNode to insert data map 
        root = new_DataNode; // A new root is created
        return true;
    }

    // BpTree is not empty
    BpTreeNode* found_DataNode = searchDataNode(key); // search key in Data node
    auto dataMap = found_DataNode->getDataMap(); 

    auto existingData = dataMap->find(key);
    if (existingData != dataMap->end()) {
        // Key already exists, update the value
        existingData->second = newData;
        return true;
    }

    // Key doesn't exist, insert the new data
    found_DataNode->insertDataMap(key, newData);
    // Check for excess data in the node and perform necessary split
    if (excessDataNode(found_DataNode)) {
        splitDataNode(found_DataNode);

        // Check for excess index nodes and perform necessary split
        BpTreeNode* parent_DataNode = found_DataNode->getParent();
        while (excessIndexNode(parent_DataNode)) {
            splitDataNode(parent_DataNode);
            parent_DataNode = parent_DataNode->getParent();
        }
    }

    return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
    // Check if the data node has more keys than allowed
    if (pDataNode->getDataMap()->size() > order - 1) return true; // order is equal to the number of elements 
    else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
    // Check if the index node has more keys than allowed
    if (pIndexNode->getIndexMap()->size() > order - 1) return true; // order is equal to the number of elements 
    else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
    // Calculate the mid point for splitting
    int mid = ceil((order - 1) / 2.0) + 1;
    int cnt = 1;
    string split_Name;

    list<string> save_RemoveName;
    map<string, LoanBookData*> split_Node;

    // Iterate through the keys and values for split
    for (auto iter = split_Node.begin(); iter != split_Node.end(); ++iter) {
        if (cnt < mid) save_RemoveName.push_back(iter->first);
        else {
            split_Name = iter->first;
            break;
        }
        ++cnt;
    }

    // Create a new data node for split
    BpTreeNode* split_DataNode = new BpTreeDataNode();
    for (const auto& data : split_Node) split_DataNode->insertDataMap(data.first, data.second);
    
    if (pDataNode->getParent() == nullptr) {
        // If the parent is nullptr, create a new index node as the root
        BpTreeNode* new_IndexNode = new BpTreeIndexNode();
        root = new_IndexNode;
    
        // Setting information on a new index node
        new_IndexNode->insertIndexMap(split_Name, split_DataNode);
        split_DataNode->setParent(new_IndexNode);
        new_IndexNode->setMostLeftChild(pDataNode);
        pDataNode->setParent(new_IndexNode);
        pDataNode->setNext(split_DataNode);
        split_DataNode->setPrev(pDataNode);
    }
    else {
        // If the parent is not nullptr, insert the split data node into the parent index node
        BpTreeNode* ParentNode = pDataNode->getParent();

        // Setting information on a parent index node
        ParentNode->insertIndexMap(split_Name, split_DataNode);
        split_DataNode->setNext(pDataNode->getNext());
        split_DataNode->setParent(ParentNode);
        split_DataNode->setPrev(pDataNode);
        pDataNode->setNext(split_DataNode);
    }
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) {
    // Calculate the mid point for splitting
    int mid = ceil((order - 1) / 2.0) + 1;
    int cnt = 1;
    string split_Name;

    list<string> save_RemoveName;
    map<string, BpTreeNode*> split_Node;

    // Iterate through the keys and values for split
    for (auto iter = pIndexNode->getIndexMap()->rbegin(); iter != pIndexNode->getIndexMap()->rend(); ++iter) {
        if (cnt <= mid) {
            split_Node.insert(*iter);
            save_RemoveName.push_back(iter->first);
        }
        else {
            split_Name = iter->first;
            break;
        }
        ++cnt;
    }

    // Remove the keys that will be moved to the new index node
    for (const string& key : save_RemoveName) pIndexNode->deleteMap(key);
    
    // Create a new index node for the split
    BpTreeNode* split_IndexNode = new BpTreeIndexNode();
    for (const auto& entry : split_Node) split_IndexNode->insertIndexMap(entry.first, entry.second);
    
    split_IndexNode->setMostLeftChild(split_IndexNode->getIndexMap()->begin()->second);

    // Setting up split and parent relationships
    if (pIndexNode->getParent() == nullptr) {
        // If the parent is nullptr, create a new index node as the root
        BpTreeNode* new_IndexNode = new BpTreeIndexNode();
        root = new_IndexNode;

        new_IndexNode->insertIndexMap(split_Name, split_IndexNode);
        split_IndexNode->setParent(new_IndexNode);
        new_IndexNode->setMostLeftChild(pIndexNode);
        pIndexNode->setParent(new_IndexNode);
    }
    else {
        // If the parent is not nullptr, insert the split index node into the parent index node
        BpTreeNode* ParentNode = pIndexNode->getParent();

        ParentNode->insertIndexMap(split_Name, split_IndexNode);
        split_IndexNode->setParent(ParentNode);
    }
}

BpTreeNode* BpTree::searchDataNode(string name) {
    // Search for the leaf data node containing the name
    BpTreeNode* pCur = root;

    // BpTree is empty
    if (pCur == nullptr || pCur->getMostLeftChild() == nullptr) return pCur;

    while (pCur != nullptr) {
        // Move to the leftmost child until reaching a leaf node
        while (pCur->getMostLeftChild() != nullptr) pCur = pCur->getMostLeftChild();

        // Search for the data node containing the name
        auto iter_find = pCur->getDataMap()->begin();
        while (iter_find != pCur->getDataMap()->end()) {
            int comparison = name.compare(iter_find->first);
            if (comparison <= 0) return pCur;
            ++iter_find;
        }

        // Move to the next node if available
        if (pCur->getNext() != nullptr) pCur = pCur->getNext();
        else break; // No more nodes to explore, break the loop
    }
    return pCur;
}

bool BpTree::searchBook(string name) {
    // Search for a book with the given name in the BpTree
    if (getRoot() == nullptr) return false;
    
    BpTreeNode* find_Node = searchDataNode(name);

    auto dataMap = find_Node->getDataMap();
    auto existingData = dataMap->find(name);

    if (existingData != dataMap->end()) {
        // Book found, print information
        *fout << "========" << "SEARCH_BP" << "========" << endl;
        auto it = existingData->second;
        string str_code;
        if(it->getCode() == 0) str_code = "000";
	    else str_code = to_string(it->getCode());
        *fout << it->getName() << "/" << str_code << "/" << it->getAuthor() << "/" << it->getYear() << "/" << it->getLoanCount() << endl;
        *fout << "========================" << endl << endl;
        return true;
    } else return false;
	
}

bool BpTree::searchRange(string start, string end) {
    // Search for books within the specified range in the BpTree
    if (getRoot() == nullptr) return false; // BpTree is empty so there are no books to find
    
    // start range node
    BpTreeNode* startNode = searchDataNode(start);
    // end range node
    BpTreeNode* endNode = searchDataNode(end);

    // Implement logic to find books in range
    BpTreeNode* find_Node = startNode;
    bool find_check = false;
    int first_check = 0;

    while(find_Node != nullptr) {
        // Logic to search for books in the range
        // (actual book printing part)
        auto dataMap = find_Node->getDataMap();
        for (const auto& data : *dataMap) {
            if (data.first >= start && data.first <= end) {
                // Print the found book or perform other actions
                if(first_check == 0) {
                    *fout << "========" << "SEARCH_BP" << "========" << endl;
                    first_check++;
                }
                string str_code;
                if(data.second->getCode() == 0) str_code = "000";
                else str_code = to_string(data.second->getCode());
                *fout << data.second->getName() << "/" << str_code << "/" << data.second->getAuthor() << "/" << data.second->getYear() << "/" << data.second->getLoanCount() << endl;
                find_check = true;
            }
        }
        // Move to the next node if it is not the end node
        if(find_Node == endNode) break;
        find_Node = find_Node->getNext(); // Move to the next node
    }
    if(first_check != 0) *fout << "========================" << endl << endl;
    return find_check; // Return whether books were found within the range
}

bool BpTree::printBook() {
    // Print all books in the BpTree
    if (getRoot() == nullptr) return false; 
    *fout << "========" << "PRINT_BP" << "========" << endl;

    BpTreeNode* cur_Node = new BpTreeNode();
    cur_Node = getRoot();

    // Move to the leftmost child of the node
    while (cur_Node->getMostLeftChild() != nullptr) cur_Node = cur_Node->getMostLeftChild(); 
    
    while (cur_Node != nullptr) {
        // Iterate through the data map and print book information
        for (auto it = cur_Node->getDataMap()->begin(); it != cur_Node->getDataMap()->end(); it++) {
            string str_code;
            if(it->second->getCode() == 0) str_code = "000";
            else str_code = to_string(it->second->getCode());
			*fout << it->second->getName() << "/" << str_code << "/" << it->second->getAuthor() << "/" << it->second->getYear() << "/" << it->second->getLoanCount() << endl;
		}
        cur_Node = cur_Node->getNext(); // Move to the next node
    }
	*fout << "========================" << endl << endl;

    return true;
}

LoanBookData* BpTree::getBookData(string name) {
    // if Bptree is empty, return nullptr as there is no data to retrieve
    if(getRoot() == nullptr) return nullptr;
    else {
        // Search for the Bptree node containing the specified name
		BpTreeNode* find_Node = searchDataNode(name);

        // Get the data map from the found Bptree node
        // Attempt to find the specified name in the data map
		auto dataMap = find_Node->getDataMap();
        auto existingData = dataMap->find(name);

        // Check if the name was found in the data map
		if (existingData != dataMap->end()) return existingData->second; // Name found, return the associated LoanBookData
		else return nullptr; // Name not found, return nullptr
		
	}
}

bool BpTree::Delete(LoanBookData* newData) {
    // Check if the Bptree is empty
    if (getRoot() == nullptr) return false;

    // Find the Bptree node containing the data to delete
    BpTreeNode* dataNodeToDelete = searchDataNode(newData->getName());

    // Get the data map from the found Bptree node
    // Attempt to find the data associated with the specified name
    auto dataMap = dataNodeToDelete->getDataMap();
    auto dataToDelete = dataMap->find(newData->getName());

    // Check if the data to delete exists in the Bptree
    if (dataToDelete == dataMap->end()) return false;
    // Delete the data from the data map
    dataNodeToDelete->deleteMap(newData->getName());

    // Check if the data node has fewer keys than the minimum required
    if (dataNodeToDelete->getDataMap()->size() < ceil(order / 2.0) - 1) {
        // If unable to borrow or merge, adjust the parent index node
        if (!borrowKeyFromSibling(dataNodeToDelete) && !mergeWithDataNodeSibling(dataNodeToDelete)) adjustParentIndexNode(dataNodeToDelete->getParent());
    }

    return true;
}

bool BpTree::borrowKeyFromSibling(BpTreeNode* pDataNode) {
    // Get parent node
    BpTreeNode* parent = pDataNode->getParent();

    // Try borrowing from the right sibling
    BpTreeNode* rightSibling = pDataNode->getNext();
    if (rightSibling != nullptr && rightSibling->getDataMap()->size() > ceil(order / 2.0) - 1) {
        // Borrow the first key from the right sibling
        auto borrowKey = rightSibling->getDataMap()->begin();
        pDataNode->insertDataMap(borrowKey->first, borrowKey->second);

        // Update the parent index node key
        // Remove the borrowed key from the right sibling
        parent->updateIndexKey(borrowKey->first, pDataNode->getDataMap()->begin()->first);
        rightSibling->deleteMap(borrowKey->first);
        return true;
    }

    // Try borrowing from the left sibling
    BpTreeNode* leftSibling = pDataNode->getPrev();
    if (leftSibling != nullptr && leftSibling->getDataMap()->size() > ceil(order / 2.0) - 1) {
        // Borrow the last key from the left sibling
        auto borrowKey = leftSibling->getDataMap()->rbegin();
        pDataNode->insertDataMap(borrowKey->first, borrowKey->second);

        // Update the parent index node key
        // Remove the borrowed key from the left sibling
        parent->updateIndexKey(borrowKey->first, leftSibling->getDataMap()->rbegin()->first);
        leftSibling->deleteMap(borrowKey->first);
        return true;
    }

    return false; // Unable to borrow from adjacent data nodes
}

bool BpTree::mergeWithDataNodeSibling(BpTreeNode* pDataNode) {
    // Get Parent node
    BpTreeNode* parent = pDataNode->getParent();

    // Find left sibling node
    BpTreeNode* leftSibling = pDataNode->getPrev();
    if (leftSibling != nullptr) {    
        // Delete the first key of the data node from its parent before merging
        // Merge with left sibling node
        // Update previous node of parent
        // Remove left sibling node from parent's current node
        // Free memory of deleted data nodes
        parent->deleteMap(pDataNode->getDataMap()->begin()->first);
        leftSibling->mergeData(pDataNode);
        parent->updateIndexKey(leftSibling->getDataMap()->rbegin()->first, leftSibling->getDataMap()->rbegin()->first);
        parent->deleteMap(leftSibling->getDataMap()->rbegin()->first);
        delete pDataNode;

        // Check the size of the parent node
        // Rescale the parent node if its size is less than the minimum requirement
        if (parent->getDataMap()->size() < ceil(order / 2.0) - 1) adjustParentIndexNode(parent);
        return true;
    }

    // Find the right sibling node (when there is no left sibling node)
    BpTreeNode* rightSibling = pDataNode->getNext();
    if (rightSibling != nullptr) {
        // Delete the first key of the data node from its parent before merging
        // Merge with right sibling node
        // Update previous node of parent
        // Remove right sibling node from parent's current node
        // Free memory of deleted data nodes
        parent->deleteMap(rightSibling->getDataMap()->begin()->first);
        pDataNode->mergeData(rightSibling);
        parent->deleteMap(rightSibling->getDataMap()->begin()->first);
        delete rightSibling;

        // Check the size of the parent node
        // Rescale the parent node if its size is less than the minimum requirement
        if (parent->getDataMap()->size() < ceil(order / 2.0) - 1) adjustParentIndexNode(parent);
        return true;
    }

    // Cannot merge because there is no left or right sibling node
    return false; 
}

void BpTree::adjustParentIndexNode(BpTreeNode* pIndexNode) {
    // Reach the root, stop adjust
    if(pIndexNode == nullptr || pIndexNode->getParent() == nullptr) return;

    // Check if the index node has fewer keys than the minimum required
    if(pIndexNode->getIndexMap()->size() < ceil(order / 2.0) - 1) {
        BpTreeNode* parent = pIndexNode->getParent();

        // Find the left and right siblings of the index node
        BpTreeNode* leftSibling = parent->findLeftSibling(pIndexNode);
        BpTreeNode* rightSibling = parent->findRightSibling(pIndexNode);

        // Try borrowing a key from the left sibling
        if(leftSibling != nullptr && leftSibling->getIndexMap()->size() > ceil(order / 2.0) - 1) {
            auto borrowKey = leftSibling->getIndexMap()->rbegin();
            pIndexNode->insertIndexMap(borrowKey->first, borrowKey->second);

            // Update the parent's key to the borrowed key
            // Remove the borrowed key from the left sibling
            parent->updateIndexKey(borrowKey->first, borrowKey->first);
            leftSibling->deleteMap(borrowKey->first);
            return;
        }

        // Try borrowing a key from the right sibling
        if(rightSibling != nullptr && rightSibling->getIndexMap()->size() > ceil(order / 2.0) - 1) {
            auto borrowKey = rightSibling->getIndexMap()->begin();
            pIndexNode->insertIndexMap(borrowKey->first, borrowKey->second);

            // Update the parent's key to the borrowed key
            // Remove the borrowed key from the right sibling
            parent->updateIndexKey(borrowKey->first, borrowKey->first);
            rightSibling->deleteMap(borrowKey->first);
            return;
        }

        // If borrowing fails, merge with the left or right sibling
        if (leftSibling != nullptr) {
            leftSibling->mergeIndex(pIndexNode);

            // Update the parent's key after merging
            // Remove the merged index node from the parent
            // Delete the merged index node
            // Recursively adjust the parent index node
            parent->updateIndexKey(leftSibling->getIndexMap()->rbegin()->first, leftSibling->getIndexMap()->rbegin()->first);
            parent->deleteMap(leftSibling->getIndexMap()->rbegin()->first);
            delete pIndexNode;
            adjustParentIndexNode(parent);
        }
        else if (rightSibling != nullptr) {
            pIndexNode->mergeIndex(rightSibling);

            // Update the parent's key after merging
            // Remove the merged index node from the parent
            // Delete the merged index node
            // Recursively adjust the parent index node
            parent->updateIndexKey(pIndexNode->getIndexMap()->begin()->first, pIndexNode->getIndexMap()->begin()->first);
            parent->deleteMap(pIndexNode->getIndexMap()->begin()->first);
            delete rightSibling;
            adjustParentIndexNode(parent);
        }
    }
}

void BpTree::destroyTree(BpTreeNode* pNode) {
    if (pNode != nullptr) {
        // If it's a data node, delete the data node
        if (dynamic_cast<BpTreeDataNode*>(pNode) != nullptr) delete static_cast<BpTreeDataNode*>(pNode);
        else {
            // If it's an index node, recursively delete its children
            auto indexNode = static_cast<BpTreeIndexNode*>(pNode);
            for (auto entry : *indexNode->getIndexMap()) destroyTree(entry.second);
            delete indexNode;
        }
    }
}