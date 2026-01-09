#pragma once
#include "NameBSTNode.h"
#include "MemberQueueNode.h"
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>

class NameBST
{
private:
	NameBSTNode* root;

public:
	NameBST();
	~NameBST();

	NameBSTNode* getRoot();
	void setRoot(MemberQueueNode* q_node);

	// insert
	NameBSTNode* insert(NameBSTNode* root_node, MemberQueueNode* q_node);
	// search
	int search(NameBSTNode* cur_node, string name);
	void search_print(NameBSTNode* cur_node, string name, ostream& file_log);
	// print
	void print(NameBSTNode* cur_node, ostream& file_log);
	// delete
	std::vector<string> remove(string name);
	NameBSTNode* remove_R(NameBSTNode* node, string name, std::vector<string>& removedNodes);
	NameBSTNode* findnextNode(NameBSTNode* node);

	void remove_name(string name);
	NameBSTNode* remove_R_name(NameBSTNode* node, string name);
};