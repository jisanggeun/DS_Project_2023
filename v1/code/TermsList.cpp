#include "TermsList.h"

// initialize 
TermsLIST::TermsLIST(): head(nullptr)
{
	exist_token = 0;
	newList_node = nullptr;
	curList_node = nullptr;
	newBST_node = nullptr;
	curBST_node = nullptr;
	
	new_A_BST = new TermsBST();
	new_B_BST = new TermsBST();
	new_C_BST = new TermsBST();
	new_D_BST = new TermsBST();
}
TermsLIST::~TermsLIST()
{

}

// to get head node function
TermsListNode* TermsLIST::getHead()
{
	return head;
}

// insert
// Insert qpopped q nodes into terms list node
void TermsLIST::insert(MemberQueueNode* q_node) {
	if(head == nullptr) { // first thing that comes in
		newList_node = new TermsListNode();
		newBST_node = new TermsBSTNode();

		string start_date = q_node->get_qnode_date();

		tm tm_start = {};
    	istringstream ss(start_date);
    	ss >> get_time(&tm_start, "%Y-%m-%d"); 

		// Calculate end date according to type
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

		// Created together with BST node and listnode
		newBST_node->setTermsBSTNode(q_node->get_qnode_name(), q_node->get_qnode_age(), start_date, end_date);
		newList_node->setListNode(q_node->get_qnode_terms_type(), 1, newBST_node);

		// Distribution according to type
		if(q_node->get_qnode_terms_type() == "A") new_A_BST->setRoot(newBST_node);
		else if(q_node->get_qnode_terms_type() == "B") new_B_BST->setRoot(newBST_node);
		else if(q_node->get_qnode_terms_type() == "C") new_C_BST->setRoot(newBST_node);
		else if(q_node->get_qnode_terms_type() == "D") new_D_BST->setRoot(newBST_node);
		
		// head
		head = newList_node;
	} else if(head != nullptr) { // When it is not head
		newList_node = new TermsListNode();
		newBST_node = new TermsBSTNode();
		curBST_node = new TermsBSTNode();
		
		curList_node = head; // head node
		exist_token = 0;

		string start_date = q_node->get_qnode_date();

		tm tm_start = {};
    	istringstream ss(start_date);
    	ss >> get_time(&tm_start, "%Y-%m-%d");

		// Calculate end date according to type
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

		// set BST node
		newBST_node->setTermsBSTNode(q_node->get_qnode_name(), q_node->get_qnode_age(), start_date, end_date);

		 // Check if the list node type matches the query node terms type
		if(curList_node->getListType() == q_node->get_qnode_terms_type()) {
			curBST_node = curList_node->getBSTNode();
			curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()+1, curBST_node);
			if(q_node->get_qnode_terms_type() == "A") new_A_BST->insert(new_A_BST->getRoot(), newBST_node, end_date);
			else if(q_node->get_qnode_terms_type() == "B") new_B_BST->insert(new_B_BST->getRoot(), newBST_node, end_date);
			else if(q_node->get_qnode_terms_type() == "C") new_C_BST->insert(new_C_BST->getRoot(), newBST_node, end_date);
			else if(q_node->get_qnode_terms_type() == "D") new_D_BST->insert(new_D_BST->getRoot(), newBST_node, end_date);
			exist_token = 1; // exist 
		}

		while(curList_node->getNext() != nullptr && exist_token == 0) {
			if(curList_node->getListType() == q_node->get_qnode_terms_type()) {
				curBST_node = curList_node->getBSTNode();
				curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()+1, curBST_node);
				// Insert the new BST node into the appropriate BST based on the terms type
				if(q_node->get_qnode_terms_type() == "A") new_A_BST->insert(new_A_BST->getRoot(), newBST_node, end_date);
				else if(q_node->get_qnode_terms_type() == "B") new_B_BST->insert(new_B_BST->getRoot(), newBST_node, end_date);
				else if(q_node->get_qnode_terms_type() == "C") new_C_BST->insert(new_C_BST->getRoot(), newBST_node, end_date);
				else if(q_node->get_qnode_terms_type() == "D") new_D_BST->insert(new_D_BST->getRoot(), newBST_node, end_date);
				exist_token = 1; // exist
			}
			curList_node = curList_node->getNext(); // get next node 
		}


		if(curList_node != nullptr && exist_token == 0) {
			// Check the last list node if it matches the terms type
			if(curList_node->getListType() == q_node->get_qnode_terms_type()) {
				curBST_node = curList_node->getBSTNode();
				curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()+1, curBST_node);
				// Insert the new BST node into the appropriate BST based on the terms type
				if(q_node->get_qnode_terms_type() == "A") new_A_BST->insert(new_A_BST->getRoot(), newBST_node, end_date);
				else if(q_node->get_qnode_terms_type() == "B") new_B_BST->insert(new_B_BST->getRoot(), newBST_node, end_date);
				else if(q_node->get_qnode_terms_type() == "C") new_C_BST->insert(new_C_BST->getRoot(), newBST_node, end_date);
				else if(q_node->get_qnode_terms_type() == "D") new_D_BST->insert(new_D_BST->getRoot(), newBST_node, end_date);
				exist_token = 1;	
			}
		}

		// If no matching list node is found, create a new list node and update the BST root accordingly
		if(exist_token == 0) {
			newList_node->setListNode(q_node->get_qnode_terms_type(), 1, newBST_node);
			curList_node->setNext(newList_node);
			newList_node->setNext(nullptr);
			// Update the root of the appropriate BST based on the terms type
			if(q_node->get_qnode_terms_type() == "A") new_A_BST->setRoot(newBST_node);
			else if(q_node->get_qnode_terms_type() == "B") new_B_BST->setRoot(newBST_node);
			else if(q_node->get_qnode_terms_type() == "C") new_C_BST->setRoot(newBST_node);
			else if(q_node->get_qnode_terms_type() == "D") new_D_BST->setRoot(newBST_node);
		}		
	}	
}
// search
void TermsLIST::remove_name(string data, string data2) {
	curList_node = new TermsListNode();
		
	curList_node = head; // cur_node = head
	TermsListNode* prevList_node = nullptr; // previous node

	while(curList_node != nullptr) {
		if(curList_node->getListType() == "A") {
			int num = new_A_BST->remove_date(data, data2);
			if(num != 0) {
				curBST_node = new_A_BST->getRoot();
				curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// delete list node
					if (prevList_node != nullptr) {
                    	// If there is a previous node
                   		prevList_node->setNext(curList_node->getNext());
                	} else {
                    	// If there is no previous node (i.e., the node to be deleted is head)
                    	head = curList_node->getNext();
                	}
                	delete curList_node; // delete cur_node
				}
			}
		} else if(curList_node->getListType() == "B") {
			int num = new_B_BST->remove_date(data, data2); // remove data
			if(num != 0) { // exist
				curBST_node = new_B_BST->getRoot(); // get root
				curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// delete list node
					if (prevList_node != nullptr) {
                    	// If there is a previous node
                   		prevList_node->setNext(curList_node->getNext());
                	} else {
                    	// If there is no previous node (i.e., the node to be deleted is head)
                    	head = curList_node->getNext();
                	}
                	delete curList_node;
				}
			}

		} else if(curList_node->getListType() == "C") {
			int num = new_C_BST->remove_date(data, data2); // remove date
			if(num != 0) { // exist 
				curBST_node = new_C_BST->getRoot(); // get root
				curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// delete list node 
					if (prevList_node != nullptr) {
                    	// If there is a previous nod
                   		prevList_node->setNext(curList_node->getNext());
                	} else {
                    	// If there is no previous node (i.e., the node to be deleted is head)
                    	head = curList_node->getNext();
                	}
                	delete curList_node; // delete
				}
			}
				
		} else if(curList_node->getListType() == "D") {
			int num = new_D_BST->remove_date(data, data2);
			if(num != 0) { // exist
				curBST_node = new_D_BST->getRoot(); // get root
				curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// delete list node
					if (prevList_node != nullptr) {
                    	// If there is a previous node
                   		prevList_node->setNext(curList_node->getNext());
                	} else {
						// If there is no previous node (i.e., the node to be deleted is head)
                    	head = curList_node->getNext();
                	}
                	delete curList_node;
				}
			}
		}
		// Save the current list node as the previous list node for reference
		prevList_node = curList_node;
		// Move to the next list node in the sequence
		curList_node = curList_node->getNext();	
	}
}

