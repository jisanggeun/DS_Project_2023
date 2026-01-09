#pragma once
#include "TermsBSTNode.h"
#include "NameBSTNode.h"
#include "NameBST.h"
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

class TermsBST
{
private:
	TermsBSTNode* root;
	NameBSTNode* remove_node;

public:
	TermsBST();
	~TermsBST();

	TermsBSTNode* getRoot();
	void setRoot(TermsBSTNode* root_node);

	// insert
	TermsBSTNode* insert(TermsBSTNode* root_node, TermsBSTNode* BST_node, string end_date);
	// print
	void print(TermsBSTNode* cur_node, ostream& file_log);

	// delete
	std::vector<string> remove(string std_date);
	TermsBSTNode* remove_R(TermsBSTNode* node, string std_date, std::vector<string>& removedNodes);
	TermsBSTNode* removeNode(TermsBSTNode* node, std::vector<string>& removedNodes);
	TermsBSTNode* findnextNode(TermsBSTNode* node);

	int remove_date(string name, string date);
	TermsBSTNode* remove_R_date(TermsBSTNode* node, string name, string date, int& count);

};