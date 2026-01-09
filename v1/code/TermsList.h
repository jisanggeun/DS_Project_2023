#pragma once
#include "TermsListNode.h"
#include "TermsBST.h"
#include "TermsBSTNode.h"
#include "MemberQueueNode.h"
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>

class TermsLIST
{
private:
	TermsListNode* head; // list head node
	TermsListNode* newList_node; 
	TermsListNode* curList_node;

	TermsBSTNode* newBST_node; 
	TermsBSTNode* curBST_node;

	// type bst
	TermsBST* new_A_BST;
	TermsBST* new_B_BST;
	TermsBST* new_C_BST;
	TermsBST* new_D_BST;

	int exist_token;

public:
	TermsLIST();
	~TermsLIST();

	// get head
	TermsListNode* getHead();

	// insert
	void insert(MemberQueueNode* List_node);
	// delete
	void remove_name(string data, string data2);
	std::vector<string> remove_date(string data);
};
