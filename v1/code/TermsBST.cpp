#include "TermsBST.h"

// constructor and initialize
TermsBST::TermsBST() : root(nullptr)
{

}

TermsBST::~TermsBST()
{

}

// get root function
TermsBSTNode* TermsBST::getRoot()
{
	return root;
}

// to set root 
void TermsBST::setRoot(TermsBSTNode* root_node) {
	this->root = root_node;
}

// insert
TermsBSTNode* TermsBST::insert(TermsBSTNode* root_node, TermsBSTNode* BST_node, string end_date) {
	// If the current root node is null, insert the BST_node and return it as the new root
	if(root_node == nullptr) {
		root_node = BST_node;
      	return root_node;
	}

	string date = end_date;
	tm tm_date = {};
    istringstream ss(date);
    ss >> get_time(&tm_date, "%Y-%m-%d");
	time_t new_date = mktime(&tm_date); // Converts date to a numerical form

	// Extract the end date from the current root node and convert it to a time_t structure for comparison
	string date2 = root_node->getTermsBST_EndDate();
	tm tm_date2 = {};
	istringstream ss2(date2);
	ss2 >> get_time(&tm_date2, "%Y-%m-%d");
	time_t cur_date = mktime(&tm_date2);
	// Compare the time_t values and recursively insert the BST_node into the left or right subtree
	if(cur_date > new_date) root_node->setLeft(insert(root_node->getLeft(), BST_node, end_date));
	else if(cur_date <= new_date) root_node->setRight(insert(root_node->getRight(), BST_node, end_date));

	 // Return the updated root node
	return root_node;
}

// print
void TermsBST::print(TermsBSTNode* cur_node, ostream& file_log) {
	if(cur_node == nullptr) return; 

	// inorder traversal
	print(cur_node->getLeft(), file_log);
	file_log << cur_node->getTermsBST_name() << "/" << cur_node->getTermsBST_age() << "/" << cur_node->getTermsBST_StartDate() << "/" << cur_node->getTermsBST_EndDate() << endl;
	print(cur_node->getRight(), file_log);
}

// delete
std::vector<string> TermsBST::remove(string std_date) {
	std::vector<string> removedNodes;
	TermsBSTNode* originalRoot = root;
	// Call the recursive remove_R function to remove nodes with the specified end date and collect removed node names
	root = remove_R(root, std_date, removedNodes);
	// If the root has changed during removal, update the tree's root
	if (root != originalRoot) setRoot(root);

	// Return the vector containing the names of removed nodes
	return removedNodes;
}
TermsBSTNode* TermsBST::remove_R(TermsBSTNode* node, string std_date, std::vector<string>& removedNodes) {
	if(node == nullptr) return nullptr;

	string date = std_date;
	tm tm_date = {};
	istringstream ss(date);
	ss >> get_time(&tm_date, "%Y-%m-%d");
	time_t standard_date = mktime(&tm_date);

	string date2 = node->getTermsBST_EndDate();
	tm tm_date2 = {};
	istringstream ss2(date2);
	ss2 >> get_time(&tm_date2, "%Y-%m-%d");
	time_t cur_date = mktime(&tm_date2);

	// If the current node's end date is earlier than the specified standard_date, remove the node and update the tree
	if(cur_date < standard_date) {
		node = removeNode(node, removedNodes);
		// Recursively continue to remove nodes that match the condition
		node = remove_R(node, std_date, removedNodes);
	} else {
		// If the current node's end date is equal to or later than the standard_date, continue recursively to the left and right subtrees
		node->setLeft(remove_R(node->getLeft(), std_date, removedNodes));
		node->setRight(remove_R(node->getRight(), std_date, removedNodes));
	}
	
	return node;
}
TermsBSTNode* TermsBST::removeNode(TermsBSTNode* node, vector<string>& removedNodes) {
	if(node == nullptr) return nullptr;
    
	if(node->getLeft() != nullptr && node->getRight() != nullptr) {
		TermsBSTNode* find_nextNode = findnextNode(node->getRight()); // find next node 
		node->setTermsBSTNode(find_nextNode->getTermsBST_name(), find_nextNode->getTermsBST_age(), find_nextNode->getTermsBST_StartDate(), find_nextNode->getTermsBST_EndDate());
		node->setRight(removeNode(find_nextNode, removedNodes)); // recursive
	} else if(node->getLeft() != nullptr) { // When there is a left child
		TermsBSTNode* temp_node = node->getLeft();
		removedNodes.push_back(node->getTermsBST_name()); // push back in vector
		delete node;
		return temp_node;
	} else if(node->getRight() != nullptr) { // When there is a right child
		TermsBSTNode* temp_node = node->getRight();
		removedNodes.push_back(node->getTermsBST_name()); // push back in vector
		delete node;
		return temp_node;
	} else if(node->getLeft() == nullptr && node->getRight() == nullptr) { // When neither is present
		removedNodes.push_back(node->getTermsBST_name()); // push back in vector
		delete node; 
		return nullptr;
	}
	return node;
}
TermsBSTNode* TermsBST::findnextNode(TermsBSTNode* node) {
	// While the left child of the current node is not null, traverse the left subtree to find the leftmost (minimum) node.
	while(node->getLeft() != nullptr) node = node->getLeft(); 
    return node;
}

