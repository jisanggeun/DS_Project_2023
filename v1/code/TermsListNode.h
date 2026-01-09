#pragma once
#include <string>
#include "TermsBSTNode.h"
using namespace std;

class TermsListNode
{
private:
	string terms_type;
	int client_num;
	
	TermsListNode* next;
	TermsBSTNode* BST_node;

public:
	// constuctor and initialize
	TermsListNode() {
		client_num = 0;
		next = nullptr;
		BST_node = nullptr;
	}
	~TermsListNode() {}

	// get type
	string getListType() {
		return terms_type;
	}

	// get client's number
	int getListNum() {
		return client_num;
	}

	// get bst node 
	TermsBSTNode* getBSTNode() {
		return BST_node;
	}

	// set node
	void setListNode(string terms_type, int client_num, TermsBSTNode* BST_node) {
		this->terms_type = terms_type;
		this->client_num = client_num;
		this->BST_node = BST_node;
	}

	// get next
	TermsListNode* getNext() {
		return next; 
	}

	// to set next 
	void setNext(TermsListNode* next) {
		this->next = next; 
	}
};