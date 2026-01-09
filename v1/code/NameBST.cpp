#include "NameBST.h"

NameBST::NameBST() : root(nullptr) // Constructor root = initialized to null
{

}
NameBST::~NameBST()
{

}

NameBSTNode* NameBST::getRoot() // to get root
{
	return root;
}

void NameBST::setRoot(MemberQueueNode* q_node) { // set root function
	string start_date = q_node->get_qnode_date();

	// Create end date of node
	tm tm_start = {};
    istringstream ss(start_date);
    ss >> get_time(&tm_start, "%Y-%m-%d"); 
	
	// Date conversion according to type
	if(q_node->get_qnode_terms_type() == "A") {
		if(tm_start.tm_mon + 6 > 12) {
			tm_start.tm_year = tm_start.tm_year + 1;
			tm_start.tm_mon = tm_start.tm_mon - 6;
		}
		else if(tm_start.tm_mon + 6 <= 12) tm_start.tm_mon = tm_start.tm_mon + 6;
	}
	else if(q_node->get_qnode_terms_type() == "B") tm_start.tm_year = tm_start.tm_year + 1;
	else if(q_node->get_qnode_terms_type() == "C") tm_start.tm_year = tm_start.tm_year + 2;
	else if(q_node->get_qnode_terms_type() == "D") tm_start.tm_year = tm_start.tm_year + 3;
	
	ostringstream es;
	es << put_time(&tm_start, "%Y-%m-%d");
	string end_date = es.str();

	// Make it root
	NameBSTNode* new_node = new NameBSTNode();		
	new_node->setNameBSTnode(q_node->get_qnode_name(), q_node->get_qnode_age(), start_date, end_date, q_node->get_qnode_terms_type());
	this->root = new_node;
}

// insert
NameBSTNode* NameBST::insert(NameBSTNode* root_node, MemberQueueNode* q_node) {
	 // If the root_node is null, create a new NameBSTNode for the current MemberQueueNode
	if(root_node == nullptr) { 
		string start_date = q_node->get_qnode_date();

		tm tm_start = {};
    	istringstream ss(start_date);
    	ss >> get_time(&tm_start, "%Y-%m-%d"); 

		// Calculate the end date based on the terms type
		if(q_node->get_qnode_terms_type() == "A") {
			if(tm_start.tm_mon + 6 > 12) {
				tm_start.tm_year = tm_start.tm_year + 1;
				tm_start.tm_mon = tm_start.tm_mon - 6;
				if(tm_start.tm_mon == 2 && tm_start.tm_mday > 28) tm_start.tm_mday = 28;
			}
			else if(tm_start.tm_mon + 6 <= 12) tm_start.tm_mon = tm_start.tm_mon + 6;
		}
		else if(q_node->get_qnode_terms_type() == "B") tm_start.tm_year = tm_start.tm_year + 1;
		else if(q_node->get_qnode_terms_type() == "C") tm_start.tm_year = tm_start.tm_year + 2;
		else if(q_node->get_qnode_terms_type() == "D") tm_start.tm_year = tm_start.tm_year + 3;

		ostringstream es;
		es << put_time(&tm_start, "%Y-%m-%d");
		string end_date = es.str();

		// Create a new NameBSTNode and set its attributes with the MemberQueueNode data
		NameBSTNode* new_node = new NameBSTNode();	
		new_node->setNameBSTnode(q_node->get_qnode_name(), q_node->get_qnode_age(), start_date, end_date, q_node->get_qnode_terms_type());
      	// Set the root_node to the newly created node and return it.
		root_node = new_node;
		return root_node;
	}

	// If root_node is not null, recursively insert the MemberQueueNode to the left or right subtree based on the name comparison
	if(root_node->getNameBST_name() > q_node->get_qnode_name()) root_node->setLeft(insert(root_node->getLeft(), q_node));
	else if(root_node->getNameBST_name() <= q_node->get_qnode_name()) root_node->setRight(insert(root_node->getRight(), q_node));

	return root_node;
}

// search
int NameBST::search(NameBSTNode* cur_node, string name) {
	if(cur_node == nullptr) return 0;
	if(cur_node->getNameBST_name() == name) return 1;
	
	// recursive left side
	int left_search = search(cur_node->getLeft(), name);
	if(left_search == 1) return 1;

	// recursive right side
	int right_search = search(cur_node->getRight(), name);
	if(right_search == 1) return 1;

	return 0;
}