// delete
std::vector<string> TermsLIST::remove_date(string data) {
	curList_node = new TermsListNode();
		
	// data is date
	// 1. Delete node from TermsBST
	// 2. Decrease the number of nodes in TermsList, if it is 0, delete the list node
	// 3. Delete node from NameBST
	curList_node = head;
	TermsListNode* prevList_node = nullptr;

	std::vector<string> terms_result;
	
	while(curList_node != nullptr) {
		if(curList_node->getListType() == "A") {
			curBST_node = curList_node->getBSTNode();
			std::vector<string>result = new_A_BST->remove(data);
			terms_result.insert(terms_result.end(), result.begin(), result.end());
			if(result.size() != 0) { // exist
				curBST_node = new_A_BST->getRoot(); // get root
				for(int i = 0; i < result.size(); i++) curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					//delete list node
					if (prevList_node != nullptr) {
						// If there is a previous node
						prevList_node->setNext(curList_node->getNext());
					} else {
						// If there is no previous node (i.e., the node to be deleted is head)
						head = curList_node->getNext();
					}
					delete curList_node; // delete
				}
			}
		} else if(curList_node->getListType() == "B") {
			curBST_node = curList_node->getBSTNode();
			std::vector<string> result = new_B_BST->remove(data);
			terms_result.insert(terms_result.end(), result.begin(), result.end()); // insert vector
			if(result.size() != 0) { // exist
				curBST_node = new_B_BST->getRoot();
				for(int i = 0; i < result.size(); i++) curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// delete list node
					if (prevList_node != nullptr) {
						// If there is a previous node
						prevList_node->setNext(curList_node->getNext());
					} else {
						// If there is no previous node (i.e., the node to be deleted is head)
						head = curList_node->getNext();
					}
					delete curList_node; // delete
				}
			}
		} else if(curList_node->getListType() == "C") {
			// Delete all nodes that meet the conditions
			curBST_node = curList_node->getBSTNode();
			std::vector<string> result = new_C_BST->remove(data);
			terms_result.insert(terms_result.end(), result.begin(), result.end());
			if(result.size() != 0) { // exist
				curBST_node = new_C_BST->getRoot();
				for(int i = 0; i < result.size(); i++) curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// delete list node
					if (prevList_node != nullptr) {
						// If there is a previous node
						prevList_node->setNext(curList_node->getNext());
					} else {
						// If there is no previous node (i.e., the node to be deleted is head)
						head = curList_node->getNext();
					}
					delete curList_node;
				}
			}
		} else if(curList_node->getListType() == "D") {
		// Delete all nodes that meet the conditions
			std::vector<string> result = new_D_BST->remove(data);
			terms_result.insert(terms_result.end(), result.begin(), result.end());
			if(result.size() != 0) { // exist
				curBST_node = new_D_BST->getRoot();
				for(int i = 0; i < result.size(); i++) curList_node->setListNode(curList_node->getListType(), curList_node->getListNum()-1, curBST_node);
				if(curList_node->getListNum() == 0) {
					// list node delete
					if (prevList_node != nullptr) {
						// If there is a previous node
						prevList_node->setNext(curList_node->getNext());
					} else {
						// If there is no previous node (i.e., the node to be deleted is head)
						head = curList_node->getNext();
					}
					delete curList_node; // delete cur_node
				}
			}
		}

		// Save the current list node as the previous list node for reference
		prevList_node = curList_node;
		// Move to the next list node in the sequence
		curList_node = curList_node->getNext();	
	}
	return terms_result; // return
}