int TermsBST::remove_date(string name, string date) {
	int count = 0;
	// Store the original root of the tree.
	TermsBSTNode* originalRoot = root;
	//// Call the recursive remove_R_date function to remove nodes with the specified name and end date, and update the count
	root = remove_R_date(root, name, date, count);
	if (root != originalRoot) setRoot(root);

	return count;
}
TermsBSTNode* TermsBST::remove_R_date(TermsBSTNode* node, string name, string date, int& count) {
	if(node == nullptr) return nullptr;

	string cur_name = node->getTermsBST_name();

	string date1 = date;
	tm tm_date = {};
	istringstream ss(date1);
	ss >> get_time(&tm_date, "%Y-%m-%d");
	time_t standard_date = mktime(&tm_date);

	string date2 = node->getTermsBST_EndDate();
	tm tm_date2 = {};
	istringstream ss2(date2);
	ss2 >> get_time(&tm_date2, "%Y-%m-%d");
	time_t cur_date = mktime(&tm_date2);

	if(cur_date == standard_date) {
		if(cur_name == name){
			if (node->getLeft() == nullptr && node->getRight() == nullptr) {
				// When it is no child node
				count++; // 1 up
				delete node;
				return nullptr; // After deleting the node, return nullptr at that location
			} else if (node->getLeft() == nullptr) { // When a node has only a right child
				TermsBSTNode* temp = node->getRight(); 
				count++; // 1 up
				delete node;
				return temp;
			} else if (node->getRight() == nullptr) { // When a node has only a left child
				TermsBSTNode* temp = node->getLeft();
				count++; // l up
				delete node;
				return temp;
			} else {
				TermsBSTNode* nextNode = findnextNode(node->getRight()); // find next node
				node->setTermsBSTNode(nextNode->getTermsBST_name(), nextNode->getTermsBST_age(), nextNode->getTermsBST_StartDate(), nextNode->getTermsBST_EndDate());
				node->setRight(remove_R_date(node->getRight(), nextNode->getTermsBST_name(), nextNode->getTermsBST_EndDate(), count)); // recursive
			}
		} // If the current node's name is greater than the target name, recursively move to the left subtree
		else if(cur_name > name) node->setLeft(remove_R_date(node->getLeft(), name, date, count));
		// If the current node's name is less than the target name, recursively move to the right subtree
		else if(cur_name < name) node->setRight(remove_R_date(node->getRight(), name, date, count));
	} else { // not same date
		node->setLeft(remove_R_date(node->getLeft(), name, date, count));
		node->setRight(remove_R_date(node->getRight(), name, date, count));
	}

	return node;
}