void NameBST::search_print(NameBSTNode* cur_node, string name, ostream& file_log) {
	if(cur_node == nullptr) return;

	// inorder traverse
	search_print(cur_node->getLeft(), name, file_log);
	// if find name
	if(cur_node->getNameBST_name() == name) file_log << cur_node->getNameBST_name() << "/" << cur_node->getNameBST_age() << "/" << cur_node->getNameBST_StartDate() << "/" << cur_node->getNameBST_EndDate() << endl;
	search_print(cur_node->getRight(), name, file_log);
}

// print
void NameBST::print(NameBSTNode* cur_node, ostream& file_log) {
	if(cur_node == nullptr) return;

	// inorder traverse
	print(cur_node->getLeft(), file_log);
	file_log << cur_node->getNameBST_name() << "/" << cur_node->getNameBST_age() << "/" << cur_node->getNameBST_StartDate() << "/" << cur_node->getNameBST_EndDate() << endl;
	print(cur_node->getRight(), file_log);
}

// delete
std::vector<string> NameBST::remove(string name) {
	// Create a vector to store the names of removed nodes.
	std::vector<string> removedNodes;
	// Call the recursive remove_R function to remove nodes with the given name and collect removed node names.
	root = remove_R(root, name, removedNodes);
	// Return the vector containing the names of removed nodes.
	return removedNodes;
}
NameBSTNode* NameBST::remove_R(NameBSTNode* node, string name, std::vector<string>& removedNodes) {
	if(node == nullptr) return nullptr; // return null

	string cur_name = node->getNameBST_name();

	vector<string> trash;

	if(cur_name == name) {
		removedNodes.push_back(node->getNameBST_EndDate());
		if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            // When a node has no children
            delete node;
            return nullptr; // After deleting the node, return nullptr at that location
        } else if (node->getLeft() == nullptr) {
			// When there is only the right child
            NameBSTNode* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr) {
			// When there is only the left child
            NameBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        } else {
			NameBSTNode* nextNode = findnextNode(node->getRight()); // find next node 
        	node->setNameBSTnode(nextNode->getNameBST_name(), nextNode->getNameBST_age(), nextNode->getNameBST_StartDate(), nextNode->getNameBST_EndDate(), nextNode->getNameBST_Terms_type());
        	node->setRight(remove_R(node->getRight(), nextNode->getNameBST_name(), trash)); // recursive
		}
	} else if(cur_name > name) node->setLeft(remove_R(node->getLeft(), name, removedNodes));
	else if(cur_name < name) node->setRight(remove_R(node->getRight(), name, removedNodes));

	return node;
}
NameBSTNode* NameBST::findnextNode(NameBSTNode* node) {
	// Traverse the left subtree of the given node to find the leftmost (minimum) node.
	while(node->getLeft() != nullptr) node = node->getLeft(); 
    return node;
}

void NameBST::remove_name(string name) {
	root = remove_R_name(root, name);
}
NameBSTNode* NameBST::remove_R_name(NameBSTNode* node, string name) {
	if(node == nullptr) return nullptr;

	string cur_name = node->getNameBST_name();
	if(cur_name == name) {
		if (node->getLeft() == nullptr && node->getRight() == nullptr) {
            // When a node has no children
            delete node;
            return nullptr; // After deleting the node, return nullptr at that location
        } else if (!node->getLeft()) {
			// When there is only the right child
            NameBSTNode* temp = node->getRight();
            delete node;
            return temp;
        } else if (!node->getRight()) {
			// When there is only the left child
            NameBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        } else {
			NameBSTNode* nextNode = findnextNode(node->getRight()); // find next node 
        	node->setNameBSTnode(nextNode->getNameBST_name(), nextNode->getNameBST_age(), nextNode->getNameBST_StartDate(), nextNode->getNameBST_EndDate(), nextNode->getNameBST_Terms_type());
        	node->setRight(remove_R_name(node->getRight(), nextNode->getNameBST_name())); // recursive
		}
	} else if(cur_name > name) node->setLeft(remove_R_name(node->getLeft(), name));
	else if(cur_name < name) node->setRight(remove_R_name(node->getRight(), name));

	return node;
}
